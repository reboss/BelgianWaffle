/* ####################################################################
   CMPT 464
   Ad Hoc Network Deployment
   Authors: Aidan Bush, Elliott Sobek, Christopher Dubeau,
   John Mulvany-Robbins, Kevin Saforo
   Friday, November 18

   File: led.cc
   Description: This file contains the leds fsm that controls the
   led indicator. The led flashed Yellow during depolyment, flashes
   red when checking the sinc, stays solid green when connected
   and stays red when disconnected
   ####################################################################
*/

#include "sysio.h"
#include "serf.h"
#include "ser.h"
#include "plug_null.h"
#include "tcvphys.h"
#include "phys_cc1100.h"
#include "node_led.h"

#define LED_YELLOW 0
#define LED_GREEN  1
#define LED_RED    2

#define LED_OFF    0
#define LED_ON     1

bool led_is_on = NO;
int cur_state = 0;

//Inplement into .h? then dont send it literal 0,1,2,3
//enum states {YELLOW_FLASH, GREEN_SOLID, RED_FLASH, RED_SOLID};
//enum states led_state = YELLOW_FLASH;

void set_led(int cur_state) {
        leds_all(LED_OFF);
        switch(cur_state) {
        case 0:
	        leds(LED_YELLOW,LED_ON);
		fastblink(YES);
                break;
        case 1:
	        leds(LED_GREEN,LED_ON);
                break;
        case 2:
	        leds(LED_RED,LED_ON);
		fastblink(YES);
                break;
        case 3:
	        leds(LED_RED,LED_ON);
                break;
        }
}
