# 1 "/home/students/saforok/CMPT464/olsonet/PICOS/PicOS/MSP430/mach.h"







# 1 "/home/students/saforok/CMPT464/olsonet/PICOS/PicOS/MSP430/supplement.h"







# 1 "/usr/lib/gcc/msp430/4.6.3/../../../../msp430/include/in430.h"



# 47 "/usr/lib/gcc/msp430/4.6.3/../../../../msp430/include/intrinsics.h"
void __nop (void);



void __dint (void);



void __eint (void);


unsigned int __read_status_register (void);


typedef unsigned int __istate_t;




__istate_t __get_interrupt_state (void);


void __write_status_register (unsigned int sr);






void __set_interrupt_state (__istate_t sv);


void *__read_stack_pointer (void);


void __write_stack_pointer (void *sp);


void __bic_status_register (unsigned int bits);


void __bis_status_register (unsigned int bits);



void __bic_status_register_on_exit (unsigned int bits);



void __bis_status_register_on_exit (unsigned int bits);



void *__builtin_frame_address (unsigned int level);



void *__builtin_return_address (unsigned int level);



void __delay_cycles (unsigned long int delay);


unsigned int __swap_bytes (unsigned int v);



unsigned int __get_watchdog_clear_value ();




void __set_watchdog_clear_value (unsigned int v);





void __watchdog_clear ();
# 145 "/usr/lib/gcc/msp430/4.6.3/../../../../msp430/include/msp430f1611.h"
extern volatile unsigned char IE1 __asm__("__" "IE1");









extern volatile unsigned char IFG1 __asm__("__" "IFG1");








extern volatile unsigned char ME1 __asm__("__" "ME1");






extern volatile unsigned char IE2 __asm__("__" "IE2");





extern volatile unsigned char IFG2 __asm__("__" "IFG2");





extern volatile unsigned char ME2 __asm__("__" "ME2");











extern volatile unsigned int WDTCTL __asm__("__" "WDTCTL");
# 242 "/usr/lib/gcc/msp430/4.6.3/../../../../msp430/include/msp430f1611.h"
extern volatile unsigned int MPY __asm__("__" "MPY");

extern volatile unsigned int MPYS __asm__("__" "MPYS");

extern volatile unsigned int MAC __asm__("__" "MAC");

extern volatile unsigned int MACS __asm__("__" "MACS");

extern volatile unsigned int OP2 __asm__("__" "OP2");

extern volatile unsigned int RESLO __asm__("__" "RESLO");

extern volatile unsigned int RESHI __asm__("__" "RESHI");

extern const volatile unsigned int SUMEXT __asm__("__" "SUMEXT");








extern const volatile unsigned char P1IN __asm__("__" "P1IN");

extern volatile unsigned char P1OUT __asm__("__" "P1OUT");

extern volatile unsigned char P1DIR __asm__("__" "P1DIR");

extern volatile unsigned char P1IFG __asm__("__" "P1IFG");

extern volatile unsigned char P1IES __asm__("__" "P1IES");

extern volatile unsigned char P1IE __asm__("__" "P1IE");

extern volatile unsigned char P1SEL __asm__("__" "P1SEL");


extern const volatile unsigned char P2IN __asm__("__" "P2IN");

extern volatile unsigned char P2OUT __asm__("__" "P2OUT");

extern volatile unsigned char P2DIR __asm__("__" "P2DIR");

extern volatile unsigned char P2IFG __asm__("__" "P2IFG");

extern volatile unsigned char P2IES __asm__("__" "P2IES");

extern volatile unsigned char P2IE __asm__("__" "P2IE");

extern volatile unsigned char P2SEL __asm__("__" "P2SEL");








extern const volatile unsigned char P3IN __asm__("__" "P3IN");

extern volatile unsigned char P3OUT __asm__("__" "P3OUT");

extern volatile unsigned char P3DIR __asm__("__" "P3DIR");

extern volatile unsigned char P3SEL __asm__("__" "P3SEL");


extern const volatile unsigned char P4IN __asm__("__" "P4IN");

extern volatile unsigned char P4OUT __asm__("__" "P4OUT");

extern volatile unsigned char P4DIR __asm__("__" "P4DIR");

extern volatile unsigned char P4SEL __asm__("__" "P4SEL");








extern const volatile unsigned char P5IN __asm__("__" "P5IN");

extern volatile unsigned char P5OUT __asm__("__" "P5OUT");

extern volatile unsigned char P5DIR __asm__("__" "P5DIR");

extern volatile unsigned char P5SEL __asm__("__" "P5SEL");


extern const volatile unsigned char P6IN __asm__("__" "P6IN");

extern volatile unsigned char P6OUT __asm__("__" "P6OUT");

