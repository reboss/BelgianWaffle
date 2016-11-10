/* CMPT 464 (Fall 2016)
   Lab #6: Sample
   Author: Nicholas M. Boers

   Limitations:
   - doesn't detect duplicate messages
   - doesn't rebroadcast new messages
   - code is untested (I only have access to one device)
*/

#include "sysio.h"
#include "serf.h"
#include "ser.h"

/* VNETI itself and the physical driver & plugin */
#include "phys_cc1100.h"
#include "plug_null.h"
#include "tcv.h"

#define CC1100_BUF_SZ	60
#define UART_BUF_SZ	64

#define POWER 7

/* session descriptor for the single VNETI session */
int sfd;

/* current node ID */
byte node_id = 1;

struct msg {
  byte sender_id;
  byte receiver_id;
  byte sequence_number;
  byte payload[CC1100_BUF_SZ];
};

/* plen determines the required buffer size for 'tcv_wnp' given
   'content_len' bytes that will be written in the packet; returns -1
   if 'content_len' is too large

   Original source: PICOS/Apps/EXAMPLES/SIMPLE/app.cc */
int plen(byte content_len)
{
    /* packet's total length is 'content_len' + 2 bytes for the header
       (network ID) + 2 bytes for CRC, with the whole thing rounded up
       to an even length */
    int len = content_len;

    /* round to even */
    if (len & 0x1)
	len++;

    if (len > CC1100_BUF_SZ - 4) {
	return -1;
    }

    return len + 4;
}

fsm sender(struct msg *msg_data) {
    int count = 0;
    byte header_len;
    byte payload_len;
    byte padding_len;
    address packet;

  state SND_INIT:
    sprintf(msg_data->payload, "%d",count++);
    header_len = 2;
    payload_len = strlen(msg_data->payload) + 1; /* +1 for NUL */
    padding_len = (payload_len & 0x1) ? 1 : 0;

    diag("DBG: sender: header: %d; payload: %d; padding: %d",
	 header_len, payload_len, padding_len);
    
  state SND_GET_BUFFER:

    int len = plen(header_len + payload_len + padding_len);
    if (len == -1) {
	diag("DBG: sender: packet too large; aborting...");
	finish;
    }
    
    packet = tcv_wnp(SND_GET_BUFFER, sfd, len);
    /* first word = 0 as in PICOS/Apps/EXAMPLES/SIMPLE/app.cc */
    packet[0] = 0;

  state SND_FILL_BUFFER:

    byte *buffer_position = (byte *)(packet + 1);

    /* insert the header */
    *buffer_position++ = ((msg_data->sender_id & 0x0f) << 4 |
			  (msg_data->receiver_id & 0x0f));
    *buffer_position++ = (((msg_data->sequence_number & 0x0f) << 4) |
			  ((payload_len + padding_len) / 2));

    /* insert the payload */
    int i;
    char *payload_position = msg_data->payload;
    for (i = 0; i < payload_len; i++) {
      *buffer_position++ = *payload_position++;
    }

    /* insert the padding */
    for (i = 0; i < padding_len; i++) {
      *buffer_position++ = '\0';
    }

    /* produce debug output */
    buffer_position = (byte *)(packet + 1);
    for (i = 0; i < (header_len + payload_len + padding_len); i++) {
	diag("DBG: sender: pkt[%d]: %x", i, (word)(*buffer_position++));
    }
    
    tcv_endp(packet);
    //wait
    delay(1000, SND_INIT);
    release;
    
    ufree(msg_data);

    finish;
}

