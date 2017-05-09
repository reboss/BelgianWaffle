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

//+++ "node_led.c"

#define LED_YELLOW   0
#define LED_GREEN    1 
#define LED_RED      2
#define LED_RED_S    3
#define LED_GREEN_S  4
#define LED_YELLOW_S 5

#define LED_OFF      0
#define LED_ON       1
#define LED_BLINK    2

void set_led(int);

#endif /* End NODE_LED_H */
