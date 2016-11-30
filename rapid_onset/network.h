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

#ifndef NETWORK_H
#define NETWORK_H

//+++ "network.cc"

#define RSSI_TEST   1
#define PACKET_TEST 2

#define MAP_P 56

#define PING_LEN     10
#define STOP_LEN     10
#define ACK_LEN      10
#define DEPLOY_LEN   10
#define DEPLOYED_LEN 18
#define MAX_RETRY    10

#define PING     1
#define DEPLOY   2
#define COMMAND  3
#define STREAM   4
#define ACK      5
#define DEPLOYED 6
#define STOP     7
#define KILL     8

#define DONE diag("\r\nDone\r\n")

#define LED_YELLOW 0
#define LED_GREEN  1
#define LED_RED    2
#define LED_RED_S  3

#define SINK_ID 0

#define MILLISECOND 100
#define SECOND 1000

void receive(word __pi_st);

void send_ping(word __pi_st);

void send_deploy(word __pi_st);

#endif /* End NETWORK_H */
