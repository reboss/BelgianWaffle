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

#define DEPLOY_DELAY 300
#define MAP_P 56
#define PING_LEN     10
#define STOP_LEN     10
#define ACK_LEN      10
#define DEPLOY_LEN   10
#define DEPLOYED_LEN 18
#define MAX_RETRY    10

#define DELAY 2000

#define PING     1
#define DEPLOY   2
#define COMMAND  3
#define STREAM   4
#define ACK      5
#define DEPLOYED 6
#define STOP     7
#define KILL     8

#define DONE diag("\r\nDone\r\n")

#define SINK_ID 0

#define MILLISECOND 1
#define SECOND 1000


volatile int sfd, retries = 0;
volatile int seq = 0;
volatile int msgs_lost = 0;
volatile bool acknowledged, pong;
stream_stat stream_info;

extern int my_id, parent_id, child_id, dest_id;
extern int ping_delay, test;
extern int max_nodes;
extern bool sink;
extern int debug;

char payload[MAX_P];
//Variable that tells the node if it can keep sending deploys
int cont = 1;
bool deployed = NO;

bool is_lost_con_retries(void) {
	return retries == MAX_RETRY;
}

bool is_lost_con_ping(int ping_retries) {
	return ping_retries == MAX_RETRY;
}


void debug_diag(address packet) {
	diag("\r\nFunction Test:\r\nDest_ID: %x\r\nSource_ID: %x\r\n"
	     "Hop_ID: %x\r\nOpCode: %x\r\nEnd: %x\r\nLength: %x\r\n"
	     "SeqNum: %x\r\nPayload: %x\r\nMaxnodes: %x\r\nRSSI: %x\r\n",
	     get_destination(packet), get_source_id(packet), get_hop_id(packet),
	     get_opcode(packet), get_end(packet), get_length(packet),
	     get_seqnum(packet), *get_payload(packet), get_payload(packet)[1],
	     get_rssi(packet));
}

fsm send_stop(int dest) {
  initial state SEND:
	if (debug)
	  diag("Entered send_stop FSM\r\n");
	if (acknowledged) {
	  if (debug)
		diag("Entered send_stop_acknowledged");
	  deployed = YES;
	  detrm_fsm_deploy_behvr();
	  set_led(LED_GREEN_S);
	  finish;
	}
	address packet = tcv_wnp(SEND, sfd, STOP_LEN);
	build_packet(packet, my_id, dest, STOP, seq, payload);
	tcv_endp(packet);
        acknowledged = NO;
	delay(DELAY, SEND);
	release;
}


bool is_last_node(void) {
    return my_id == (max_nodes - 1);
}

fsm final_deploy {

	int i = 0;
    address packet;
	char msg[56];
	int len;
	initial state INIT:
	    diag("value of ack is %d\r\n", acknowledged);
            set_power(sfd, HIGH_POWER);//set high power
	    if (debug)
	        diag("In final_deploy fsm\r\n");
	    proceed SEND;

	state SEND:
	  if (msgs_lost == 0 || !acknowledged) {
		diag("In sending final deploy\r\n");
		form(msg, "%dTEAM FLABERGASTED%d\0", msgs_lost, i);
		//form(msg, "55TEAM FLABBERGASTED");
		len = strlen(msg);
		len += len % 2 ? 1 : 2;//add room for null term
		packet = tcv_wnp(SEND, sfd, 8 + len);
		build_packet(packet, my_id, SINK_ID, STREAM, seq, msg);
		//packet = tcv_wnp(SEND, sfd, 8 + 20);
		//build_packet(packet, my_id, SINK_ID, STREAM, seq,
		//"TEAM FLABBERGASTED");
		tcv_endp(packet);
		msgs_lost++;
		delay(SECOND, SEND);
		release;
	    }
	    proceed NEW;

	state NEW:
		acknowledged = NO;
		diag("final deploy NEW\r\n");
		if (i >= 100)
			finish;
		i++;
		msgs_lost = 0;
		seq++;
		proceed SEND;
}


