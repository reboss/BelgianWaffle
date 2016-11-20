//+++ "node_tools.cc"

#include "sysio.h"

extern int my_id, parent, child;

void get_id(address);

int get_source(address);

int get_dest(address);

int get_hop_id(address);

int get_opcode(address);

int get_end(address);

int get_length(address);

int get_seqnum(address);

char *get_payload(address);

int get_rssi(address);

void build_packet(address, int, int, int, int, char *);
