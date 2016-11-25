#ifndef RSSI_TEST_H
#define RSSI_TEST_H

#include "sysio.h"
//+++ rssi_test.c

/* Records how many on the last 16 packets dropped below the rssi threshold, and
 *  returns if too many were lost.
 * Parameters: the packet address being assessed
 * Return: 1 if the number of low rssi values equals or exceeds threshold
 */
int rssi_setup_test(address);

#endif /*RSSI_TEST_H*/
