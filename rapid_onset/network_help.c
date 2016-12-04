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

#include "phys_cc1100.h"
#include "tcv.h"
#include "network_help.h"

extern stream_stat stream_info;

void set_power(int sfd, int power) {
    int pow = power;
    tcv_control(sfd, PHYSOPT_SETPOWER, &power);
}

void add_stream_info(address packet, int i) {
    if (i >= NUM_TEST_MSGS) {
        if (debug >= 1)
            diag("Past max msgs for test data\r\n");
        return;
    }
    stream_info.packet_loss[i] = ;
    stream_info.seq_num[i] = get_seqnum(packet);
    stream_info.packet_len[i] = get_length(packet);
    stream_info.timestamp[i] = seconds();
}

