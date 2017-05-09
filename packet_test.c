/* ####################################################################
   CMPT 464
   Ad Hoc Network Deployment
   Authors: Aidan Bush, Elliott Sobek, Christopher Dubeau,
   John Mulvany-Robbins, Kevin Saforo
   Thursday, November 10

   File: node_tools.h
   Description: The header file for node_tools.c
   ####################################################################
*/

#include "sysio.h"
#include "node_led.h"

#define PACKET_LOSS_THRESHOLD 4

int num_lost(word losses) {
    int i, lost = 0;
    for (i = 0; i < 15; i++) {
        if ((losses >> i) & 1 == 1)
            lost++;
    }
    return lost;
}

int packet_setup_test(address packet) {
    static int last_seq;//seq of last recieved packet
    static word prev_lost = 0;//last 15 packets and a setup bit
    int i;
    int cur_seq = get_seqnum(packet);
    if (prev_lost == 0){
        last_seq = cur_seq;
        prev_lost = 1 << 15;
        return 0;
    }
    set_led(LED_YELLOW);

    //deal with lost packets
    for (i = 0; i < (cur_seq - last_seq - 1); i++) {
        set_led(LED_RED);
        prev_lost = (prev_lost << 1) | 1;//add lost packet
        diag("packet lost");
    }
    last_seq = cur_seq;
    //deal with current since its valid
    prev_lost <<= 1;
    prev_lost &= ~1;
    prev_lost |= 1 << 15;

    if (num_lost(prev_lost) >= PACKET_LOSS_THRESHOLD) {
        return 1;
    }
    return 0;
}