extern volatile unsigned char P6DIR __asm__("__" "P6DIR");

extern volatile unsigned char P6SEL __asm__("__" "P6SEL");
# 382 "/usr/lib/gcc/msp430/4.6.3/../../../../msp430/include/msp430f1611.h"
extern volatile unsigned char U0CTL __asm__("__" "U0CTL");

extern volatile unsigned char U0TCTL __asm__("__" "U0TCTL");

extern volatile unsigned char U0RCTL __asm__("__" "U0RCTL");

extern volatile unsigned char U0MCTL __asm__("__" "U0MCTL");

extern volatile unsigned char U0BR0 __asm__("__" "U0BR0");

extern volatile unsigned char U0BR1 __asm__("__" "U0BR1");

extern const volatile unsigned char U0RXBUF __asm__("__" "U0RXBUF");

extern volatile unsigned char U0TXBUF __asm__("__" "U0TXBUF");
# 439 "/usr/lib/gcc/msp430/4.6.3/../../../../msp430/include/msp430f1611.h"
extern volatile unsigned char U1CTL __asm__("__" "U1CTL");

extern volatile unsigned char U1TCTL __asm__("__" "U1TCTL");

extern volatile unsigned char U1RCTL __asm__("__" "U1RCTL");

extern volatile unsigned char U1MCTL __asm__("__" "U1MCTL");

extern volatile unsigned char U1BR0 __asm__("__" "U1BR0");

extern volatile unsigned char U1BR1 __asm__("__" "U1BR1");

extern const volatile unsigned char U1RXBUF __asm__("__" "U1RXBUF");

extern volatile unsigned char U1TXBUF __asm__("__" "U1TXBUF");
# 496 "/usr/lib/gcc/msp430/4.6.3/../../../../msp430/include/msp430f1611.h"
extern volatile unsigned char I2CIE __asm__("__" "I2CIE");










extern volatile unsigned char I2CIFG __asm__("__" "I2CIFG");










extern volatile unsigned char I2CNDAT __asm__("__" "I2CNDAT");










extern volatile unsigned char I2CTCTL __asm__("__" "I2CTCTL");
# 551 "/usr/lib/gcc/msp430/4.6.3/../../../../msp430/include/msp430f1611.h"
extern volatile unsigned char I2CDCTL __asm__("__" "I2CDCTL");








extern volatile unsigned char I2CPSC __asm__("__" "I2CPSC");

extern volatile unsigned char I2CSCLH __asm__("__" "I2CSCLH");

extern volatile unsigned char I2CSCLL __asm__("__" "I2CSCLL");

extern volatile unsigned char I2CDRB __asm__("__" "I2CDRB");

extern volatile unsigned int I2CDRW __asm__("__" "I2CDRW");


extern volatile unsigned int I2COA __asm__("__" "I2COA");

extern volatile unsigned int I2CSA __asm__("__" "I2CSA");


extern const volatile unsigned int I2CIV __asm__("__" "I2CIV");
















extern const volatile unsigned int TAIV __asm__("__" "TAIV");

extern volatile unsigned int TACTL __asm__("__" "TACTL");

extern volatile unsigned int TACCTL0 __asm__("__" "TACCTL0");

extern volatile unsigned int TACCTL1 __asm__("__" "TACCTL1");

extern volatile unsigned int TACCTL2 __asm__("__" "TACCTL2");

extern volatile unsigned int TAR __asm__("__" "TAR");

extern volatile unsigned int TACCR0 __asm__("__" "TACCR0");

extern volatile unsigned int TACCR1 __asm__("__" "TACCR1");

extern volatile unsigned int TACCR2 __asm__("__" "TACCR2");
# 716 "/usr/lib/gcc/msp430/4.6.3/../../../../msp430/include/msp430f1611.h"
extern const volatile unsigned int TBIV __asm__("__" "TBIV");

extern volatile unsigned int TBCTL __asm__("__" "TBCTL");

extern volatile unsigned int TBCCTL0 __asm__("__" "TBCCTL0");

extern volatile unsigned int TBCCTL1 __asm__("__" "TBCCTL1");

extern volatile unsigned int TBCCTL2 __asm__("__" "TBCCTL2");

extern volatile unsigned int TBCCTL3 __asm__("__" "TBCCTL3");

extern volatile unsigned int TBCCTL4 __asm__("__" "TBCCTL4");

extern volatile unsigned int TBCCTL5 __asm__("__" "TBCCTL5");

extern volatile unsigned int TBCCTL6 __asm__("__" "TBCCTL6");

extern volatile unsigned int TBR __asm__("__" "TBR");

extern volatile unsigned int TBCCR0 __asm__("__" "TBCCR0");

