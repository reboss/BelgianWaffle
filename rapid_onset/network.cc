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

volatile int sfd, retries = 0;
volatile int seq = 0;
volatile bool acknowledged, pong;
extern int my_id, parent_id, child_id, dest_id;
extern cur_state;
extern int ping_delay, test;
extern int max_nodes;
extern bool sink;

const char *deploy_message =
	"Lorem ipsum dolor sit amet, consectetur adipiscing elit. Nullam sagittis interdum magna nec aliquam. Aenean lacinia gravida erat vel ultricies. Donec sed mi ac ante consequat vestibulum in vitae elit. Donec a bibendum lectus, a varius ex. Cras accumsan sapien quis sem condimentum, at ornare leo scelerisque. Donec sit amet augue risus. Etiam dignissim facilisis dolor eu porttitor. Morbi neque ligula, sodales ac ullamcorper eu, posuere in ipsum. Suspendisse bibendum massa id ligula rhoncus feugiat. Integer posuere dolor magna, a elementum nibh egestas vel. Morbi sit amet orci facilisis, mollis dui id, vulputate neque. Pellentesque pharetra, risus a elementum sagittis, neque ipsum blandit leo, nec viverra augue sapien vel nisi. Morbi euismod consectetur magna, at tincidunt orci laoreet et. Etiam fringilla tincidunt commodo. Donec sollicitudin nunc lectus, non maximus ligula ornare at.";

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

fsm send_stop(int dest) {

    initial state SEND:
        diag("Entered send_stop FSM\r\n");
	    if (acknowledged) {
	      detrm_fsm_deploy_behvr();
	      deployed = YES;
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
            deployed = YES;
            runfsm send_stop(my_id - 1);
        }
        break;

    case PACKET_TEST:
        diag("P TEST SEQ: %x\r\n", get_seqnum(packet));
        test = PACKET_TEST;
        if (packet_setup_test(packet) == 1) {
            set_ids(packet);//set id                                                 
            seq = 0;
            deployed = YES;
            runfsm send_stop(my_id - 1);
        }
        break;

    default:
        set_led(LED_RED_S);
        diag("Unrecognized deployment type");
        break;
    }
}


bool is_last_node(void) {
  return my_id == (max_nodes - 1);
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


//sends the test messages to sink
fsm final_deploy {

    address packet;
    char msg[56];
    int i, len;
    
    initial state INIT:
        i = 1;
        diag("In final_deploy fsm\r\n");
        proceed SEND;
    
    state SEND:
        form(msg, "TEAM FLABERGASTED:%d", i);
        len = strlen(msg);
        len += len % 2 ? 1 : 2;//add room for null term
        diag("msg:%s\r\nlen:%d\r\n", msg, len);
        packet = tcv_wnp(SEND, sfd, 8 + len);
        diag("wnp\r\n");
        build_packet(packet, my_id, SINK_ID, STREAM, seq++, msg);
        //packet = tcv_wnp(SEND, sfd, 8 + 20);
        //build_packet(packet, my_id, SINK_ID, STREAM, seq,
		 //"TEAM FLABBERGASTED");
        diag("build packet\r\n");
        tcv_endp(packet);
        diag("endp\r\n");
        i++;
        delay(SECOND, SEND);
        release;
}

void detrm_fsm_deploy_behvr(void) {
  if (!is_last_node()) // OLD (For verify): my_id<max_nodes-1
    runfsm send_deploy(test);
  else
    runfsm final_deploy;
}

void set_test_behaviour(address packet) {
    static bool backtrack = NO;

    switch(get_payload(packet)[0]) {
    case RSSI_TEST:
        diag("RSSI: %x\r\n", get_rssi(packet));
        if (backtrack){//need to fix
            if (rssi_test_(pcaket)){
                set_test_mode_data(packet);
                runfsm send_stop(my_id - 1);
            }
        } else {
            test = RSSI_TEST;
            if (rssi_setup_test(packet))
                backtrack = Yes;
        }
        break;
    case PACKET_TEST:
        diag("PACKET TEST SEQ: %x\r\n", get_seqnum(packet));
        test = PACKET_TEST;
        if (packet_setup_test(packet) == 1) {
	        set_test_mode_data(packet);
            runfsm send_stop(my_id - 1);
        }
        break;
    default:
        set_led(LED_RED_S);
        diag("Unrecognized deployment type");
        break;
    }
}

//TODO: SEE DEPLOYED case in receive fsm
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
		delay(SECOND, SEND_DEPLOY_ACTIVE);
		release;
        } else {
		  //runfsm send_stop(my_id - 1);
          finish;
        }
}