void detrm_fsm_deploy_behvr(void) {
  if (!is_last_node()){ // OLD (For verify): my_id<max_nodes-1
	if(test == PACKET_TEST){
	  set_power(sfd, LOW_POWER);
	}
    runfsm send_deploy(test);
  } else {
        set_led(LED_GREEN_S);
	acknowledged = NO;
	runfsm final_deploy;
  }
}

void set_test_mode_data(address packet) {
    set_ids(packet);
    seq = 0;
    deployed = YES;
}

/*
   sends the same packet continuously until an ack is received.
   After 10 retries, lost connection is assumed.
*/

 
void set_test_behaviour(address packet) {
	static bool backtrack = NO;
	
	switch(get_payload(packet)[0]) {
	case RSSI_TEST:
		if (debug)
			diag("RSSI: %x\r\n", get_rssi(packet));
		test = RSSI_TEST;
		if (rssi_setup_test(packet)) {
			set_test_mode_data(packet);
			runfsm send_stop(my_id - 1);
		}
		break;
	case PACKET_TEST:
		if (debug)
			diag("PACKET TEST SEQ: %x\r\n", get_seqnum(packet));
		test = PACKET_TEST;
		set_led(LED_YELLOW_S);
		if (packet_setup_test(packet) == 1) {
			set_test_mode_data(packet);
			runfsm send_stop(my_id - 1);
		}
		break;
	default:
		set_led(LED_RED_S);
		if (debug)
			diag("Unrecognized deployment type");
		break;
	}
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

	    if (debug) {
		    debug_diag(packet);
		    diag("deploy sent\r\n");
	    }
	    set_led(LED_GREEN);
	    tcv_endp(packet);

	    //temporary increment
	    seq = (seq + 1) % 256;
	    delay(DEPLOY_DELAY, SEND_DEPLOY_ACTIVE);
	    release;
        } else {
		//runfsm send_stop(my_id - 1);
		finish;
	}
        
}

fsm send_ack(int dest) {

  // ack sequence will match packet it is responding to
  initial state SEND:
	  if (debug)
		  diag("In send ack fsm\r\n");
    address packet = tcv_wnp(SEND, sfd, ACK_LEN);
    build_packet(packet, my_id, dest, ACK, 0, NULL);
    tcv_endp(packet);
    finish;
}

fsm stream_data(address packet_copy) {
  
  /* indicates whether to increment msgs_lost when we don't receive an ACK */
  int flag;
  
  initial state INIT:
	flag = NO;
    proceed SEND;

  state SEND:
	  if (debug)
		  diag("In stream data fsm\r\n");

	  if (acknowledged) {
		  if (debug)
			diag("stream ack\r\n");
		  flag = NO;
		  ufree(packet_copy);
		  finish;
	  }
	  if (flag == YES)
		msgs_lost++;

	  if (is_lost_con_retries())
		set_led(LED_RED_S);
        address packet = tcv_wnp(SEND, sfd, packet_length(packet_copy));
        copy_packet(packet, packet_copy);
	if (debug)
		debug_diag(packet);
	tcv_endp(packet);
	flag = YES;
	delay(SECOND, SEND);
	release;
}


fsm indicate_reset {

    int reset_time = 300 * MILLISECOND;

    initial state YELLOW:
        set_led(LED_YELLOW);
	delay(reset_time, GREEN);
	release;

    state GREEN:
	set_led(LED_GREEN);
	delay(reset_time, RED);
	release;

    state RED:
	set_led(LED_RED);
	delay(reset_time, YELLOW);
	release;
}


fsm send_pong {

    initial state SEND:
        address packet = tcv_wnp(SEND, sfd, PING_LEN);
        build_packet(packet, my_id, parent_id, PING, 0, NULL);
	tcv_endp(packet);
	if (debug)
		diag("sent pong\r\n");
        finish;
}

