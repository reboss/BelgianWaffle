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

#define PACKET_TEST 1
#define RSSI_TEST 2

int sfd;
char message[30];
extern int my_id;
int receiver = 0;
word current_state;

int ping_delay = 2000;//2 Seconds default

//Global that indicates if the node is the sink or not
int sink = 0;

extern int (*test_func)(address *);

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
        runfsm receive;

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
        ser_inf(SELECTION, "%c", &selection);
        proceed PROMPT;

	state PROMPT:
        switch (selection) {
        case 'C':
            proceed PING_PROMPT;
            break;
        case 'P':
            if (sink) {
                ser_out(PROMPT, "This node is already the sink\r\n");
                break;
            }
            ser_out(PROMPT, "Beginning Packet Deployment...\r\n");
            test_func = &packet_setup_test;
            sink = 1;
            runfsm send_deploy(PACKET_TEST);
            break;
        case 'R':
            if (sink) {
                ser_out(PROMPT, "This node is already the sink\r\n");
                break;
            }
            ser_out(PROMPT, "Beginning RSSI Deployment...\r\n");
            test_func = &rssi_setup_test;
            sink = 1;
            runfsm send_deploy(RSSI_TEST);
            break;
        case 'S':
            ser_outf(PROMPT, "Sink set to: %d\r\n", sink);
            //TODO: Do we need this?
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
}
