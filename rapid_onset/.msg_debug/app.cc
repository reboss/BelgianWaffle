#include "sysio.h"
#include "serf.h"
#include "ser.h"

#include "plug_null.h"
#include "tcv.h"
#include "phys_cc1100.h"

#include "node_tools.h"

#define MAX_P 56 /*from node_tools.cc*/

int my_id, parent_id, child_id;//needed for node_tools to work

int sfd;

init_cc1100() { 
    phys_cc1100(0, 60);
    tcv_plug(0, &plug_null);
    sfd = tcv_open(WNONE, 0, 0);
    tcv_control(sfd, PHYSOPT_ON, NULL);
} 

fsm root {
    address packet;
    sint plength;
    
    int source, dest, hop, opcode;
    int end, len, seq;
    char payload[MAX_P +1];
    int rssi;
    
    initial state R_INIT:
        init_cc1100();
        diag("radio setup\r\n");
        proceed(RE_RECV);
    
    state RE_RECV:
        diag("before tvc_rnp\r\n");
        packet = tcv_rnp(RE_RECV, sfd);
        diag("\r\nRECIEVED PACKET\r\n");
        plength = tcv_left(packet);
        proceed(RE_SETUP);
    
    state RE_SETUP:
        diag("RE_SETUP start\r\n");
        source = get_source_id(packet);
        dest = get_destination(packet);
        hop = get_hop_id(packet);
        opcode = get_opcode(packet);
        
        end = get_end(packet);
        len = get_length(packet);
        seq = get_seqnum(packet);
        
        strcpy(payload, get_payload(packet));
        payload[MAX_P] = '\0';
        
        rssi = get_rssi(packet);
        proceed(RE_PRINT);
        
    state RE_PRINT:
        ser_outf(RE_PRINT, "word 1: %x\r\n"
            "  source: %x\r\n"
            "  dest:   %x\r\n"
            "  hop:    %x\r\n"
            "  opcode: %x\r\n"//conver to string?
            "word 2: %x\r\n"
            "  end:    %x\r\n"
            "  len:    %x\r\n"
            "  seqnum: %x\r\n"
            "payload:\r\n"
            "  |%s|\r\n"
            "rssi:     %x\r\n",
            packet[1], source, dest, hop, opcode, packet[2], end, len, seq,
            payload, rssi);
        proceed(RE_RECV);
        
}
