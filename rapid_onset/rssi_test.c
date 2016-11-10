#include "sysio.h"

#define RSSI_THRESHOLD  80
#define RSSI_LOW_CUTOFF 10

int rssi_setup_test(address *packet) {
    //which packets in the last 16 droped below the rssi threshold
    static word prev_rssi = 0;
    
    prev_rssi <<= 1;
    //check rssi
    if (get_rssi(packet) < RSSI_THESHOLD)
        prev_rssi |= 1;
    else
        prev_rssi &= ~1;
    
    //if to many were low
    if (num_cutoff >= RSSI_LOW_CUTOFF)
        return 1;
    return 0;
}

int num_cutoff(byte rssi) {
    int i, low = 0;
    for (i = 0; i < 16; i++) {
        if ((rssi >> i) & 1 == 1)
            low++;
    }
    return low;
}


