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

#ifndef PACKET_TEST_H
#define PACKET_TEST_H

#include "sysio.h"
//+++ packet_test.c

/**
 * packet_setup_test
 *
 * Records how many on the last 15 packets dropped below the rssi threshold, anh
 *  returns if too many were lost.
 * Args:
 * address packet - the DEPLOY packet being tested
 *
 * Returns:
 * 1 if the number of lost packets in the last 15 packets exceeds the threshold
 */
int packet_setup_test(address);

#endif /*PACKET_TEST_H*/
