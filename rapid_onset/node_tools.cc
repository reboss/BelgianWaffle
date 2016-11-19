/* ####################################################################
   CMPT 464
   Ad Hoc Network Deployment
   Authors: Aidan Bush, Elliott Sobek, Christopher Dubeau,
   John Mulvany-Robbins, Kevin Saforo
   Thursday, November 10

   File: node_tools.cc
   Description: This file contains helper network functions.
   ####################################################################
*/
#include <string.h>

#include "sysio.h"

#define MAX_P 56

extern int my_id, parent_id, child_id;

void get_id(address packet) {
  my_id = (packet[1] >> 8) & 15;
  parent_id = (packet[1] >> 12) & 15;
  child_id = my_id + 1;
}

int get_source(address packet) {
    return packet[1] & 15;
}

int get_dest(address packet) {
    return (packet[1] >> 4) & 15
}

int get_hop_id(address packet) {
  int hop_id = (packet[1] >> 4) & 15;
  return hop_id;
}

int get_opcode(address packet) {
  int opcode = (packet[1]) & 15;
  return opcode;
}

int get_length(address packet) {
  int length = (packet[2] << 2) >> 10;
  return length;
}

int get_seqnum(address packet) {
  int seqnum = (packet[2] << 8) >> 8;
  return seqnum;
}

int get_rssi(address packet) {
  int length = (3 + (get_length(packet) / 2));
  int rssi = packet[length] >> 8;
  return rssi;
}

void build_packet(address packet, int source_id, int destination, int opcode,
                  int seqnum, char * payload) {
  packet[1] = source_id << 12 | destination << 8 | my_id << 4 | opcode;
  if(payload){
    int length = strlen(payload) + 1;
    packet[2] = 1 << 14 | ((length + (length % 2)) << 8) | seqnum;
    strncpy((char *) (packet + 3), payload, MAX_P);
  }
  else {
    packet[2] = 1 << 14 | seqnum;
  }
}
