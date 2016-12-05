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

#ifndef RSSI_TEST_H
#define RSSI_TEST_H

#include "sysio.h"
//+++ rssi_test.c

/**
 * rssi_setup_test
 *
 * Records how many on the last 16 packets dropped below the rssi threshold, and
 * returns if too many were lost.
 *
 * Args:
 * address packet - the DEPLOY packet being tested
 *
 * Returns:
 * 1 if the number of low rssi values equals or exceeds threshold
 */
int rssi_setup_test(address);

#endif /*RSSI_TEST_H*/
