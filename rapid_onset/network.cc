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
#define SINK_ID    0

#define PING_LEN   8
#define STOP_LEN   8
#define ACK_LEN    8
#define DEPLOY_LEN 12

#define DEPLOYED_LEN 17
#define MAX_RETRY    10

#define PING       1
#define DEPLOY     2
#define COMMAND    3
#define STREAM     4
#define ACK        5
#define DEPLOYED   6
#define STOP       7
#define KILL       8

#define LED_YELLOW 0
#define LED_GREEN  1
#define LED_RED    2
#define LED_RED_S  3

#define SINK_ID     0 //move to .h so can be used else where

volatile int sfd, retries = 0;
volatile int seq = 0;
volatile bool acknowledged, pong;
extern int my_id, parent_id, child_id, dest_id;
extern cur_state;
extern int ping_delay, test;
extern int max_nodes;
extern bool sink;

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


//sends the test messages to sink
fsm final_deploy {
    address packet;
    
    initial state INIT:
        packet = tcv_wnp(INIT, sfd, 8 + 20);
        build_packet(packet, my_id, SINK_ID, STREAM, seq,
		 "TEAM FLABBERGASTED");
        tcv_endp(packet);
        finish;
}

fsm send_stop(int dest) {//refactor this is ugly

    initial state SEND:
        diag("Entered send_stop FSM\r\n");
	    if (acknowledged) {
		    if (my_id < max_nodes - 1)//if not last node
			    runfsm send_deploy(test);
		    else
			    runfsm final_deploy;
		    deployed = TRUE;
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

    byte pl[3];
	 
    initial state SEND_DEPLOY_INIT:
        pl[0] = test;
        pl[1] = max_nodes;
        pl[2] = '\0';
	proceed SEND_DEPLOY_ACTIVE;

    //keep sending deploys
    state SEND_DEPLOY_ACTIVE:
        if (cont) {
	    address packet;
	    packet = tcv_wnp(SEND_DEPLOY_ACTIVE, sfd, DEPLOY_LEN);
	    build_packet(packet, my_id, my_id + 1, DEPLOY, seq, pl);
		diag("\r\nFunction Test:\r\nDest_ID: %x\r\nSource_ID: %x\r\n"
			 "Hop_ID: %x\r\nOpCode: %x\r\nEnd: %x\r\nLength: %x\r\n"
			 "SeqNum: %x\r\nPayload: %x\r\nMaxnodes: %x\r\nRSSI: %x\r\n",
             get_destination(packet), get_source_id(packet), get_hop_id(packet),
             get_opcode(packet), get_end(packet), get_length(packet),
             get_seqnum(packet), *get_payload(packet), get_payload(packet)[1],
             get_rssi(packet));
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


fsm stream_data(address packet) {

	address hop_packet;
	
  initial state SEND:
        if (acknowledged)
            finish;
        if (is_lost_con_retries())
	    set_led(LED_RED_S);
	
	hop_packet = tcv_wnp(SEND, sfd,
			     strlen(get_payload(packet)) + 1 + 8);
	build_packet(hop_packet, get_source_id(packet),
		     get_destination(packet), get_opcode(packet), seq++,
		     get_payload(packet));
	tcv_endp(hop_packet);
       
        retries++;
        seq++;
}


fsm indicate_reset {

	initial state YELLOW:
		set_led(LED_YELLOW);
	        delay(300, GREEN);
		release;

	state GREEN:
		set_led(LED_GREEN);
		delay(300, RED);
		release;
	state RED:
		set_led(LED_RED);
	        delay(300, YELLOW);
		release;
}


fsm send_pong {
  
  initial state SEND:
        address packet;
        packet = tcv_wnp(SEND, sfd, PING_LEN);
        build_packet(packet, my_id, parent_id, PING, 0, NULL);
	tcv_endp(packet);
	diag("sent pong\r\n");
        finish;
}

fsm send_ping {

    int ping_retries = 0;
    bool pong_atf = FALSE;
    address packet;

    initial state SEND:
        if (pong)
            ping_retries = 0;
        else
            ping_retries++;
        
        if (is_lost_con_ping(ping_retries)) {
	        
	        if (!sink) {
		        killall(receive);
		        killall(send_pong);
		        killall(stream_data);
		        runfsm indicate_reset;
		        finish;
		}
	        diag("Network shutdown\r\n");
		cont = 1;
		runfsm send_deploy;
	        finish;
	}
	
	diag("about to send ping\r\n");
        pong = NO;
        packet = tcv_wnp(SEND, sfd, PING_LEN);
        build_packet(packet, my_id, child_id, PING, 0, NULL);
	diag("\r\nFunction Test:\r\nDest_ID: %x\r\nSource_ID: %x\r\n"
	     "Hop_ID: %x\r\nOpCode: %x\r\nEnd: %x\r\nLength: %x\r\n"
	     "SeqNum: %x\r\nPayload: %x\r\nRSSI: %x\r\n", get_destination(packet),
	     get_source_id(packet), get_hop_id(packet), get_opcode(packet), get_end(packet),
	     get_length(packet), get_seqnum(packet), *get_payload(packet), get_rssi(packet));
	tcv_endp(packet);
	diag("ping sent\r\n");
	delay(ping_delay, SEND);
	release;

}

fsm receive {
	address packet;
	sint plength;

	initial state INIT_CC1100:
		proceed RECV;
	
	state RECV:
		diag("before\n\r");
	        packet = tcv_rnp(RECV, sfd);
		diag("here\r\n");
		diag("after\n\r");
		proceed EVALUATE;

	state EVALUATE:
		switch (get_opcode(packet)) {
		case PING:
		    if (get_destination(packet) == my_id) {
			    if (get_source_id(packet) == parent_id) {
				    diag("sending pong");
				    runfsm send_pong;
			    } else {
				    diag("received pong");
				    pong = YES;
			    }
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
			diag("\r\nHOP PACKET!!!!!\r\n%s\r\n", get_payload(packet));
			// check sequence number for lost ack
			// check if packet has reached it's destination
			acknowledged = NO;
			strncpy(get_payload(packet), payload, MAX_P);
			runfsm stream_data(packet);
			runfsm send_ack(get_hop_id(packet));
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
				if (cont) {
					diag("cont is equal to 1 and will be set to 0\r\n");
					runfsm send_ping;
				}
				
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
