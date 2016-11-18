/* ####################################################################
   CMPT 464
   Ad Hoc Network Deployment
   Authors: Aidan Bush, Elliot Sobek, Christopher Dubeau,
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

#define LED_YELLOW 0
#define LED_GREEN  1
#define LED_RED    2

#define LED_OFF    0
#define LED_ON     1

bool led_is_on = false;
int cur_state = 0;
enum states {YELLOW_FLASH, GREEN_SOLID, RED_FLASH, RED_SOLID};

fsm leds {

        initial state INIT:
	        if(cur_state != states){
		        cur_state = states;
			leds_all(LED_OFF);
		}
		
		switch(states) {
		        case GREEN_SOLID:
			        proceed CONNECTED;
		        case YELLOW_FLASH:
		                proceed CONNECTING;
		        case RED_FLASH:
		                proceed CHECKING;
		        case RED_SOLID:
		                proceed DISCONNECTED;
		}

	state CONNECTED:
                if(!led_is_on) {
	                leds(LED_GREEN, LED_ON);
	                led_is_on = true;
	        }
	        delay(25, INIT);
	        release;


	state CONNECTING:
	        if(led_is_on) {
	                leds(LED_YELLOW, LED_OFF);
	                led_is_on = false;
	        }
	        else{
	                leds(LED_YELLOW, LED_ON);
	                led_is_on = true;
	        }
	        delay(100, INIT);
	        release;

	state CHECKING:
	        if(led_is_on) {
	                leds(LED_RED, LED_OFF);
	                led_is_on = false;
	        }
	        else{
	                leds(LED_RED, LED_ON);
	                led_is_on = true;
	        }
	        delay(100, INIT);
	        release;

	state DISCONNECTED:
	        if(!led_is_on) {
	                leds(LED_RED, LED_ON);
	                led_is_on = true;
	        }
	        delay(25, INIT);
	        release;
