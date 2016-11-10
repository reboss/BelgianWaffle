#include "sysio.h"
#include "serf.h"
#include "ser.h"
#include "plug_null.h"
#include "tcvphys.h"
#include "phys_cc1100.h"

#include "node_tools.h"

#define BUFFER 10
#define MAX_P 60
#define PONG_LEN 2
#define EOT 0

int sfd;


struct ring_buffer {
	char buffer[BUFFER][MAX_P];
	// need to indicate EOT (end of transmission)
	int retries;
	int in, out, size;
};

// get id's from node_tools
volatile int my_id = 2, parent = 1, child = 3;

volatile struct ring_buffer stream = {
	.retries = 0, .in = 0,
	.out = 0, .size = 0
};

/* 
   sends the same packet continuously until an ack is received.
   After 10 retries, lost connection is assumed.
*/
fsm stream_data {
	
	initial state SEND:
		if (stream.size == 0)
			finish;
		if (stream.retries == MAX_RETRY) {
			// lost connection
		}
		address packet;
		sint plen = strnlen(stream.buffer[stream.out], MAX_P);
	        packet = tcv_wnp(SEND, sfd, plen);
		packet[1] = my_id << 12 | parent << 8 | 1 << 4;
		strcpy((char *) (stream.buffer[stream.out]+2), stream.buffer);
		tcv_endp(packet);
		stream.retries++;
}

fsm send_pong {
	
	initial state SEND:
		address packet;
	        packet = tcv_wnp(SEND, sfd, PONG);
		packet[1] = my_id << 12 | 
	
}

fsm receive {

	address packet;
	sint plength;

	initial state RECV:
		packet = tcv_rnp(RECV, sfd);
	        plength = tcv_left(packet);
		proceed EVALUATE;

        state EVALUATE:
		switch ((packet[1] << 8) >> 12) {

		case 1:
			runfsm send_pong;
			break;
		case 2:
			// receive broadcast
			// setup()
			break;
		case 3:
			// don't overwrite packets!
			strncpy(stream.buffer[stream.in], packet+2, MAX_P);
			stream.in = (stream.in + 1) % BUFFER;
			stream.size++;
			runfsm stream_data;
			runfsm send_ack;
			break;
		case 4:
			/* do not increment out until an ack is received */
			stream.size--;
			stream.out = (stream.out + 1) % BUFFER;
			stream.retries = 0;
			break;
		default:
			break;
		}
}

