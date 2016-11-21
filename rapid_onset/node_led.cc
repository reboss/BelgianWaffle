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
#include "node_led.h"

#define LED_YELLOW 0
#define LED_GREEN  1
#define LED_RED    2

#define LED_OFF    0
#define LED_ON     1

bool led_is_on = false;
int cur_state = 0;
enum states {YELLOW_FLASH, GREEN_SOLID, RED_FLASH, RED_SOLID};


fsm leds {

  /* Init switches to the needed led function based on what states is set to */ 
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
  /* CONNECTED is the state that controls the green led when the node is communicating */
	state CONNECTED:
                if(!led_is_on) {
	                leds(LED_GREEN, LED_ON);
	                led_is_on = true;
	        }
	        delay(25, INIT);
	        release;

  /* CONNECTING is the state that controls the flashing yellow led as the node attemps to   connect to the network
  */
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
  
  /* CHECKING is the state that controls the flashing red led as the node ch  ecks its con  nection to the sinc 
  */
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
  
  /* DISCONNECTED is the state that controls the solid red led that indicates the node has  lost connection to the network after deployment
  */
	state DISCONNECTED:
	        if(!led_is_on) {
	                leds(LED_RED, LED_ON);
	                led_is_on = true;
	        }
	        delay(25, INIT);
	        release;
}