extern volatile unsigned int TBCCR1 __asm__("__" "TBCCR1");

extern volatile unsigned int TBCCR2 __asm__("__" "TBCCR2");

extern volatile unsigned int TBCCR3 __asm__("__" "TBCCR3");

extern volatile unsigned int TBCCR4 __asm__("__" "TBCCR4");

extern volatile unsigned int TBCCR5 __asm__("__" "TBCCR5");

extern volatile unsigned int TBCCR6 __asm__("__" "TBCCR6");
# 849 "/usr/lib/gcc/msp430/4.6.3/../../../../msp430/include/msp430f1611.h"
extern volatile unsigned char DCOCTL __asm__("__" "DCOCTL");

extern volatile unsigned char BCSCTL1 __asm__("__" "BCSCTL1");

extern volatile unsigned char BCSCTL2 __asm__("__" "BCSCTL2");
# 908 "/usr/lib/gcc/msp430/4.6.3/../../../../msp430/include/msp430f1611.h"
extern volatile unsigned char SVSCTL __asm__("__" "SVSCTL");
# 928 "/usr/lib/gcc/msp430/4.6.3/../../../../msp430/include/msp430f1611.h"
extern volatile unsigned int FCTL1 __asm__("__" "FCTL1");

extern volatile unsigned int FCTL2 __asm__("__" "FCTL2");

extern volatile unsigned int FCTL3 __asm__("__" "FCTL3");
# 977 "/usr/lib/gcc/msp430/4.6.3/../../../../msp430/include/msp430f1611.h"
extern volatile unsigned char CACTL1 __asm__("__" "CACTL1");

extern volatile unsigned char CACTL2 __asm__("__" "CACTL2");

extern volatile unsigned char CAPD __asm__("__" "CAPD");
# 1021 "/usr/lib/gcc/msp430/4.6.3/../../../../msp430/include/msp430f1611.h"
extern volatile unsigned int ADC12CTL0 __asm__("__" "ADC12CTL0");

extern volatile unsigned int ADC12CTL1 __asm__("__" "ADC12CTL1");

extern volatile unsigned int ADC12IFG __asm__("__" "ADC12IFG");

extern volatile unsigned int ADC12IE __asm__("__" "ADC12IE");

extern volatile unsigned int ADC12IV __asm__("__" "ADC12IV");








extern volatile unsigned int ADC12MEM0 __asm__("__" "ADC12MEM0");

extern volatile unsigned int ADC12MEM1 __asm__("__" "ADC12MEM1");

extern volatile unsigned int ADC12MEM2 __asm__("__" "ADC12MEM2");

extern volatile unsigned int ADC12MEM3 __asm__("__" "ADC12MEM3");

extern volatile unsigned int ADC12MEM4 __asm__("__" "ADC12MEM4");

extern volatile unsigned int ADC12MEM5 __asm__("__" "ADC12MEM5");

extern volatile unsigned int ADC12MEM6 __asm__("__" "ADC12MEM6");

extern volatile unsigned int ADC12MEM7 __asm__("__" "ADC12MEM7");

extern volatile unsigned int ADC12MEM8 __asm__("__" "ADC12MEM8");

extern volatile unsigned int ADC12MEM9 __asm__("__" "ADC12MEM9");

extern volatile unsigned int ADC12MEM10 __asm__("__" "ADC12MEM10");

extern volatile unsigned int ADC12MEM11 __asm__("__" "ADC12MEM11");

extern volatile unsigned int ADC12MEM12 __asm__("__" "ADC12MEM12");

extern volatile unsigned int ADC12MEM13 __asm__("__" "ADC12MEM13");

extern volatile unsigned int ADC12MEM14 __asm__("__" "ADC12MEM14");

extern volatile unsigned int ADC12MEM15 __asm__("__" "ADC12MEM15");








extern volatile unsigned char ADC12MCTL0 __asm__("__" "ADC12MCTL0");

extern volatile unsigned char ADC12MCTL1 __asm__("__" "ADC12MCTL1");

extern volatile unsigned char ADC12MCTL2 __asm__("__" "ADC12MCTL2");

extern volatile unsigned char ADC12MCTL3 __asm__("__" "ADC12MCTL3");

extern volatile unsigned char ADC12MCTL4 __asm__("__" "ADC12MCTL4");

extern volatile unsigned char ADC12MCTL5 __asm__("__" "ADC12MCTL5");

extern volatile unsigned char ADC12MCTL6 __asm__("__" "ADC12MCTL6");

extern volatile unsigned char ADC12MCTL7 __asm__("__" "ADC12MCTL7");

extern volatile unsigned char ADC12MCTL8 __asm__("__" "ADC12MCTL8");

extern volatile unsigned char ADC12MCTL9 __asm__("__" "ADC12MCTL9");

