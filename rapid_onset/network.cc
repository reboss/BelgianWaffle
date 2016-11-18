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

#include <stdbool.h>
#include <string.h>

#include "sysio.h"
#include "serf.h"
#include "ser.h"
#include "plug_null.h"
#include "tcvphys.h"
#include "phys_cc1100.h"

#include "node_tools.h"
#include "packet_test.h"
#include "rssi_test.h"

#define MAX_P     56
#define PING_LEN  2
#define ACK_LEN   2
#define MAX_RETRY 10

#define PING      1
#define DEPLOY    2
#define COMMAND   3
#define STREAM    4
#define ACK       5
#define DEPLOYED  6

#define LED_RED 0
#define LED_GREEN 1
#define LED_YELLOW 2

char payload[MAX_P];
bool ack = true, pong;
extern int ping_delay;
int seq = 0;
extern int sfd;
int retries = 0;//retries should be static for the fsm
int my_id = 2, parent_id = 1, child_id = 3;

// does this have to be called asynchronously?
fsm setup {

    initial state SETUP:
        finish;
}

/*
   sends the same packet continuously until an ack is received.
   After 10 retries, lost connection is assumed.
*/
fsm stream_data {

    initial state SEND:
        if (ack)
            finish;
        if (is_lost_con_retries())
            leds(LED_RED, 1);
    	address packet;
    	sint plen = strnlen(payload, MAX_P);
        packet = tcv_wnp(SEND, sfd, plen);
    	build_packet(packet, my_id, parent_id, STREAM, seq, payload);
    	tcv_endp(packet);
    	retries++;
    	seq++;
}

fsm send_pong {

    initial state SEND:
        address packet;
        packet = tcv_wnp(SEND, sfd, PING_LEN);
        build_packet(packet, my_id, parent, PING, seq, NULL);
        finish;
}

fsm send_ping {

    int ping_sequence = 0;
    int ping_retries = 0;
    int dest_id = 0;//need to set dest id
    initial state SEND:
        if (pong) {
            ping_sequence++;
            ping_retries = 0;
        }
        else
            ping_retries++;
        if (is_lost_con_ping(ping_retries))
            leds(LED_RED, 1);
        
        pong = false;
        address packet;
        packet = tcv_wnp(SEND, sfd, PING_LEN);
        build_packet(packet, my_id, dest_id, PING, ping_sequence, NULL);
        delay(2000, SEND);//should use define not magic number
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
            if (get_hop_id(packet) < my_id)
                runfsm send_pong;
            else
                pong = true;
            break;
        case DEPLOY:
            runfsm setup;
            break;
        case DEPLOYED:
            // my_id++;
            // parent_id++;
            send_deployed_status();
            break;
        case STREAM:
            // check sequence number for lost ack
            // check if packet has reached it's destination
            ack = false;
            strncpy(payload, (char *) packet + 3, MAX_P);
            runfsm stream_data;
            //runfsm send_ack;
            break;
        case ACK:
            ack = true;
            retries = 0;
            break;
        case COMMAND:
            break;
        default:
            break;
        }
}

fsm send_ack {

    // ack sequence will match packet it is responding to
    int ack_seq = 0;
    int dest = 0;//what is it sending it to?
    initial state SEND:
        address packet = tcv_wnp(SEND, sfd, ACK_LEN);
        build_packet(packet, my_id, dest, ACK, ack_seq, NULL);
        tcv_endp(packet);
        finish;
}

// Tell parent to shutup
void send_deployed_status() {
    return;
}

int is_lost_con_retries() {
    return retries >= MAX_RETRY;
}

int is_lost_con_ping(int ping_retries) {
    return ping_retries == MAX_RETRY;
}
