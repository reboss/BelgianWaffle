#include "sysio.h"
#include "serf.h"
#include "ser.h"
#include "plug_null.h"
#include "tcvphys.h"
#include "phys_cc1100.h"

#define MAX_P 56

void set_ids(address packet);
int get_destination(address packet);
int get_source_id(address packet);
int get_hop_id(address packet);
int get_opcode(address packet);
int get_length(address packet);
int get_seqnum(address packet);
int get_rssi(address packet);
void build_packet(address packet, int source_id, int destination, int opcode, int seqnum, char * payload);