extern volatile unsigned char ADC12MCTL10 __asm__("__" "ADC12MCTL10");

extern volatile unsigned char ADC12MCTL11 __asm__("__" "ADC12MCTL11");

extern volatile unsigned char ADC12MCTL12 __asm__("__" "ADC12MCTL12");

extern volatile unsigned char ADC12MCTL13 __asm__("__" "ADC12MCTL13");

extern volatile unsigned char ADC12MCTL14 __asm__("__" "ADC12MCTL14");

extern volatile unsigned char ADC12MCTL15 __asm__("__" "ADC12MCTL15");
# 1280 "/usr/lib/gcc/msp430/4.6.3/../../../../msp430/include/msp430f1611.h"
extern volatile unsigned int DAC12_0CTL __asm__("__" "DAC12_0CTL");

extern volatile unsigned int DAC12_1CTL __asm__("__" "DAC12_1CTL");
# 1320 "/usr/lib/gcc/msp430/4.6.3/../../../../msp430/include/msp430f1611.h"
extern volatile unsigned int DAC12_0DAT __asm__("__" "DAC12_0DAT");

extern volatile unsigned int DAC12_1DAT __asm__("__" "DAC12_1DAT");






extern volatile unsigned int DMACTL0 __asm__("__" "DMACTL0");
# 1389 "/usr/lib/gcc/msp430/4.6.3/../../../../msp430/include/msp430f1611.h"
extern volatile unsigned int DMACTL1 __asm__("__" "DMACTL1");





extern volatile unsigned int DMA0CTL __asm__("__" "DMA0CTL");

extern volatile unsigned int DMA1CTL __asm__("__" "DMA1CTL");

extern volatile unsigned int DMA2CTL __asm__("__" "DMA2CTL");
# 1442 "/usr/lib/gcc/msp430/4.6.3/../../../../msp430/include/msp430f1611.h"
extern volatile unsigned int DMA0SA __asm__("__" "DMA0SA");

extern volatile unsigned int DMA0DA __asm__("__" "DMA0DA");

extern volatile unsigned int DMA0SZ __asm__("__" "DMA0SZ");

extern volatile unsigned int DMA1SA __asm__("__" "DMA1SA");

extern volatile unsigned int DMA1DA __asm__("__" "DMA1DA");

extern volatile unsigned int DMA1SZ __asm__("__" "DMA1SZ");

extern volatile unsigned int DMA2SA __asm__("__" "DMA2SA");

extern volatile unsigned int DMA2DA __asm__("__" "DMA2DA");

extern volatile unsigned int DMA2SZ __asm__("__" "DMA2SZ");
# 208 "/home/students/saforok/CMPT464/olsonet/PICOS/PicOS/MSP430/supplement.h"
extern char *__bss_end;
# 13 "/home/students/saforok/CMPT464/olsonet/PICOS/PicOS/MSP430/arch.h"
typedef unsigned char bool;
typedef unsigned char Boolean;
typedef unsigned int word;
typedef int sint;
typedef long int lint;
typedef unsigned char byte;
typedef unsigned long lword;
typedef unsigned int field;
typedef word *address;


typedef volatile address va_list;







typedef struct {

 byte pdmode:1,
  evntpn:1,
  fstblk:1,
  ledblk:1,
  ledsts:4;

 byte ledblc;

} systat_t;

extern volatile systat_t __pi_systat;
# 70 "/home/students/saforok/CMPT464/olsonet/PICOS/PicOS/MSP430/arch.h"
void __pi_release () __attribute__ ((noreturn));
# 477 "/home/students/saforok/CMPT464/olsonet/PICOS/PicOS/MSP430/mach.h"
void tci_run_delay_timer ();
void tci_run_auxiliary_timer ();
word tci_update_delay_ticks (Boolean);
# 20 "/home/students/saforok/CMPT464/olsonet/PICOS/PicOS/MSP430/uart_def.h"





typedef struct {
 word rate;
 byte A, B;
} uart_rate_table_entry_t;
# 501 "/home/students/saforok/CMPT464/olsonet/PICOS/PicOS/MSP430/mach.h"



typedef struct {






 volatile byte flags;
 byte out;



 byte in [32];
 byte ib_in, ib_out, ib_count;

} uart_t;









extern uart_t __pi_uart [];
# 1 "/home/students/saforok/CMPT464/olsonet/PICOS/PicOS/leds.h"











# 397 "/home/students/saforok/CMPT464/olsonet/PICOS/PicOS/sysio.h"
void root (word state);

typedef void (*fsmcode)(word);

