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

/* test files */
#include "rssi_test.h"
#include "packet_test.h"

extern int my_id, sfd;
extern bool deployed;
char message[30];
int receiver = 0, test;
word current_state;

int ping_delay = 2000;//2 Seconds default


//Global that indicates if the node is the sink or not
int sink = 0;


void init_cc1100() {
    phys_cc1100(0, 60);
    tcv_plug(0, &plug_null);
    sfd = tcv_open(WNONE, 0, 0);
    tcv_control(sfd, PHYSOPT_ON, NULL);
}

fsm root {

    char selection = '\0';

    initial state INIT:
        init_cc1100();
        leds_all(0);
        runfsm receive;
	proceed DISPLAY;

    state DISPLAY:
        ser_outf(DISPLAY, "Rapid Onset; Node id (%d)\r\n"
          "(C)hange Ping Rate\r\n"
          "(P)acket Deployment\r\n"
          "(R)SSI Deployment\r\n"
          "(S)et Number of Nodes: (%d)\r\n"
          "Selection: ",
	  my_id, max_nodes);
        proceed SELECTION;

    state SELECTION:
        ser_inf(SELECTION, "%c", &selection);
        proceed PROMPT;

	state PROMPT:
        switch (selection) {
        case 'C':
            proceed PING_PROMPT;
            break;
        case 'P':
            if (sink) {
                diag("This node is already the sink\r\n");
                break;
            }
            diag("Beginning Packet Deployment...\r\n");
            sink = 1;
            deployed = TRUE;
			test = PACKET_TEST;
            runfsm send_deploy(test);
            break;
        case 'R':
            if (sink) {
                diag("This node is already the sink\r\n");
                break;
            }
            diag("Beginning RSSI Deployment...\r\n");
            sink = 1;
            deployed = TRUE;
			test = RSSI_TEST;
            runfsm send_deploy(test);
            break;
        case 'S':
            proceed NODE_PROMPT;
            break;
        default:
            break;
        }
        proceed DISPLAY;

    state PING_PROMPT:
        ser_outf(PING_PROMPT, "Enter new ping delay in milliseconds: ");
        proceed PING_SELECT;

    state PING_SELECT:
        ser_inf(PROMPT, "%d", &ping_delay);
        proceed PING_CONFIRM;

    state PING_CONFIRM:
        ser_outf(PING_CONFIRM, "New ping delay %d\r\n\r\n", ping_delay);
        proceed DISPLAY;
	
    state NODE_PROMPT:
        ser_outf(PING_PROMPT, "Enter new number of nodes: ");
	proceed PING_SELECT;

    state NODE_SELECT:
        ser_inf(PROMPT, "%d", &max_nodes);
        proceed PING_CONFIRM;

    state NODE_CONFIRM:
        ser_outf(PING_CONFIRM, "New max nodes: %d\r\n\r\n", max_nodes);
        proceed DISPLAY;


}
