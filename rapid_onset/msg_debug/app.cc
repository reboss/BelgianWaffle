#include "sysio.h"
#include "serf.h"

#include "phys_cc1100.h"
#include "plug_null.h"
#include "tcv.h"

#include "../node_tools.h"

init_cc1100() { 
    phys_cc1100(0, 60);
    tcv_plug(0, &plug_null);
    sfd = tcv_open(WNONE, 0, 0);
} 

fsm reciever {
    static address packet;
    static sint plength;
    
    static int source, dest, hop, opcode;
    static int end, len, seq;
    static char[MAX_P +1] payload;
    static int rssi;
    
    inital state RE_RECV:
        packet = tcv_rnp(RE_RECV, sfd);
        plength = tcv_left(packet);
        proceed(RE_SETUP);
    
    state RE_SETUP:
        source = get_source(packet);
        dest = get_dest(packet);
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
        ser_outf(RE_PRINT, "word 1:\r\n"
            "  source: %x\r\n"
            "  dest:   %x\r\n"
            "  hop:    %x\r\n"
            "  opcode: %x\r\n"//conver to string?
            "word 2:\r\n"
            "  end:    %x\r\n"
            "  len:    %x\r\n"
            "  seqnum: %x\r\n"
            "payload:\r\n"
            "  |%s|\r\n"
            "rssi:     %x\r\n",
            source, dest, hop, opcode, end, len, seq, payload, rssi);
        proceed(RE_RECV);
        
}

fsm root {
    initial state R_INIT:
        init_cc1100();
        runfsm reciever;
        finish;
}
