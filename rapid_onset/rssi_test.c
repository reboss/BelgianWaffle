/* ####################################################################
   CMPT 464
   Ad Hoc Network Deployment
   Authors: Aidan Bush, Elliott Sobek, Christopher Dubeau,
   John Mulvany-Robbins, Kevin Saforo
   Thursday, November 10

   File: node_tools.h
   Description: The header file for node_tools.c
   ####################################################################
*/

#include "sysio.h"
#include "node_led.h"

#define RSSI_THRESHOLD  0x80//currently 0x80 is stable starts droping at 0x70
#define RSSI_LOW_CUTOFF 10

int num_cutoff(word rssi) {
    int i, low = 0;
    for (i = 0; i < 16; i++) {
        if ((rssi >> i) & 1 == 1)
            low++;
    }
    if (low >= (RSSI_LOW_CUTOFF / 2))
        set_led(LED_RED_S);
    diag("Low = %d\r\n",low);
    return low;
}

int rssi_setup_test(address packet) {
    //which packets in the last 16 droped below the rssi threshold
    static word prev_rssi = 0;
    //static bool backtrack = NO;

    prev_rssi <<= 1;
    //check rssi
    if (get_rssi(packet) < RSSI_THRESHOLD) {
        set_led(LED_RED);
        prev_rssi |= 1;
    } else {
        set_led(LED_YELLOW);
        prev_rssi &= ~1;
    }

    //if to many were low
    if (num_cutoff(prev_rssi) >= RSSI_LOW_CUTOFF) {
        return 1;
    } else {
        return 0;
    }
}


