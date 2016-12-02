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

#define RSSI_TEST   1
#define PACKET_TEST 2

//+++ "network.cc"

bool is_lost_con_retries(void);

bool is_lost_con_ping(int ping_retries);

bool is_last_node(void);

void final_deploy(word __pi_st);

void detrm_fsm_deploy_behvr(void);

bool send_stop(word __pi_st, int dest);

void set_test_mode_data(address packet);

void set_test_behaviour(address packet);

void send_deploy(word __pi_st);

void send_ack(word __pi_st, int dest);

void stream_data(word __pi_st, address packet_copy);

void indicate_reset(word __pi_st);

void send_pong(word __pi_st);

void send_ping(word __pi_st);

void receive(word __pi_st);

#endif /* End NETWORK_H */