fsm send_ping {

    int ping_retries = 0;
    bool pong_atf = NO;
    initial state SEND:
	  if (pong)
		ping_retries = 0;
	  else
		ping_retries++;
	  /*if (is_lost_con_ping(ping_retries)) {
		if (!sink) {
		  killall(receive);
		  killall(send_deploy);
		  killall(send_pong);
		  killall(send_stop);
		  killall(stream_data);
		  runfsm indicate_reset;
		  finish;
		}
		if (debug)
			diag("Network shutdown\r\n");
		cont = 1;
		runfsm send_deploy;
	        finish;
	}*/

        pong = NO;
        address packet = tcv_wnp(SEND, sfd, PING_LEN);
        build_packet(packet, my_id, child_id, PING, 0, NULL);
	/*if (debug)
		debug_diag(packet);*/
	tcv_endp(packet);
	if (debug)
		diag("Ping sent\r\n");
	delay(ping_delay, SEND);
	release;
}

fsm receive {

    address packet;
    initial state INIT_CC1100:
        proceed RECV;

    state RECV:
        packet = tcv_rnp(RECV, sfd);
        if (debug)
            diag("after receive RECV packet recieve\n\r");
        proceed EVALUATE;

    state EVALUATE:
        switch (get_opcode(packet)) {
        case PING:
            if (get_destination(packet) == my_id) {
                if (get_source_id(packet) == parent_id) {
                    if (debug)
                        diag("sending pong");
                    runfsm send_pong;
                } else {
                    if (debug)
                        diag("received pong");
                    pong = YES;
                }
            }
            break;
        case DEPLOY:
            if (deployed)
                break;
            set_ids(packet);
            max_nodes = get_payload(packet)[1];//set max nodes
            set_test_behaviour(packet);
            break;

        /* IS DEPLOYED OPCODE BEING USED? */
        case DEPLOYED:
            if (debug)
                diag("Recieved DEPLOYED");
            //runfsm send_deployed;
            break;
        case STREAM:
		  if (debug)
            diag("stream hop id: %d\r\nchild id:%d\r\nstream source id %d\r\n",
				 get_hop_id(packet), child_id, get_source_id(packet));
		  if (get_hop_id(packet) != child_id) {//if not from parent
			diag("not parent\r\n");
			break;
		  }
            runfsm send_ack(get_hop_id(packet));
            msgs_lost = get_msgs_lost(packet);
            if (sink) {
                add_stream_info(packet);
                if (debug) {
                    diag("STREAM:%s\r\n", get_payload(packet));
                    diag("STREAM PACKET LOSS: %d PACKETS\r\n", msgs_lost);
                    //debug_diag(packet);
                }
                break;
            } else {
                if (debug){
                    diag("\r\nHOP PACKET!!!!!\r\n%s\r\n", get_payload(packet));
                    //debug_diag(packet);
                }
				
                acknowledged = NO;
                address hop_packet = umalloc(packet_length(packet) / 2 *
                                             sizeof(word));
                copy_packet(hop_packet, packet);
                runfsm stream_data(hop_packet);
            }
            break;
        case ACK://deal w/ type
            if (debug)
                diag("Recieved ACK\r\n");
            if (get_destination(packet) == my_id) {
                acknowledged = YES;
                retries = 0;
            }
            break;
        case COMMAND:
            if (debug)
                diag("Recieved COMMAND\r\n");
            break;
        case STOP:
            set_power(sfd, HIGH_POWER);//set high power
            if (get_destination(packet) == my_id) {
			  set_led(LED_GREEN_S);
                runfsm send_ack(get_source_id(packet));
                if (cont) {
                    if (debug)
                        diag("cont is equal to 1 and will be set to 0\r\n");
                    runfsm send_ping;
                }
                cont = 0;
                if (debug)
                    diag("\r\nRECEIVED STOP...\r\n");
            }
            break;
        default:
            if (debug)
                diag("Unknown opcode\r\n");
            break;
        }
        tcv_endp(packet);
        if (debug)
            diag("END fsm Recieve\r\n");
        proceed RECV;
}