fsm receiver {

    address packet;
    byte *data;
    byte sender, receiver, sequence, length;
    char *type;
  
  state RCV_INIT:

  state RCV_WAIT:

    packet = tcv_rnp(RCV_WAIT, sfd);

  state RCV_PROCESS:

    data = (byte *)(packet + 1);
    sender = ((*data) >> 4) & 0xf;
    receiver = (*data) & 0x0f;

    data++;
    sequence = ((*data) >> 4) & 0x0f;
    length = (*data) & 0x0f;

    data++;

    if (receiver == 0) {
	proceed(RCV_BROADCAST);
    } else if (receiver == node_id) {
	proceed(RCV_DIRECT);
    } else {
	tcv_endp(packet);
	proceed(RCV_WAIT);
    }
    release;

  state RCV_BROADCAST:

    type = "Broadcast";
    proceed(RCV_DISPLAY_MESSAGE);

  state RCV_DIRECT:

    type = "Message";
    proceed(RCV_DISPLAY_MESSAGE);

  state RCV_DISPLAY_MESSAGE:
    byte first = packet[length + 2] & 255;
    byte last = (packet[length + 2] >> 8) & 255;
    ser_outf(RCV_BROADCAST, "%s from node #%d: %s\r\nFIRST %x\r\nLAST %x\r\n",
	     type, sender, data, first, last);
    tcv_endp(packet);
    proceed(RCV_WAIT);
        
}

fsm root {

    byte receiver_id = 0;
    byte sequence_number = 0;
    
    struct msg *msg_data;
    char serial_input[UART_BUF_SZ];
  
  state R_INIT:
    phys_cc1100(0, CC1100_BUF_SZ);
    tcv_plug(0, &plug_null);
    sfd = tcv_open(NONE, 0, 0);
    if (sfd < 0) {
      diag("unable to open TCV session");
      syserror(EASSERT, "no session");
    }
    
    tcv_control(sfd, PHYSOPT_SETPOWER, POWER);//set power level to 0 (min)
    tcv_control(sfd, PHYSOPT_ON, NULL);

    runfsm receiver;
    
  state R_DISPLAY_MENU:

    ser_outf(R_DISPLAY_MENU,
	     "\r\nP2P Chat (Node #%d)\r\n"
	     "(C)hange node ID\r\n"
	     "(D)irect transmission\r\n"
	     "(B)roadcast transmission\r\n"
	     "Selection: ", node_id);

  state R_GET_MENU_SELECTION:
    
    ser_inf(R_GET_MENU_SELECTION, "%s", serial_input);

    switch (serial_input[0]) {
    case 'C':
      proceed(R_CHANGE_NODE_ID);
    case 'D':
      proceed(R_DIRECT_TRANSMISSION);
    case 'B':
      proceed(R_BROADCAST_TRANSMISSION);
    default:
      proceed(R_INVALID_OPTION);
    }

  state R_INVALID_OPTION:

    ser_outf(R_INVALID_OPTION,
	     "Invalid menu selection.\r\n\r\n");
    proceed(R_DISPLAY_MENU);

  state R_CHANGE_NODE_ID:

    ser_outf(R_CHANGE_NODE_ID,
	     "\r\nNew node ID (1-15): ");

  state R_GET_NODE_ID:

    ser_inf(R_GET_NODE_ID, "%s", serial_input);
    node_id = atoi(serial_input);
    proceed(R_DISPLAY_MENU);
    
  state R_DIRECT_TRANSMISSION:

    ser_outf(R_DIRECT_TRANSMISSION,
	     "\r\nReceiver node ID (1-15): ");

  state R_GET_RECEIVER:

    ser_inf(R_GET_RECEIVER, "%s", serial_input);
    receiver_id = atoi(serial_input);
    proceed(R_MSG_PROMPT);

  state R_BROADCAST_TRANSMISSION:

    ser_outf(R_BROADCAST_TRANSMISSION, "\r\n");
    receiver_id = 0;
    proceed(R_MSG_PROMPT);
  
  state R_MSG_PROMPT:

    ser_outf(R_MSG_PROMPT, "Message: ");

  state R_GET_MSG:

    ser_in(R_GET_MSG, serial_input, UART_BUF_SZ);

    /* prepare data to send */
    msg_data = (struct msg *)umalloc(sizeof(struct msg));
    msg_data->sender_id = node_id;
    msg_data->receiver_id = receiver_id;
    msg_data->sequence_number = sequence_number;
    strcpy(msg_data->payload, serial_input);

    /* advance sequence number */
    sequence_number = (sequence_number + 1) & 0x0f;

    diag("DBG: root: running sender [%d->%d (seq. #%d): %s]",
	 msg_data->sender_id, msg_data->receiver_id,
	 msg_data->sequence_number, (char *)msg_data->payload);
    
    runfsm sender(msg_data);
    
    proceed(R_DISPLAY_MENU);
	    
}
