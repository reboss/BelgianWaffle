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

#include "network_help.h"
#include "network.h"
#include "node_tools.h"
#include "node_led.h"

// Test files 
#include "rssi_test.h"
#include "packet_test.h"

// Milliseconds
#define DEFAULT_DELAY 2000
 
extern int my_id, sfd;
extern bool deployed;
extern stream_stat stream_info;

char message[30];
int receiver = 0, test;
int max_nodes = 3;

//2 Seconds default ping delay
int ping_delay = DEFAULT_DELAY;

int debug = 0; 

//Global that indicates if the node is the sink or not
bool sink = NO;

void init_cc1100(void) {
    phys_cc1100(0, 60);
    tcv_plug(0, &plug_null);
    sfd = tcv_open(WNONE, 0, 0);
    tcv_control(sfd, PHYSOPT_ON, NULL);
    set_power(sfd, HIGH_POWER);
}

void set_globals_sink_YES(void) {
    sink = YES;
    deployed = YES;
}

fsm root {
    int stat_index = 0;

    char selection = '\0';
    initial state INIT:
        init_cc1100();
        leds_all(0);
		set_led(LED_YELLOW_S);
        runfsm receive;
	proceed DISPLAY;

    state DISPLAY:
        ser_outf(DISPLAY, "Rapid Onset; Node id (%d)\r\n"
          "(C)hange Ping Rate (%dms)\r\n"
          "(P)acket Deployment\r\n"
          "(R)SSI Deployment\r\n"
          "(S)et Number of Nodes: (%d)\r\n"
          "(D)ebug mode (%d)\r\n"
          "(N)etwork statistics\r\n"
          "Selection: ",
	  my_id, ping_delay, max_nodes, debug);
	  proceed SELECTION;

    state SELECTION:
        ser_inf(SELECTION, "%c", &selection);
        proceed PROMPT;

	state PROMPT:
	switch (toupper(selection)) {
        case 'C':
            proceed PING_PROMPT;
            break;
        case 'P':
            if (sink) {
		    ser_outf(PROMPT, "This node is already the sink\r\n");
		    break;
            }
            ser_outf(PROMPT, "Beginning Packet Deployment...\r\n");
			set_power(sfd, LOW_POWER);
	    set_globals_sink_YES();
		test = PACKET_TEST;
		runfsm send_deploy(test);
            break;
        case 'R':
            if (sink) {
		    ser_outf(PROMPT, "This node is already the sink\r\n");
                break;
            }
            ser_outf(PROMPT, "Beginning RSSI Deployment...\r\n");
	    set_power(sfd,HIGH_POWER);
	    set_globals_sink_YES();
	    test = RSSI_TEST;
	    set_led(LED_GREEN);
            runfsm send_deploy(test);
            break;
        case 'S':
            proceed NODE_PROMPT;
            break;
        case 'D':
            proceed DEBUG_PROMPT;
        case 'N':
            proceed STATS_HEAD;
        default:
            break;
        }
        proceed DISPLAY;

    state PING_PROMPT:
        ser_outf(PING_PROMPT, "Enter new ping delay in milliseconds: ");
        proceed PING_SELECT;

    state PING_SELECT:
        ser_inf(PING_SELECT, "%d", &ping_delay);
        proceed PING_CONFIRM;

    state PING_CONFIRM:
        ser_outf(PING_CONFIRM, "New ping delay: %dms\r\n\r\n", ping_delay);
        proceed DISPLAY;

    state NODE_PROMPT:
        ser_outf(NODE_PROMPT, "Enter new number of nodes: ");
	proceed NODE_SELECT;

    state NODE_SELECT:
        ser_inf(NODE_SELECT, "%d", &max_nodes);
        proceed NODE_CONFIRM;

    state NODE_CONFIRM:
        ser_outf(NODE_CONFIRM, "New max nodes is: %d\r\n\r\n", max_nodes);
        proceed DISPLAY;

    state DEBUG_PROMPT:
        ser_outf(DEBUG_PROMPT, "Enter new debug mode (higher for more info): ");
        proceed DEBUG_SELECT;

    state DEBUG_SELECT:
        ser_inf(DEBUG_SELECT, "%d", &debug);
        proceed DEBUG_CONFIRM;

    state DEBUG_CONFIRM:
        ser_outf(DEBUG_CONFIRM, "New debug mode: %d\r\n\r\n", debug);
        proceed DISPLAY;

    state STATS_HEAD:
        ser_outf(STATS_HEAD,
            "\r\nEach line is for different packets in sequential order.\r\n"
            "Packets lost, sequence number, packet length, timestamp (s)\r\n");
        stat_index = 0;
        proceed STATS_DATA;

    state STATS_DATA:
        if (stat_index >= stream_info.num_elems)
            proceed DISPLAY;
        if (debug >= 1)
            diag("print stat line\r\n");
        ser_outf(STATS_DATA, "%d,%d,%d,%d\r\n",
                stream_info.packet_loss[stat_index],
                stream_info.seq_num[stat_index],
                stream_info.packet_len[stat_index],
                stream_info.timestamp[stat_index]);

        stat_index++;
        proceed STATS_DATA;

}
