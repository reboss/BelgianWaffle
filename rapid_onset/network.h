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

/**
 * is_lost_con_retries
 * 
 * Checks if the number of ACK retries has reached the maximum and
 * returns a boolean value.
 *
 * Returns:
 * YES if the number of tries has reached the maximum.
 *
 */
bool is_lost_con_retries(void);

/**
 * is_lost_con_ping
 *
 * Checks if the number ping retries has reached the maximum and
 * returns a boolean value.
 * 
 * Returns:
 * YES if the number of retries has reached the maximum.
 *
 */
bool is_lost_con_ping(int ping_retries);

/**
 * is_last_node
 *
 * Checks if the node is the last node declared in app.cc.
 *
 * Returns:
 * YES if the id of the node is equal to the last node.
 *
 */
bool is_last_node(void);

/**
 * final_deploy
 *
 * A finite state machine that sends a message from the source
 * to the sink when the network is fully deployed.
 *
 */
void final_deploy(word __pi_st);

/**
 * detrm_fsm_deploy_bevhr
 * 
 * A function that decides which deployment behaviour to use.
 * See send_deploy and final_deploy.
 *
 */

void detrm_fsm_deploy_behvr(void);

/**
 * send_stop
 * 
 * A finite state machine that sends a packet with opcode STOP
 * to the node's parent.
 *
 * Args:
 * int dest - the ID of the node the packet is intended for.
 *
 */
void send_stop(word __pi_st);

/**
 * set_test_mode_data
 * 
 * A function that initializes the ids, sequence number, and
 * deploy status of a node.
 *
 * Args:
 * address packet - A DEPLOY packet received from the nodes parent.
 *
 */
void set_test_mode_data(address packet);

/**
 * set_test_behaviour
 * 
 * A function that checks the deployment method, and calls the appropriate
 * deployment fsm. 
 *
 * Args:
 * address packet - A DEPLOY packet received from the nodes parent.
 *
 */
void set_test_behaviour(address packet);

/**
 * send_deploy
 * 
 * A finite state machine that repeatedly sends DEPLOY packets to the parent
 * until the parents sends a STOP packet.
 *
 */
void send_deploy(word __pi_st);

/**
 * send_ack
 * 
 * Sends an ACK packet to a node.
 * 
 * Args:
 * int dest - The ID of the node the packet is intended for.
 *
 */
void send_ack(word __pi_st);

/**
 * stream_data
 *
 * A finite state machine that sends a STREAM packet to 
 * the destination node.
 *
 * Args:
 * address packet_copy - A copy of the packet that will be sent.
 *
 */
void stream_data(word __pi_st);

/**
 * indicate_reset
 *
 * A finite state machine that cycles through the LEDs constantly. Indicates
 * that the node has lost connection and needs to be restarted.
 *
 */
void indicate_reset(word __pi_st);

/**
 * send_pong
 * 
 * A finite state machine that sends a PONG packet to the nodes parent.
 *
 */ 
void send_pong(word __pi_st);

/**
 * send_ping
 * 
 * A finite state machine that sends a PING packet to the nodes child.
 * If a pong has not been replied after MAX_RETRY times, the node is
 * shutdown. This will cascade and shutdown all subsequent nodes.
 *
 */
void send_ping(word __pi_st);

/**
 * receive
 * 
 * A finite state machine that listens for packets, and evaluates them. It make
 * several calls to functions and other finite state machines depending on 
 * what the packet contains.
 *
 */
void receive(word __pi_st);

#endif /* End NETWORK_H */
