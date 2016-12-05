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
#include "sysio.h"

#include "network_help.h"
#include "node_tools.h"

extern stream_stat stream_info;
extern int debug;

void set_power(int sfd, int power) {
    int pow = power;
    tcv_control(sfd, PHYSOPT_SETPOWER, &power);
}

void add_stream_info(address packet) {
    static i = 0;

    diag("%d,%d,%d,%d\r\n", get_msgs_lost(packet), get_seqnum(packet),
				get_length(packet), seconds());
    if (i == 0)
        stream_info.num_elems = 0;

    if (i >= NUM_TEST_MSGS) {
        if (debug >= 1)
            diag("Past max msgs for test data\r\n");
        return;
    }
    if (i != 0 && get_seqnum(packet) == stream_info.seq_num[i - 1]) {
        return;
    }
    stream_info.packet_loss[i] = get_msgs_lost(packet);
    stream_info.seq_num[i] = get_seqnum(packet);
    stream_info.packet_len[i] = get_length(packet);
    stream_info.timestamp[i] = seconds();

    stream_info.num_elems++;
    i++;
}