void __pi_wait (word, word);
void __pi_trigger (word), __pi_ptrigger (sint, word);
sint __pi_fork (fsmcode func, word data);
void __pi_fork_join_release (fsmcode func, word data, word st);
void reset (void) __attribute__ ((noreturn)) ;
void halt (void) __attribute__ ((noreturn)) ;

int __pi_strlen (const char*);
void __pi_strcpy (char*, const char*);
void __pi_strncpy (char*, const char*, int);
void __pi_strcat (char*, const char*);
void __pi_strncat (char*, const char*, int);
void __pi_memcpy (char *dest, const char *src, int);
void __pi_memset (char *dest, char c, int);

extern const char __pi_hex_enc_table [];


extern const lword host_id;



address __pi_malloc (word);
void __pi_free (address);
void __pi_waitmem (word);


word __pi_memfree (address);
word __pi_maxfree (address);
# 456 "/home/students/saforok/CMPT464/olsonet/PICOS/PicOS/sysio.h"
word __pi_stackfree (void);







void __pi_syserror (int, const char*) __attribute__ ((noreturn)) ;
# 586 "/home/students/saforok/CMPT464/olsonet/PICOS/PicOS/sysio.h"
void diag (const char *, ...);






lword lrnd (void);
# 613 "/home/students/saforok/CMPT464/olsonet/PICOS/PicOS/sysio.h"
int io (int, int, int, char*, int);








void unwait (void);


void delay (word, word);
word dleft (sint);





void kill (sint);

void killall (fsmcode);






sint running (fsmcode);
int crunning (fsmcode);

fsmcode getcode (sint);

void proceed (word);

void powerup (void), powerdown (void);

void utimer_add (address), utimer_delete (address);


void __pi_utimer_set (address, word);













extern byte __pi_mincd;


extern lword __pi_nseconds;




void udelay (word);
void mdelay (word);
# 713 "/home/students/saforok/CMPT464/olsonet/PICOS/PicOS/sysio.h"
void __pi_badstate (void);
# 1 "/home/students/saforok/CMPT464/olsonet/PICOS/PicOS/tcv_defs.h"







typedef struct {






 word head,
  tail;
} tcvadp_t;




typedef struct {
 int (*tcv_ope) (int, int, va_list);
 int (*tcv_clo) (int, int);
 int (*tcv_rcv) (int, address, int, int*, tcvadp_t*);
 int (*tcv_frm) (address, tcvadp_t*);
 int (*tcv_out) (address);
 int (*tcv_xmt) (address);
 int (*tcv_tmt) (address);
 int tcv_info;
} tcvplug_t;




struct __tcv_qitem_s {
 struct __tcv_qitem_s *next,
    *prev;
};

typedef struct __tcv_qitem_s __tcv_qitem_t;
typedef struct __tcv_qitem_s __tcv_qhead_t;



struct __tcv_titem_s {

 struct __tcv_titem_s *next,
    *prev;
 word value;
};

typedef struct __tcv_titem_s __tcv_titem_t;

typedef struct {
 __tcv_titem_t *next,
    *prev;
} __tcv_thead_t;

typedef union {
 word value;
 struct {
  word queued:1,
   outgoing:1,
   urgent:1,
   session:7,
   plugin:3,
   phys:3;
 } b;
} __tcv_battr_t;




struct __tcv_hblock_s {



    union {
 __tcv_qitem_t bqueue;
 tcvadp_t pointers;





    } u;










 word length;




 __tcv_battr_t attributes;











};



typedef struct __tcv_hblock_s __tcv_hblock_t;

typedef struct {



 __tcv_qhead_t rqueue;



 __tcv_battr_t attpattern;














} __tcv_sesdesc_t;
# 166 "/home/students/saforok/CMPT464/olsonet/PICOS/PicOS/tcv_defs.h"
int tcv_plug (int, const tcvplug_t*);
int tcv_open (word, int, int, ...);
int tcv_close (word, int);
address tcv_rnp (word, int);
address tcv_wnps (word, int, int, Boolean);
int tcv_qsize (int, int);
int tcv_erase (int, int);
int tcv_read (address, byte*, int);
int tcv_write (address, const byte*, int);
void tcv_endp (address);
void tcv_drop (address);
int tcv_control (int, int, address);
# 801 "/home/students/saforok/CMPT464/olsonet/PICOS/PicOS/sysio.h"
extern lword entropy;
# 881 "/home/students/saforok/CMPT464/olsonet/PICOS/PicOS/sysio.h"
typedef struct {



 word State;
 word Event;
} __pi_event_t;

struct __pi_pcb_s {








 word Status;
 word Timer;
 fsmcode code;
 word data;
 __pi_event_t Events [4];


 struct __pi_pcb_s *Next;

};

typedef struct __pi_pcb_s __pi_pcb_t;

