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

void set_ids(address packet);
int get_destination(address packet);
int get_source_id(address packet);
int get_hop_id(address packet);
int get_opcode(address packet);
int get_length(address packet);
int get_seqnum(address packet);
int get_rssi(address packet);
void build_packet(address packet, int source_id, int destination, int opcode, int seqnum, char * payload);
