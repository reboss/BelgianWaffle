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

#define MAX_P        56
#define DELAY        2000

#define PING_LEN     8
#define STOP_LEN     8
#define ACK_LEN      8
#define DEPLOY_LEN   10
#define DEPLOYED_LEN 17
#define MAX_RETRY    10

#define PING         1
#define DEPLOY       2
#define COMMAND      3
#define STREAM       4
#define ACK          5
#define DEPLOYED     6
#define STOP         7

#define DONE diag("\r\ndone\r\n")

volatile int sfd, retries = 0;
volatile int seq = 0;
volatile bool acknowledged, pong;
extern   int my_id, parent_id, child_id, dest_id;
extern   cur_state;
extern   int ping_delay, test;
extern   int max_nodes;

char payload[MAX_P];
//Variable that tells the node if it can keep sending deploys
int cont = 1;
bool deployed = FALSE;

bool is_lost_con_retries(void) {
    return retries == MAX_RETRY;
}

bool is_lost_con_ping(int ping_retries) {
    return ping_retries == MAX_RETRY;
}

void deploy_node(address packet){
    set_ids(packet);
    set_led(LED_YELLOW);
    cur_state = 0;
    switch(get_payload(packet)[0]) {

    case RSSI_TEST:
        diag("RSSI: %x\r\n", get_rssi(packet));
        test = RSSI_TEST;
        if (rssi_setup_test(packet)) {
            set_ids(packet);//set ids                                                
            seq = 0;
            deployed = TRUE;
            runfsm send_stop(my_id - 1);
        }
        break;

    case PACKET_TEST:
        diag("P TEST SEQ: %x\r\n", get_seqnum(packet));
        test = PACKET_TEST;
        if (packet_setup_test(packet) == 1) {
            set_ids(packet);//set id                                                 
            seq = 0;
            deployed = TRUE;
            runfsm send_stop(my_id - 1);
        }
        break;

    default:
        set_led(LED_RED_S);
        diag("Unrecognized deployment type");
        break;
    }

}

/*
   sends the same packet continuously until an ack is received.
   After 10 retries, lost connection is assumed.
*/


fsm send_stop(int dest) {//refactor this is ugly

    initial state SEND:
        diag("Entered send_stop FSM\r\n");
	if (acknowledged) {
		runfsm send_deploy(test);
		set_led(LED_GREEN);
                finish;
	}
      //if (is_lost_con_retries())
	      //set_led(LED_RED_S);

        address packet = tcv_wnp(SEND, sfd, STOP_LEN);
        build_packet(packet, my_id, dest, STOP, seq, payload);
        tcv_endp(packet);
        delay(DELAY, SEND);
        release;
}

fsm send_deploy {

	//address packet;
    byte pl[2];
	 
    initial state SEND_DEPLOY_INIT:
	    pl[0] = test;
            pl[1] = '\0';
	    proceed SEND_DEPLOY_ACTIVE;
        

    //keep sending deploys
    state SEND_DEPLOY_ACTIVE:
        if (cont) {
	    address packet;
	    packet = tcv_wnp(SEND_DEPLOY_ACTIVE, sfd, DEPLOY_LEN);
	    build_packet(packet, my_id, my_id + 1, DEPLOY, seq, pl);
	    diag("\r\nFunction Test:\r\nDest_ID: %x\r\nSource_ID: %x\r\n"
		"Hop_ID: %x\r\nOpCode: %x\r\nEnd: %x\r\nLength: %x\r\n"
		 "SeqNum: %x\r\nPayload: %x\r\nRSSI: %x\r\n", get_destination(packet),
			 get_source_id(packet), get_hop_id(packet), get_opcode(packet), get_end(packet),
			 get_length(packet), get_seqnum(packet), *get_payload(packet), get_rssi(packet));
		tcv_endp(packet);
			
		//temporary increment
	    seq = (seq + 1) % 256;
            delay(1000, SEND_DEPLOY_ACTIVE);
            release;
        } else {
		  //runfsm send_stop(my_id - 1);
          finish;
        }
}


fsm send_ack(int dest) {

  // ack sequence will match packet it is responding to
  int ack_sequence = 0;

  initial state SEND:
    address packet = tcv_wnp(SEND, sfd, ACK_LEN);
    build_packet(packet, my_id, dest, ACK, ack_sequence, NULL);
    tcv_endp(packet);
    finish;
}


fsm stream_data {
  
  initial state SEND:
        if (acknowledged)
            finish;
        if (is_lost_con_retries())
	    set_led(LED_RED_S);
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
	    set_led(LED_RED_S);

        pong = NO;
        address packet;
        packet = tcv_wnp(SEND, sfd, PING_LEN);
        build_packet(packet, my_id, dest_id, PING, ping_sequence, NULL);               delay(ping_delay, SEND);
        release;
}

fsm receive {
	address packet;
	sint plength;

	initial state INIT_CC1100:
		proceed RECV;
	
	state RECV:
		packet = tcv_rnp(RECV, sfd);
	        plength = tcv_left(packet);
		proceed EVALUATE;

	state EVALUATE:
		 switch (get_opcode(packet)) {
		 case PING:
		     if (get_hop_id(packet) < my_id) {
		         seq = 0;
			     runfsm send_pong;
		     } else {
		         pong = YES;
		     }
		     break;
		 case DEPLOY://turn into funciton to long/complicated
		     if (deployed)
		       break;
		     deploy_node(packet);
		     break;
			  
			/* The DEPLOYED opcode is intended for the sink, nodes need to pass
			   it on and the sink has to keep track of when every node is
			   deployed, so it can begin streaming */
		case DEPLOYED:
		        //runfsm send_deployed;
			break;
		case STREAM:
			// check sequence number for lost ack
			// check if packet has reached it's destination
			acknowledged = NO;
			strncpy(payload, (char *) packet+3, MAX_P);
			runfsm stream_data;
			runfsm send_ack(dest_id);
			break;
		case ACK://deal w/ type
			acknowledged = YES;
			retries = 0;
			break;
		case COMMAND:
			break;
		case STOP:
		  if (get_destination(packet) == my_id) {
			runfsm send_ack(get_source_id(packet));
			cont = 0;
			diag("\r\nRECEIVED STOP...\r\n");
		  }
			break;
		default:
			break;
		}
		tcv_endp(packet);
		proceed RECV;
}
