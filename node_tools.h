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

#ifndef NODE_TOOLS_H
#define NODE_TOOLS_H

#include "sysio.h"

//+++ "node_tools.c"

#define MAX_P 56

void set_ids(address);

int get_destination(address);

int get_source_id(address);

int get_hop_id(address);

int get_opcode(address);

int get_end(address);

int get_length(address);

int get_seqnum(address);

byte * get_payload(address packet);

int get_rssi(address);

void build_packet(address, int, int, int, int, byte *);

void copy_packet(address, address);

int packet_length(address);

#endif /*NODE_TOOLS_H*/
