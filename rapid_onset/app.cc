/* ####################################################################
   CMPT 464
   Ad Hoc Network Deployment
   Authors: Aidan Bush, Elliot Sobek, Christopher Dubeau, 
   John Mulvany-Robbins, Kevin Saforo
   Thursday, November 10

   File: App.cc
   Description: The contains the menu, and calls to other functions 
   for the deployment of an ad hoc network, and the streaming of data
   through nodes.
   ####################################################################
*/


#include "sysio.h"
#include "serf.h"
#include "ser.h"
#include "plug_null.h"
#include "tcvphys.h"
#include "phys_cc1100.h"

int sfd;
char message[30];
int my_id = 1;
int receiver = 0;
word current_state;
int ping = 2; //2 Seconds default

fsm root {

	char selection = ' ';

	initial state INIT:
		phys_cc1100(0, 60);
	        tcv_plug(0, &plug_null);
		sfd = tcv_open(WNONE, 0, 0);
		tcv_control(sfd, PHYSOPT_RXON, NULL);
		runfsm receive;
		proceed DISPLAY;
	
	
	state DISPLAY:
		ser_outf(DISPLAY, "Rapid Onset Menu\r\n"
			"(C)hange Ping Rate\r\n"
			"(P)acket Deployment\r\n"
			"(R)SSI Deployment\r\n"
			"(S)ink Status\r\n"
			"Selection: ",
			my_id);
 
	        proceed SELECTION;

	state SELECTION:
		switch (selection) {
		case 'C':
			//TODO: Add ping rate to the ser_out call
			ser_outf(SELECTION, "The current ping rate is: %d\r\n", ping);
			proceed PROMPT;
			break;
		case 'P':
			selection = 'P';
			proceed PROMPT;
			break;
		case 'R':
			selection = 'R';
			proceed PROMPT;
 			break;
		case 'S':
			selection = 'S';
			proceed PROMPT;
			break;
		default:
			ser_inf(SELECTION, "%c", &selection);
			proceed PROMPT;
			break;
		}
		proceed PROMPT;
		release;

	state PROMPT:
		switch (selection) {
		case 'C':
			//TODO: Set ping rate
			ser_inf(PROMPT, "%d", &ping);
			ser_outf(PROMPT, "New ping: %d\r\n", ping);
			selection = ' ';
			proceed DISPLAY;
			break;
		case 'P':
			ser_out(PROMPT, "Beginning Packet Deployment... \r\n");
			//TODO: Add Packet Deployment functions
			selection = ' ';
			proceed DISPLAY;
			break;
		case 'R':
			ser_out(PROMPT, "Beginning RSSI Deployment... \r\n");
			//TODO: Add RSSI Deployment functions
			selection = ' ';
			proceed DISPLAY;
			break;
		case 'S':
			ser_out(PROMPT, "Checking Sink Status... \r\n");
			//TODO: Do we need this?
			selection = ' ';
			proceed DISPLAY;
			break;
		default:
			selection = ' ';
			proceed DISPLAY;
			break;
		
		}
}