extern __pi_pcb_t *__pi_curr;
# 1 "/home/students/saforok/CMPT464/olsonet/PICOS/PicOS/Libs/Lib/serf.h"







# 11 "/home/students/saforok/CMPT464/olsonet/PICOS/PicOS/Libs/Lib/form.h"
word __pi_vfparse (char*, word, const char*, va_list);
char *vform (char*, const char*, va_list);
int vscan (const char*, const char*, va_list);
char *form (char*, const char*, ...);
word fsize (const char*, ...);
int scan (const char*, const char*, ...);
# 9 "/home/students/saforok/CMPT464/olsonet/PICOS/PicOS/Libs/Lib/serf.h"



int ser_outf (word, const char*, ...);
int ser_inf (word, const char*, ...);
# 12 "/home/students/saforok/CMPT464/olsonet/PICOS/PicOS/Libs/Lib/ser.h"
int ser_out (word, const char*);
int ser_in (word, char*, int);
int ser_outb (word, const char*);
# 14 "app.cc"


# 10 "/home/students/saforok/CMPT464/olsonet/PICOS/PicOS/Libs/Lib/phys_cc1100.h"
void phys_cc1100 (int, int);
# 14 "/home/students/saforok/CMPT464/olsonet/PICOS/PicOS/Libs/Lib/plug_null.h"
extern const tcvplug_t plug_null;
# 1 "/home/students/saforok/CMPT464/olsonet/PICOS/PicOS/tcv.h"






# 1 "/home/students/saforok/CMPT464/olsonet/PICOS/PicOS/pins.h"







# 1 "/home/students/saforok/CMPT464/olsonet/PICOS/PicOS/analog_sensor.h"







# 11 "/home/students/saforok/CMPT464/olsonet/PICOS/PicOS/MSP430/sensors_sys.h"
typedef struct {

 word W [3];

} i_sensdesc_t;

typedef struct {

 byte tp,
  adcpars [3];
 word nsamples;

} a_sensdesc_t;

typedef struct {

 byte tp, num;
 void (*fun_val) (word, const byte*, address);
 void (*fun_ini) ();

} d_sensdesc_t;
# 12 "/home/students/saforok/CMPT464/olsonet/PICOS/PicOS/sensors.h"

void read_sensor (word, sint, address);
# 9 "/home/students/saforok/CMPT464/olsonet/PICOS/PicOS/analog_sensor.h"



void analog_sensor_read (word, const a_sensdesc_t*, address);
# 212 "/home/students/saforok/CMPT464/olsonet/PICOS/PicOS/MSP430/pins_sys.h"
typedef struct {
 byte poff, pnum;
} pind_t;










Boolean __pi_pin_available (word);
Boolean __pi_pin_adc_available (word);
word __pi_pin_ivalue (word);
word __pi_pin_ovalue (word);
Boolean __pi_pin_adc (word);
Boolean __pi_pin_output (word);
void __pi_pin_set (word);
void __pi_pin_clear (word);
void __pi_pin_set_input (word);
void __pi_pin_set_output (word);
void __pi_pin_set_adc (word);
# 261 "/home/students/saforok/CMPT464/olsonet/PICOS/PicOS/MSP430/pins_sys.h"
Boolean __pi_pin_dac_available (word);
Boolean __pi_pin_dac (word);
void __pi_clear_dac (word);
void __pi_set_dac (word);
void __pi_write_dac (word, word, word);
# 17 "/home/students/saforok/CMPT464/olsonet/PICOS/PicOS/kernel/kernel.h"

void __pi_set_release (void);
void update_n_wake (word, Boolean);


void __pi_init_sensors (void);






extern word __pi_mintk;
extern volatile word __pi_old, __pi_new;

extern void tcv_init (void);



extern __pi_pcb_t *__PCB;
# 75 "/home/students/saforok/CMPT464/olsonet/PICOS/PicOS/kernel/kernel.h"
typedef void (*devinitfun_t)(int param);
typedef int (*devreqfun_t)(int, char*, int);

typedef struct {



 devinitfun_t init;
 int param;
} devinit_t;

void adddevfunc (devreqfun_t, int);
# 19 "app.cc"







int sfd;


byte node_id = 1;

struct msg {
  byte sender_id;
  byte receiver_id;
  byte sequence_number;
  byte payload[60];
};






int plen(byte content_len)
{



    int len = content_len;


    if (len & 0x1)
 len++;

    if (len > 60 - 4) {
 return -1;
    }

    return len + 4;
}


