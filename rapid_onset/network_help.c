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

#include "phys_cc1100.h"
#include "tcv.h"

#include "network_help.h"

void set_power(int sfd, int power) {
    tcv_control(sfd, PHYSOPT_SETPOWER, power);
}

