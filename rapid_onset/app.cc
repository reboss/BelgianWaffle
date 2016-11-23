/* ####################################################################
   CMPT 464
   Ad Hoc Network Deployment
   Authors: Aidan Bush, Elliott Sobek, Christopher Dubeau,
   John Mulvany-Robbins, Kevin Saforo
   Thursday, November 10

   File: app.cc
   Description: This file contains the menu, calls to other functions
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

#include "network.h"
#include "node_tools.h"

int sfd;
char message[30];
extern int my_id;
int receiver = 0;
word current_state;

int ping_delay = 2;//2 Seconds default

//Global that indicates if the node is the sink or not
int sink = 0; 

void init_cc1100() {
  phys_cc1100(0, 60);
  tcv_plug(0, &plug_null);
  sfd = tcv_open(WNONE, 0, 0);
}

fsm node {
    state NODE_INIT:
    if (sink) {
        //send setup packet here
        ser_out(NODE_INIT, "Sending DEPLOY packets..\r\n");
        runfsm send_deploy;
    }
}

fsm root {

	char selection = ' ';

	initial state INIT:
		init_cc1100();
		runfsm receive;
		if (sfd >= 0) {
		  tcv_control(sfd, PHYSOPT_RXON, NULL);
		  sink = 1;
		  proceed DISPLAY;
		}

	state DISPLAY:
		ser_outf(DISPLAY, "Rapid Onset; Node id (%d)\r\n"
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
			ser_outf(SELECTION, "The current ping rate is: %d\r\n", ping_delay);
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
			ser_inf(PROMPT, "%d", &ping_delay);
			ser_outf(PROMPT, "New ping: %d\r\n", ping_delay);
			selection = ' ';
			proceed DISPLAY;
			break;
		case 'P':
			ser_out(PROMPT, "Beginning Packet Deployment... \r\n");
			//TODO: Add Packet Deployment functions
			// deploy_packet();
			selection = ' ';
			proceed DISPLAY;
			break;
		case 'R':
			ser_out(PROMPT, "Beginning RSSI Deployment... \r\n");
			//TODO: Add RSSI Deployment functions
			runfsm node;
			// deploy_rssi();
			selection = ' ';
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