fsm send_ack(int dest) {

  // ack sequence will match packet it is responding to

  initial state SEND:
    diag("In send ack fsm\r\n");
    address packet = tcv_wnp(SEND, sfd, ACK_LEN);
    build_packet(packet, my_id, dest, ACK, 0, NULL);
    tcv_endp(packet);
    finish;
}

//wont work need to write the packet here the packet here
fsm stream_data(address packet_copy) {

  initial state SEND:
    diag("In stream data fsm\r\n");
        if (acknowledged)
            diag("stream ack\r\n");
            finish;
        if (is_lost_con_retries())
	  set_led(LED_RED_S);
        address packet = tcv_wnp(SEND, sfd, packet_length(packet_copy));
        copy_packet(packet, packet_copy);
	ufree(packet_copy);
        tcv_endp(packet);
        diag("End fsm stream_data\r\n");
        finish;
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

        pong = NO;
        address packet = tcv_wnp(SEND, sfd, PING_LEN);
        build_packet(packet, my_id, child_id, PING, 0, NULL);
	diag("\r\nFunction Test:\r\nDest_ID: %x\r\nSource_ID: %x\r\n"
	     "Hop_ID: %x\r\nOpCode: %x\r\nEnd: %x\r\nLength: %x\r\n"
	     "SeqNum: %x\r\nPayload: %x\r\nRSSI: %x\r\n", get_destination(packet),
	     get_source_id(packet), get_hop_id(packet), get_opcode(packet), get_end(packet),
	     get_length(packet), get_seqnum(packet), *get_payload(packet), get_rssi(packet));
	tcv_endp(packet);
	diag("Ping sent\r\n");
	delay(ping_delay, SEND);
	release;

}

fsm receive {

	address packet;
	sint plength; // Unused?

	initial state INIT_CC1100:
		proceed RECV;

	state RECV:
	        packet = tcv_rnp(RECV, sfd);
		diag("after receive RECV packet recieve\n\r");
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

			set_ids(packet);
			cur_state = 0;
			max_nodes = get_payload(packet)[1];//set max nodes
			set_test_behaviour(packet);
			break;

			/* The DEPLOYED opcode is intended for the sink, nodes need to pass
			   it on and the sink has to keep track of when every node is
			   deployed, so it can begin streaming */
		case DEPLOYED:
		  diag("Recieved DEPLOYED");
		        //runfsm send_deployed;
			break;
		case STREAM:
			runfsm send_ack(get_hop_id(packet));
			if (sink) {
				diag("STREAM:%s\r\n", get_payload(packet));
				break;//deal with it as sink
			} else {
				diag("\r\nHOP PACKET!!!!!\r\n%s\r\n", get_payload(packet));
				acknowledged = NO;
				address hop_packet = umalloc(packet_length(packet) / 2 * sizeof(word));
				copy_packet(hop_packet, packet);
				runfsm stream_data(hop_packet);
			}
			break;
		case ACK://deal w/ type
		  diag("Recieved ACK\r\n");
		  //if (get_destination(packet) == my_id) {
			acknowledged = YES;
			retries = 0;
			// }
			break;
		case COMMAND:
		  diag("Recieved COMMAND\r\n");
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
		  diag("Unknown opcode\r\n");
			break;
		}
		tcv_endp(packet);
        diag("END fsm Recieve\r\n");
		proceed RECV;
}