#define SND_INIT 0
#define SND_GET_BUFFER 1
#define SND_FILL_BUFFER 2
# 61 "app.cc"
void sender (word __pi_st) { struct msg * msg_data = (struct msg *)(__pi_curr->data); switch (__pi_st) { 
# 61 "app.cc"

    static int count=0 ;
    static byte header_len;
    static byte payload_len;
    static byte padding_len;
    static address packet;

  case SND_INIT : __stlab_SND_INIT: {
    sprintf(msg_data->payload, "%d",count++);
    header_len = 2;
    payload_len = __pi_strlen (msg_data->payload) + 1;
    padding_len = (payload_len & 0x1) ? 1 : 0;

    diag("DBG: sender: header: %d; payload: %d; padding: %d",
  header_len, payload_len, padding_len);

  } case SND_GET_BUFFER : __stlab_SND_GET_BUFFER: {

    int len = plen(header_len + payload_len + padding_len);
    if (len == -1) {
 diag("DBG: sender: packet too large; aborting...");
 kill (0);
    }

    packet = tcv_wnps (SND_GET_BUFFER, sfd, len, ((Boolean)0));

    packet[0] = 0;

  } case SND_FILL_BUFFER : __stlab_SND_FILL_BUFFER: {

    byte *buffer_position = (byte *)(packet + 1);


    *buffer_position++ = ((msg_data->sender_id & 0x0f) << 4 |
     (msg_data->receiver_id & 0x0f));
    *buffer_position++ = (((msg_data->sequence_number & 0x0f) << 4) |
     ((payload_len + padding_len) / 2));


    int i;
    char *payload_position = msg_data->payload;
    for (i = 0; i < payload_len; i++) {
      *buffer_position++ = *payload_position++;
    }


    for (i = 0; i < padding_len; i++) {
      *buffer_position++ = '\0';
    }


    buffer_position = (byte *)(packet + 1);
    for (i = 0; i < (header_len + payload_len + padding_len); i++) {
 diag("DBG: sender: pkt[%d]: %x", i, (word)(*buffer_position++));
    }

    tcv_endp(packet);

    delay(1000, SND_INIT);
    __pi_release ();

    __pi_free ((address)(msg_data));

    kill (0);
break; } default: __pi_badstate (); } }
#undef SND_INIT
#undef SND_GET_BUFFER
#undef SND_FILL_BUFFER
# 125 "app.cc"



#define RCV_INIT 0
#define RCV_WAIT 1
#define RCV_PROCESS 2
#define RCV_BROADCAST 3
#define RCV_DIRECT 4
#define RCV_DISPLAY_MESSAGE 5
# 127 "app.cc"
void receiver (word __pi_st) { switch (__pi_st) { 
# 127 "app.cc"


    static address packet;
    static byte *data;
    static byte sender,receiver,sequence,length;
    static char *type;

  case RCV_INIT : __stlab_RCV_INIT: {

  } case RCV_WAIT : __stlab_RCV_WAIT: {

    packet = tcv_rnp(RCV_WAIT, sfd);

  } case RCV_PROCESS : __stlab_RCV_PROCESS: {

    data = (byte *)(packet + 1);
    sender = ((*data) >> 4) & 0xf;
    receiver = (*data) & 0x0f;

    data++;
    sequence = ((*data) >> 4) & 0x0f;
    length = (*data) & 0x0f;

    data++;

    if (receiver == 0) {
 proceed (RCV_BROADCAST);
    } else if (receiver == node_id) {
 proceed (RCV_DIRECT);
    } else {
 tcv_endp(packet);
 proceed (RCV_WAIT);
    }
    __pi_release ();

  } case RCV_BROADCAST : __stlab_RCV_BROADCAST: {

    type = "Broadcast";
    proceed (RCV_DISPLAY_MESSAGE);

  } case RCV_DIRECT : __stlab_RCV_DIRECT: {

    type = "Message";
    proceed (RCV_DISPLAY_MESSAGE);

  } case RCV_DISPLAY_MESSAGE : __stlab_RCV_DISPLAY_MESSAGE: {
    byte first = packet[length + 2] & 255;
    byte last = (packet[length + 2] >> 8) & 255;
    ser_outf(RCV_BROADCAST, "LOW POWER %s from node #%d: %s\r\nLQI: %x\r\nRSSI: %x\r\n",
      type, sender, data, first, last);
    tcv_endp(packet);
    proceed (RCV_WAIT);

break; } default: __pi_badstate (); } }
#undef RCV_INIT
#undef RCV_WAIT
#undef RCV_PROCESS
#undef RCV_BROADCAST
#undef RCV_DIRECT
#undef RCV_DISPLAY_MESSAGE
# 180 "app.cc"



