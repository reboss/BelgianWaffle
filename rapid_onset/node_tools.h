#include "sysio.h"
#include "serf.h"
#include "ser.h"
#include "plug_null.h"
#include "tcvphys.h"
#include "phys_cc1100.h"

extern int my_id, parent, child;

void get_id(address);

int get_hop_id(address);

int get_opcode(address);

int get_length(address);

int get_seqnum(address);

int get_rssi(address);

void build_packet(address, int, int, int, int, char *);
