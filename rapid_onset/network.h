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

#define RSSI_TEST       1
#define PACKET_TEST     2

#define TRUE            1
#define FALSE           0

#define TRUE       1
#define FALSE      0

void receive(word __pi_st);

void send_ping(word __pi_st);

void send_deploy(word __pi_st);

#endif /* End NETWORK_H */
