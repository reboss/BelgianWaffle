#include "sysio.h"

#define RSSI_THRESHOLD  0xF0
#define RSSI_LOW_CUTOFF 10

int num_cutoff(word rssi) {
    int i, low = 0;
    for (i = 0; i < 16; i++) {
        if ((rssi >> i) & 1 == 1)
            low++;
    }
    diag("num low: %x\r\n", low);
    return low;
}

int rssi_setup_test(address packet) {
    //which packets in the last 16 droped below the rssi threshold
    static word prev_rssi = 0;
    diag("prev_rssi: %x\r\n", prev_rssi);
    prev_rssi <<= 1;
    //check rssi
    if (get_rssi(packet) < RSSI_THRESHOLD)
        prev_rssi |= 1;
    else
        prev_rssi &= ~1;
    
    //if to many were low
    if (num_cutoff(prev_rssi) >= RSSI_LOW_CUTOFF) {
        diag("low rssi\r\n");
        return 1;
    }
    return 0;
}


