



#include "sysio.h"
#include "serf.h"
#include "ser.h"
#include "plug_null.h"
#include "tcvphys.h"
#include "phys_cc1100.h"
#include "node_tools.h"

#define MAX_P 56

extern int my_id, parent, child;


void set_ids(address packet) {
        my_id = (packet[1] >> 8) & 15;
        parent = (packet[1] >> 12) & 15;
        child = my_id + 1;
}

int get_destination(address packet) {
        int destination = (packet[1] >> 8) & 15;
        return destination;
}

int get_source_id(address packet) {
        int source_id = packet[1] >> 12;
        return source_id;
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

void build_packet(address packet, int source_id, int destination, int opcode, int seqnum, char * payload) {
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
