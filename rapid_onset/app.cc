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

fsm transmit {

	initial state SEND:
		address packet;
		packet = tcv_wnp(SEND, sfd, 30);
		packet[1] = my_id << 12 | receiver << 8 | 1 << 4;
		strcpy((char *) (packet+2), message);
		tcv_endp(packet);
		finish;
}

fsm receive {

	address packet;
	sint plength;
	initial state RECV:
		packet = tcv_rnp(RECV, sfd);
		plength = tcv_left(packet);
		proceed OUTPUT_PACKET;

        state OUTPUT_PACKET:
		ser_outf(OUTPUT_PACKET, packet+2);
	        tcv_endp(packet);
		proceed RECV;

}

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
		ser_outf(DISPLAY, "P2P Chat (Node #%d)\r\n"
			"(C)hange node ID\r\n"
			"(D)irect transmission\r\n"
			"(B)roadcast transmission\r\n"
			"Selection: ",
			my_id);
 
	        proceed SELECTION;

	state SELECTION:
		switch (selection) {
		case 'I':
			ser_inf(SELECTION, "%d", &my_id);
			proceed PROMPT;
			break;
		case 'D':
			ser_inf(SELECTION, "%d", &receiver);
			selection = 'B';
			proceed PROMPT;
			break;
		case 'M':
			ser_in(SELECTION, message, 30);
			runfsm transmit;
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
			ser_outf(PROMPT, "New node ID (1-15): ");
			selection = 'I';
			proceed SELECTION;
			break;
		case 'D':
			ser_outf(PROMPT, "Receiver node ID (1-15): ");
			proceed SELECTION;
			break;
		case 'B':
			ser_outf(PROMPT, "Message : ");
			selection = 'M';
			proceed SELECTION;
			break;
		default:
			selection = ' ';
			proceed DISPLAY;
			break;
		
		}
}

