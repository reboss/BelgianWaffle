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

#ifndef NODE_LED_H
#define NODE_LED_H

#define LED_YELLOW 0
#define LED_GREEN  1
#define LED_RED    2
#define LED_RED_S  3

//+++ "node_led.c"
void set_led(int);

#endif /* End NODE_LED_H */
