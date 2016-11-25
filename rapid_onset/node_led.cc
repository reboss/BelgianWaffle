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

#define FALSE      0
#define TRUE       1

bool led_is_on = FALSE;
int cur_state = 0;
enum states {YELLOW_FLASH, GREEN_SOLID, RED_FLASH, RED_SOLID};
enum states led_state = YELLOW_FLASH;

void set_states(int cur_state) {
        switch(cur_state) {
        case 0:
                led_state = YELLOW_FLASH;
                break;
        case 1:
                led_state = GREEN_SOLID;
                break;
        case 2:
                led_state = RED_FLASH;
                break;
        case 3:
                led_state = RED_SOLID;
                break;
        }
}

fsm node_leds {

        /* Init switches to the needed led function based on what states is set to */
        initial state INIT:
            if (cur_state != led_state) {
                cur_state = led_state;
                leds_all(LED_OFF);
            }

        switch(led_state) {
        case GREEN_SOLID:
            proceed CONNECTED;
            break;
        case YELLOW_FLASH:
            proceed CONNECTING;
            break;
        case RED_FLASH:
            proceed CHECKING;
            break;
        case RED_SOLID:
            proceed DISCONNECTED;
            break;
        default:
            break;
        }
    /* CONNECTED is the state that controls the green led when the node is
       communicating
    */
    state CONNECTED:
                if (!led_is_on) {
                    leds(LED_GREEN, LED_ON);
                    led_is_on = TRUE;
                }
            delay(25, INIT);
            release;

    /* CONNECTING is the state that controls the flashing yellow led as the node
     *  attemps to   connect to the network
     */
    state CONNECTING:
            if (led_is_on) {
                    leds(LED_YELLOW, LED_OFF);
                    led_is_on = FALSE;
            } else {
                    leds(LED_YELLOW, LED_ON);
                    led_is_on = TRUE;
            }
            delay(100, INIT);//should be defined not magic
            release;

    /* CHECKING is the state that controls the flashing red led as the node
     *  checks its con  nection to the sink
     */
    state CHECKING:
            if (led_is_on) {
                    leds(LED_RED, LED_OFF);
                    led_is_on = FALSE;
            } else {
                    leds(LED_RED, LED_ON);
                    led_is_on = TRUE;
            }
            delay(100, INIT);
            release;

    /* DISCONNECTED is the state that controls the solid red led that indicates the node has  lost connection to the network after deployment
    */
    state DISCONNECTED:
            if (!led_is_on) {
                    leds(LED_RED, LED_ON);
                    led_is_on = TRUE;
            }
            delay(25, INIT);
            release;
}