#define R_INIT 0
#define R_DISPLAY_MENU 1
#define R_GET_MENU_SELECTION 2
#define R_INVALID_OPTION 3
#define R_CHANGE_NODE_ID 4
#define R_GET_NODE_ID 5
#define R_DIRECT_TRANSMISSION 6
#define R_GET_RECEIVER 7
#define R_BROADCAST_TRANSMISSION 8
#define R_MSG_PROMPT 9
#define R_GET_MSG 10
# 182 "app.cc"
void root (word __pi_st) { switch (__pi_st) { 
# 182 "app.cc"


    static byte receiver_id=0 ;
    static byte sequence_number=0 ;

    static struct msg *msg_data;
    static char serial_input[64];

  case R_INIT : __stlab_R_INIT: {
    phys_cc1100(0, 60);
    tcv_plug(0, &plug_null);
    sfd = tcv_open(((word)(-1)), 0, 0);
    if (sfd < 0) {
      diag("unable to open TCV session");
      __pi_syserror (10, "no session");
    }

    tcv_control(sfd, 7, 0);
    tcv_control(sfd, 4, 0);
    int _5chan = 5;
    tcv_control(sfd, 18, &_5chan);

    __pi_fork (receiver, 0);

  } case R_DISPLAY_MENU : __stlab_R_DISPLAY_MENU: {

    ser_outf(R_DISPLAY_MENU,
      "\r\nP2P Chat (Node #%d)\r\n"
      "(C)hange node ID\r\n"
      "(D)irect transmission\r\n"
      "(B)roadcast transmission\r\n"
      "Selection: ", node_id);

  } case R_GET_MENU_SELECTION : __stlab_R_GET_MENU_SELECTION: {

    ser_inf(R_GET_MENU_SELECTION, "%s", serial_input);

    switch (serial_input[0]) {
    case 'C':
      proceed (R_CHANGE_NODE_ID);
    case 'D':
      proceed (R_DIRECT_TRANSMISSION);
    case 'B':
      proceed (R_BROADCAST_TRANSMISSION);
    default:
      proceed (R_INVALID_OPTION);
    }

  } case R_INVALID_OPTION : __stlab_R_INVALID_OPTION: {

    ser_outf(R_INVALID_OPTION,
      "Invalid menu selection.\r\n\r\n");
    proceed (R_DISPLAY_MENU);

  } case R_CHANGE_NODE_ID : __stlab_R_CHANGE_NODE_ID: {

    ser_outf(R_CHANGE_NODE_ID,
      "\r\nNew node ID (1-15): ");

  } case R_GET_NODE_ID : __stlab_R_GET_NODE_ID: {

    ser_inf(R_GET_NODE_ID, "%s", serial_input);
    node_id = atoi(serial_input);
    proceed (R_DISPLAY_MENU);

  } case R_DIRECT_TRANSMISSION : __stlab_R_DIRECT_TRANSMISSION: {

    ser_outf(R_DIRECT_TRANSMISSION,
      "\r\nReceiver node ID (1-15): ");

  } case R_GET_RECEIVER : __stlab_R_GET_RECEIVER: {

    ser_inf(R_GET_RECEIVER, "%s", serial_input);
    receiver_id = atoi(serial_input);
    proceed (R_MSG_PROMPT);

  } case R_BROADCAST_TRANSMISSION : __stlab_R_BROADCAST_TRANSMISSION: {

    ser_outf(R_BROADCAST_TRANSMISSION, "\r\n");
    receiver_id = 0;
    proceed (R_MSG_PROMPT);

  } case R_MSG_PROMPT : __stlab_R_MSG_PROMPT: {

    ser_outf(R_MSG_PROMPT, "Message: ");

  } case R_GET_MSG : __stlab_R_GET_MSG: {

    ser_in(R_GET_MSG, serial_input, 64);


    msg_data = (struct msg *)__pi_malloc (sizeof(struct msg));
    msg_data->sender_id = node_id;
    msg_data->receiver_id = receiver_id;
    msg_data->sequence_number = sequence_number;
    __pi_strcpy (msg_data->payload, serial_input);


    sequence_number = (sequence_number + 1) & 0x0f;

    diag("DBG: root: running sender [%d->%d (seq. #%d): %s]",
  msg_data->sender_id, msg_data->receiver_id,
  msg_data->sequence_number, (char *)msg_data->payload);

    __pi_fork (sender, (word)(msg_data ));

    proceed (R_DISPLAY_MENU);

break; } default: __pi_badstate (); } }
#undef R_INIT
#undef R_DISPLAY_MENU
#undef R_GET_MENU_SELECTION
#undef R_INVALID_OPTION
#undef R_CHANGE_NODE_ID
#undef R_GET_NODE_ID
#undef R_DIRECT_TRANSMISSION
#undef R_GET_RECEIVER
#undef R_BROADCAST_TRANSMISSION
#undef R_MSG_PROMPT
#undef R_GET_MSG
# 290 "app.cc"

