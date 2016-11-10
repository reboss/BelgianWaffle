#include "sysio.h"

#define PACKET_LOSS_THRESHOLD 8

int packet_setup_test(address *packet) {
    static int last_seq = 0;//deal with initial setup
    static word prev_lost;//last 15 packets and a setup bit
    int i;
    int cur_seq = get_seqnum(packet);
    
    if (prev_lost == 0){
        last_seq = cur_seq;
        prev_lost = 1 << 15;
        return 0;
    }
    //deal with lost packets
    for (i = 0; i < (cur_seq - last_seq - 1); i++) {
        prev_lost = (prev_lost << 1) | 1;//add lost packet
    }
    //deal with current since its valid
    prev_lost <<= 1;
    prev_lost &= ~1;
    
    if (num_lost(prev_lost) >= PACKET_LOSS_THRESHOLD)
        return 1;
    return 0;
}


int num_lost(word losses) {
    int i, lost = 0;
    for (i = 0; i < 15; i++) {
        if ((losses >> i) & 1 == 1)
            lost++;
    }
    return lost;
}


