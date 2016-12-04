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
int num_data = 0;

void set_power(int sfd, int power) {
    int pow = power;
    tcv_control(sfd, PHYSOPT_SETPOWER, &power);
}

void add_stream_info(address packet) {
    static num_data = 0;

    if (num_data >= NUM_TEST_MSGS) {
        if (debug >= 1)
            diag("Past max msgs for test data\r\n");
        return;
    }
    stream_info.packet_loss[num_data] = get_msgs_lost(packet);
    stream_info.seq_num[num_data] = get_seqnum(packet);
    stream_info.packet_len[num_data] = get_length(packet);
    stream_info.timestamp[num_data] = seconds();

    num_data++;
}

void print_stat_header(word state) {
    ser_outf(state, "each line is for different packets in sequential order\r\n"
            "packets lost, sequence number, packet length, timestamp (s)\r\n");
}

int print_stat_line(word state, bool restart) {
    static i = 0;
    if (debug >= 1)
        diag("print stat line\r\n");
    if (restart)
        i = 0;
    ser_outf(state, "%d,%d,%d,%d\r\n", stream_info.packet_loss[i],
            stream_info.seq_num[i], stream_info.packet_len[i],
            stream_info.timestamp[i]);
    i++;
    if (i >= num_data)
        return 1;
    return 0;
}
