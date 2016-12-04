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

#ifndef NETWORK_HELP_H
#define NETWORK_HELP_H

#define HIGH_POWER   1
#define LOW_POWER    0

#define NUM_TEST_MSGS 250
//+++ "network_help.c"

typedef struct _stream_stat {
    int num_elems;
    int packet_loss[NUM_TEST_MSGS];
    int seq_num[NUM_TEST_MSGS];
    int packet_len[NUM_TEST_MSGS];
    lword timestamp[NUM_TEST_MSGS];
} stream_stat;

void set_power(int sfd, int power);

#endif /*NETWORK_HELP_H*/
