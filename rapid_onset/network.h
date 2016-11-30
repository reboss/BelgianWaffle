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

#define MAP_P 56

#define RSSI_TEST   1
#define PACKET_TEST 2

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

#define DONE diag("\r\nDone\r\n")

void receive(word __pi_st);

void send_ping(word __pi_st);

void send_deploy(word __pi_st);

#endif /* End NETWORK_H */
