/* ####################################################################
   CMPT 464
   Ad Hoc Network Deployment
   Authors: Aidan Bush, Elliott Sobek, Christopher Dubeau,
   John Mulvany-Robbins, Kevin Saforo
   Thursday, November 10

   File: network.cc
   Description: This file contains all the logic for sending packets
   and how to handle recieved packets.
   ####################################################################
*/

#include "sysio.h"
#include "serf.h"
#include "ser.h"
#include "plug_null.h"
#include "tcvphys.h"
#include "phys_cc1100.h"

#include "node_tools.h"
#include "packet_test.h"
#include "rssi_test.h"
#include "network_help.h"
#include "network.h"
#include "node_led.h"

#define MAX_P      56
#define PING_LEN   2
#define ACK_LEN    2
#define DEPLOY_LEN 2
#define DEPLOYED_LEN 17
#define MAX_RETRY  10

#define PING       1
#define DEPLOY     2
#define COMMAND    3
#define STREAM     4
#define ACK        5
#define DEPLOYED   6
#define STOP       7

#define LED_YELLOW 0
#define LED_GREEN  1
#define LED_RED    2

#define TRUE       1
#define FALSE      0

volatile int sfd, retries = 0;
volatile int seq = 0;
volatile bool acknowledged, pong;
// get id's from node_tools
extern int my_id, parent_id, child_id, dest_id;
extern cur_state;
extern int ping_delay;

char payload[MAX_P];
//Variable that tells the node if it can keep sending deploys
int cont = 0;

/*
   sends the same packet continuously until an ack is received.
   After 10 retries, lost connection is assumed.
*/

fsm send_deploy {

  initial state SEND_DEPLOY_INIT:
    address packet;
    build_packet(packet, my_id, my_id + 1, DEPLOY, seq, NULL);

    //keep sending deploys
  state SEND_DEPLOY_ACTIVE:
    address packet;
    if (cont) {
      tcv_endp(packet);
      delay(1000, SEND_DEPLOY_ACTIVE);
      proceed SEND_DEPLOY_ACTIVE;
    } else {
      //Tell sink we are deployed
      if (my_id != 1) {
        build_packet(packet, my_id, 1, DEPLOYED, seq, NULL);
        tcv_endp(packet);
      }

      /*TODO: Need state to wait for other nodes while they
        are setting up. Or start sending pings? */

      release;
    }
}

bool is_lost_con_retries(void) {
    return retries == MAX_RETRY;
}

bool is_lost_con_ping(int ping_retries) {
    return ping_retries == MAX_RETRY;
}


fsm send_ack {

  // ack sequence will match packet it is responding to
  int ack_sequence = 0;

  initial state SEND:
    address packet = tcv_wnp(SEND, sfd, ACK_LEN);
    build_packet(packet, my_id, dest_id, ACK, ack_sequence, NULL);
    tcv_endp(packet);
    finish;
}


fsm stream_data {

    initial state SEND:
        if (acknowledged)
            finish;
        if (is_lost_con_retries())
            leds(LED_RED, 1);
        address packet;
        sint plen = strlen(payload);
        packet = tcv_wnp(SEND, sfd, plen);
        //should be forwarding not rebuilding
        build_packet(packet, my_id, dest_id, STREAM, seq, payload);
        tcv_endp(packet);
        retries++;
        seq++;
}

fsm send_pong {

    initial state SEND:
        address packet;
        packet = tcv_wnp(SEND, sfd, PING_LEN);
        build_packet(packet, my_id, dest_id, PING, seq, NULL);
        finish;
}

fsm send_ping {

    int ping_sequence = 0;
    int ping_retries = 0;

    initial state SEND:
        if (pong) {
            ping_sequence++;
            ping_retries = 0;
        }
        else
            ping_retries++;
        if (is_lost_con_ping(ping_retries))
            leds(LED_RED, 1);

        pong = FALSE;
        address packet;
        packet = tcv_wnp(SEND, sfd, PING_LEN);
        build_packet(packet, my_id, dest_id, PING, ping_sequence, NULL);
        delay(2000, SEND);
        release;
}

fsm send_deployed {

    char * payload;

    initial state SEND:
        sprintf(payload, "Node %d deployed\n", my_id);
        if (acknowledged)
          finish;
        if (is_lost_con_retries())
            leds(LED_RED, 1);
        address packet = tcv_wnp(SEND, sfd, DEPLOYED_LEN);
        build_packet(packet, my_id, dest_id, DEPLOYED, seq, payload);
        tcv_endp(packet);
        retries++;
        seq++;
        delay(2000, SEND);//should use define not magic number
        release;
}

fsm receive {
	address packet;
	sint plength;

	initial state RECV:
		packet = tcv_rnp(RECV, sfd);
	    plength = tcv_left(packet);
		proceed EVALUATE;

	state EVALUATE:
        switch (get_opcode(packet)) {
        case PING:
		    //TODO: Can't nodes receive pings from their parent as well?
		    if (get_hop_id(packet) < my_id)
				runfsm send_pong;
			else
				pong = TRUE;
			break;
		case DEPLOY:
		    set_ids(packet);
			//Make LED flash yellow when packet received
			cur_state = 0;
			runfsm node_leds;
			runfsm send_deploy;
			break;

            /* The DEPLOYED opcode is intended for the sink, nodes need to pass
               it on and the sink has to keep track of when every node is
               deployed, so it can begin streaming */
		case DEPLOYED:
            runfsm send_deployed;
			break;
		case STREAM:
			// check sequence number for lost ack
			// check if packet has reached it's destination
			acknowledged = FALSE;
			strncpy(payload, (char *) packet+3, MAX_P);
			runfsm stream_data;
			runfsm send_ack;
			break;
		case ACK:
			acknowledged = TRUE;
			retries = 0;
			break;
		case COMMAND:
			break;
		case STOP:
		    cont = 0;
            break;
        default:
            break;
        }
}
