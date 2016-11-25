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

#include "sysio.h"
#include "serf.h"
#include "ser.h"
#include "node_tools.h"

#define MAX_P 56

int my_id, parent_id, child_id, dest_id;

/* set_ids() is used during deployment to set the nodes own id, its
   parents id and its childs id
*/
void set_ids(address packet) {
        my_id = (packet[1] >> 8) & 15;
        parent_id = (packet[1] >> 12) & 15;
        child_id = my_id + 1;
}

/* get_destination() takes in a packet and returns the int value of
   the destination node for the packet
*/
int get_destination(address packet) {
        return (packet[1] >> 4) & 15;
}

/* get_source_id() takes in a packet and returns the int value of
   the node that the packet originates from
*/
int get_source_id(address packet) {
        return packet[1] & 15;
}

/* get_hop_id() takes in a packet and returns the int value of the
   node that last relayed the packet
*/
int get_hop_id(address packet) {
        return (packet[1] >> 8) & 15;
}

/* get_opcode() takes in a packet and returns the int value of the
   operation code that coresponds to the packet
*/
int get_opcode(address packet) {
        return (packet[1] >> 12) & 15;
}

/* get_end() returns the end bit of the packet
 */
int get_end(address packet) {
    return (packet[2] >> 1) & 1;
}

/* get_length() takes in a packet and returns the int value of the
   length of the message in the packet (in bytes)
*/
int get_length(address packet) {
        return (packet[2] >> 2) & 63;
}

/* get_seqnum() takes in a packet and returns the int value that
   represents the packets position in a message
*/
int get_seqnum(address packet) {
        return (packet[2] >> 8) & 255;
}

char * get_payload(address packet) {
    return packet + 2;
}

/* get_rssi() takes in a packet and returns the rssi value as an
   int
*/
int get_rssi(address packet) {
        int length = (3 + (get_length(packet) / 2));
        return (packet[length] >> 8) & 255;
}

/* build_packet() takes in the components of a package and assembles
   it into a full package at the address it was sent
*/
void build_packet(address packet, int source_id, int destination,
                  int opcode, int seqnum, char * payload) {
    packet[1] = source_id | destination << 4 | my_id << 8 | opcode << 12;
    if(payload){
        int length = strlen(payload);
        packet[2] = 1 << 1 | length << 2 | seqnum << 8;
        strncpy((char *) (packet + 3), payload, MAX_P);
    } else {
        packet[2] = 1 << 1 | seqnum << 12;
    }
}
