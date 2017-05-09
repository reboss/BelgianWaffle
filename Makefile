#
# Created by mkmk, DO NOT EDIT!!!
#
CC=msp430-gcc
AS=msp430-as
OC=msp430-objcopy -O ihex
SI=msp430-size -Ax
CF=-mmcu=msp430f1611 -DSYSVER_U=4 -DSYSVER_L=0 -DSYSVER_T=PG160928A -DBOARD_WARSAW -DBOARD_TYPE=WARSAW -D__COMP_VERSION__=4 -D__MSP430__ -D__MSP430_1611__
AF=-mmcu=msp430f1611
OF=-Os -g -Wundef -fno-strict-aliasing
TR=Image
TD=./KTMP
LD=
# include directories
I00=/home/students/saforok/CMPT464/olsonet/PICOS/PicOS/MSP430
I01=/home/students/saforok/CMPT464/olsonet/PICOS/PicOS/MSP430/BOARDS/WARSAW
I02=/home/students/saforok/CMPT464/olsonet/PICOS/PicOS/kernel
I03=/home/students/saforok/CMPT464/olsonet/PICOS/PicOS
I04=/home/students/saforok/CMPT464/olsonet/PICOS/PicOS/Libs/Lib
# source directories
S00=.
S01=/home/students/saforok/CMPT464/olsonet/PICOS/PicOS/MSP430
S02=/home/students/saforok/CMPT464/olsonet/PICOS/PicOS
S03=/home/students/saforok/CMPT464/olsonet/PICOS/PicOS/Libs/Lib
S04=/home/students/saforok/CMPT464/olsonet/PICOS/PicOS/kernel
#
IN=-I $(I00) -I $(I01) -I $(I02) -I $(I03) -I $(I04) 

all :	$(TR)

# target: ""
BF=$(TD)/app.o $(TD)/main.o $(TD)/tcv.o $(TD)/phys_cc1100.o $(TD)/storage_at45xxx.o $(TD)/iflash.o $(TD)/form.o $(TD)/scan.o $(TD)/ser_outf.o $(TD)/ser_inf.o $(TD)/ser_select.o $(TD)/ser_out.o $(TD)/ser_outb.o $(TD)/ser_in.o $(TD)/plug_null.o $(TD)/sensors.o $(TD)/analog_sensor.o $(TD)/pins_sys.o $(TD)/p1irq.o $(TD)/vform.o $(TD)/vscan.o $(TD)/__outserial.o $(TD)/__inserial.o $(TD)/pins_sys_in.o $(TD)/pins_sys_out.o $(TD)/kernel.o 

$(TR) :	$(BF)
	$(CC) -o $(TR) $(CF) $(BF) $(LD)
	$(OC) $(TR) $(TR).a43
	chmod 0644 $(TR).a43
	$(SI) $(TR)

$(TD)/app.o : $(S00)/app.cc $(I01)/board_options.sys $(I03)/modsyms.h $(I00)/supplement.h $(I00)/portnames.h $(I00)/arch.h $(I00)/mach.h $(I00)/uart_def.h $(I00)/leds_sys.h $(I01)/board_leds.h $(I03)/leds.h $(I00)/diag_sys.h $(I03)/dbgtrc.h $(I01)/board_headers.h $(I03)/tcv_defs.h $(I03)/sysio.h $(I04)/form.h $(I04)/serf.h $(I04)/ser.h $(I04)/phys_cc1100.h $(I04)/plug_null.h $(I03)/ualeds.h $(I03)/uart.h $(I00)/sensors_sys.h $(I03)/sensors.h $(I03)/analog_sensor.h $(I01)/board_pins.h $(I00)/pins_sys.h $(I03)/pins.h $(I02)/kernel.h $(I03)/tcv.h
	mkdir -p $(TD)
	cp $(S00)/app.cc $(TD)/___pcs___app.c
	$(CC) $(CF) $(OF) $(IN) -E $(TD)/___pcs___app.c > $(TD)/___pct___app.c
	picomp -p < $(TD)/___pct___app.c > $(TD)/app.c
	rm $(TD)/___pcs___app.c $(TD)/___pct___app.c
	$(CC) $(CF) $(OF) $(IN) -c $(TD)/app.c -o $(TD)/app.o

$(TD)/main.o : $(S01)/main.c $(I01)/board_options.sys $(I03)/modsyms.h $(I00)/supplement.h $(I00)/portnames.h $(I00)/arch.h $(I00)/mach.h $(I00)/uart_def.h $(I00)/leds_sys.h $(I01)/board_leds.h $(I03)/leds.h $(I00)/diag_sys.h $(I03)/dbgtrc.h $(I01)/board_headers.h $(I03)/tcv_defs.h $(I03)/sysio.h $(I03)/ualeds.h $(I03)/uart.h $(I00)/sensors_sys.h $(I03)/sensors.h $(I03)/analog_sensor.h $(I01)/board_pins.h $(I00)/pins_sys.h $(I03)/pins.h $(I02)/kernel.h $(I03)/storage.h $(I03)/storage_at45xxx.h $(I01)/board_storage.h $(I00)/iflash_sys.h $(I03)/iflash.h $(I03)/irq_timer_headers.h $(I02)/scheduler.h $(I00)/portinit.h $(I03)/irq_timer_leds.h $(I03)/irq_timer.h $(I01)/board_second.h $(I03)/second_reset.h $(I03)/second.h
	mkdir -p $(TD)
	$(CC) $(CF) $(OF) $(IN) -c $(S01)/main.c -o $(TD)/main.o

$(TD)/tcv.o : $(S02)/tcv.c $(I01)/board_options.sys $(I03)/modsyms.h $(I00)/supplement.h $(I00)/portnames.h $(I00)/arch.h $(I00)/mach.h $(I00)/uart_def.h $(I00)/leds_sys.h $(I01)/board_leds.h $(I03)/leds.h $(I00)/diag_sys.h $(I03)/dbgtrc.h $(I01)/board_headers.h $(I03)/tcv_defs.h $(I03)/sysio.h $(I03)/ualeds.h $(I03)/uart.h $(I00)/sensors_sys.h $(I03)/sensors.h $(I03)/analog_sensor.h $(I01)/board_pins.h $(I00)/pins_sys.h $(I03)/pins.h $(I02)/kernel.h $(I03)/tcv.h $(I03)/tcvphys.h $(I03)/tcvplug.h $(I03)/tcv_node_data.h
	mkdir -p $(TD)
	$(CC) $(CF) $(OF) $(IN) -c $(S02)/tcv.c -o $(TD)/tcv.o

$(TD)/phys_cc1100.o : $(S03)/phys_cc1100.c $(I01)/board_options.sys $(I03)/modsyms.h $(I00)/supplement.h $(I00)/portnames.h $(I00)/arch.h $(I00)/mach.h $(I00)/uart_def.h $(I00)/leds_sys.h $(I01)/board_leds.h $(I03)/leds.h $(I00)/diag_sys.h $(I03)/dbgtrc.h $(I01)/board_headers.h $(I03)/tcv_defs.h $(I03)/sysio.h $(I03)/ualeds.h $(I03)/uart.h $(I00)/sensors_sys.h $(I03)/sensors.h $(I03)/analog_sensor.h $(I01)/board_pins.h $(I00)/pins_sys.h $(I03)/pins.h $(I02)/kernel.h $(I03)/tcvphys.h $(I01)/board_rf.h $(I00)/cc1100_sys.h $(I03)/rfleds.h $(I03)/cc1100.h
	mkdir -p $(TD)
	$(CC) $(CF) $(OF) $(IN) -c $(S03)/phys_cc1100.c -o $(TD)/phys_cc1100.o

$(TD)/storage_at45xxx.o : $(S02)/storage_at45xxx.c $(I01)/board_options.sys $(I03)/modsyms.h $(I00)/supplement.h $(I00)/portnames.h $(I00)/arch.h $(I00)/mach.h $(I00)/uart_def.h $(I00)/leds_sys.h $(I01)/board_leds.h $(I03)/leds.h $(I00)/diag_sys.h $(I03)/dbgtrc.h $(I01)/board_headers.h $(I03)/tcv_defs.h $(I03)/sysio.h $(I03)/ualeds.h $(I03)/uart.h $(I00)/sensors_sys.h $(I03)/sensors.h $(I03)/analog_sensor.h $(I01)/board_pins.h $(I00)/pins_sys.h $(I03)/pins.h $(I02)/kernel.h $(I03)/storage.h $(I03)/storage_at45xxx.h $(I01)/board_storage.h $(I00)/iflash_sys.h $(I03)/iflash.h $(I03)/storage_eeprom.h
	mkdir -p $(TD)
	$(CC) $(CF) $(OF) $(IN) -c $(S02)/storage_at45xxx.c -o $(TD)/storage_at45xxx.o

$(TD)/iflash.o : $(S02)/iflash.c $(I01)/board_options.sys $(I03)/modsyms.h $(I00)/supplement.h $(I00)/portnames.h $(I00)/arch.h $(I00)/mach.h $(I00)/uart_def.h $(I00)/leds_sys.h $(I01)/board_leds.h $(I03)/leds.h $(I00)/diag_sys.h $(I03)/dbgtrc.h $(I01)/board_headers.h $(I03)/tcv_defs.h $(I03)/sysio.h $(I00)/sensors_sys.h $(I03)/sensors.h $(I03)/analog_sensor.h $(I01)/board_pins.h $(I00)/pins_sys.h $(I03)/pins.h $(I03)/ualeds.h $(I03)/uart.h $(I02)/kernel.h $(I03)/storage.h $(I03)/storage_at45xxx.h $(I01)/board_storage.h $(I00)/iflash_sys.h $(I03)/iflash.h
	mkdir -p $(TD)
	$(CC) $(CF) $(OF) $(IN) -c $(S02)/iflash.c -o $(TD)/iflash.o

$(TD)/form.o : $(S03)/form.c $(I01)/board_options.sys $(I03)/modsyms.h $(I00)/supplement.h $(I00)/portnames.h $(I00)/arch.h $(I00)/mach.h $(I00)/uart_def.h $(I00)/leds_sys.h $(I01)/board_leds.h $(I03)/leds.h $(I00)/diag_sys.h $(I03)/dbgtrc.h $(I01)/board_headers.h $(I03)/tcv_defs.h $(I03)/sysio.h $(I04)/form.h
	mkdir -p $(TD)
	$(CC) $(CF) $(OF) $(IN) -c $(S03)/form.c -o $(TD)/form.o

$(TD)/scan.o : $(S03)/scan.c $(I01)/board_options.sys $(I03)/modsyms.h $(I00)/supplement.h $(I00)/portnames.h $(I00)/arch.h $(I00)/mach.h $(I00)/uart_def.h $(I00)/leds_sys.h $(I01)/board_leds.h $(I03)/leds.h $(I00)/diag_sys.h $(I03)/dbgtrc.h $(I01)/board_headers.h $(I03)/tcv_defs.h $(I03)/sysio.h $(I04)/form.h
	mkdir -p $(TD)
	$(CC) $(CF) $(OF) $(IN) -c $(S03)/scan.c -o $(TD)/scan.o

$(TD)/ser_outf.o : $(S03)/ser_outf.c $(I01)/board_options.sys $(I03)/modsyms.h $(I00)/supplement.h $(I00)/portnames.h $(I00)/arch.h $(I00)/mach.h $(I00)/uart_def.h $(I00)/leds_sys.h $(I01)/board_leds.h $(I03)/leds.h $(I00)/diag_sys.h $(I03)/dbgtrc.h $(I01)/board_headers.h $(I03)/tcv_defs.h $(I03)/sysio.h $(I04)/form.h
	mkdir -p $(TD)
	$(CC) $(CF) $(OF) $(IN) -c $(S03)/ser_outf.c -o $(TD)/ser_outf.o

$(TD)/ser_inf.o : $(S03)/ser_inf.c $(I01)/board_options.sys $(I03)/modsyms.h $(I00)/supplement.h $(I00)/portnames.h $(I00)/arch.h $(I00)/mach.h $(I00)/uart_def.h $(I00)/leds_sys.h $(I01)/board_leds.h $(I03)/leds.h $(I00)/diag_sys.h $(I03)/dbgtrc.h $(I01)/board_headers.h $(I03)/tcv_defs.h $(I03)/sysio.h $(I04)/form.h
	mkdir -p $(TD)
	$(CC) $(CF) $(OF) $(IN) -c $(S03)/ser_inf.c -o $(TD)/ser_inf.o

$(TD)/ser_select.o : $(S03)/ser_select.c $(I01)/board_options.sys $(I03)/modsyms.h $(I00)/supplement.h $(I00)/portnames.h $(I00)/arch.h $(I00)/mach.h $(I00)/uart_def.h $(I00)/leds_sys.h $(I01)/board_leds.h $(I03)/leds.h $(I00)/diag_sys.h $(I03)/dbgtrc.h $(I01)/board_headers.h $(I03)/tcv_defs.h $(I03)/sysio.h
	mkdir -p $(TD)
	$(CC) $(CF) $(OF) $(IN) -c $(S03)/ser_select.c -o $(TD)/ser_select.o

$(TD)/ser_out.o : $(S03)/ser_out.c $(I01)/board_options.sys $(I03)/modsyms.h $(I00)/supplement.h $(I00)/portnames.h $(I00)/arch.h $(I00)/mach.h $(I00)/uart_def.h $(I00)/leds_sys.h $(I01)/board_leds.h $(I03)/leds.h $(I00)/diag_sys.h $(I03)/dbgtrc.h $(I01)/board_headers.h $(I03)/tcv_defs.h $(I03)/sysio.h
	mkdir -p $(TD)
	$(CC) $(CF) $(OF) $(IN) -c $(S03)/ser_out.c -o $(TD)/ser_out.o

$(TD)/ser_outb.o : $(S03)/ser_outb.c $(I01)/board_options.sys $(I03)/modsyms.h $(I00)/supplement.h $(I00)/portnames.h $(I00)/arch.h $(I00)/mach.h $(I00)/uart_def.h $(I00)/leds_sys.h $(I01)/board_leds.h $(I03)/leds.h $(I00)/diag_sys.h $(I03)/dbgtrc.h $(I01)/board_headers.h $(I03)/tcv_defs.h $(I03)/sysio.h
	mkdir -p $(TD)
	$(CC) $(CF) $(OF) $(IN) -c $(S03)/ser_outb.c -o $(TD)/ser_outb.o

$(TD)/ser_in.o : $(S03)/ser_in.c $(I01)/board_options.sys $(I03)/modsyms.h $(I00)/supplement.h $(I00)/portnames.h $(I00)/arch.h $(I00)/mach.h $(I00)/uart_def.h $(I00)/leds_sys.h $(I01)/board_leds.h $(I03)/leds.h $(I00)/diag_sys.h $(I03)/dbgtrc.h $(I01)/board_headers.h $(I03)/tcv_defs.h $(I03)/sysio.h
	mkdir -p $(TD)
	$(CC) $(CF) $(OF) $(IN) -c $(S03)/ser_in.c -o $(TD)/ser_in.o

$(TD)/plug_null.o : $(S03)/plug_null.c $(I01)/board_options.sys $(I03)/modsyms.h $(I00)/supplement.h $(I00)/portnames.h $(I00)/arch.h $(I00)/mach.h $(I00)/uart_def.h $(I00)/leds_sys.h $(I01)/board_leds.h $(I03)/leds.h $(I00)/diag_sys.h $(I03)/dbgtrc.h $(I01)/board_headers.h $(I03)/tcv_defs.h $(I03)/sysio.h $(I03)/tcvplug.h $(I04)/plug_null_node_data.h
	mkdir -p $(TD)
	$(CC) $(CF) $(OF) $(IN) -c $(S03)/plug_null.c -o $(TD)/plug_null.o

$(TD)/sensors.o : $(S02)/sensors.c $(I01)/board_options.sys $(I03)/modsyms.h $(I00)/supplement.h $(I00)/portnames.h $(I00)/arch.h $(I00)/mach.h $(I00)/uart_def.h $(I00)/leds_sys.h $(I01)/board_leds.h $(I03)/leds.h $(I00)/diag_sys.h $(I03)/dbgtrc.h $(I01)/board_headers.h $(I03)/tcv_defs.h $(I03)/sysio.h $(I00)/sensors_sys.h $(I03)/sensors.h $(I03)/analog_sensor.h $(I01)/board_pins.h $(I00)/pins_sys.h $(I03)/pins.h
	mkdir -p $(TD)
	$(CC) $(CF) $(OF) $(IN) -c $(S02)/sensors.c -o $(TD)/sensors.o

$(TD)/analog_sensor.o : $(S02)/analog_sensor.c $(I01)/board_options.sys $(I03)/modsyms.h $(I00)/supplement.h $(I00)/portnames.h $(I00)/arch.h $(I00)/mach.h $(I00)/uart_def.h $(I00)/leds_sys.h $(I01)/board_leds.h $(I03)/leds.h $(I00)/diag_sys.h $(I03)/dbgtrc.h $(I01)/board_headers.h $(I03)/tcv_defs.h $(I03)/sysio.h $(I03)/ualeds.h $(I03)/uart.h $(I00)/sensors_sys.h $(I03)/sensors.h $(I03)/analog_sensor.h $(I01)/board_pins.h $(I00)/pins_sys.h $(I03)/pins.h $(I02)/kernel.h
	mkdir -p $(TD)
	$(CC) $(CF) $(OF) $(IN) -c $(S02)/analog_sensor.c -o $(TD)/analog_sensor.o

$(TD)/pins_sys.o : $(S01)/pins_sys.c $(I01)/board_options.sys $(I03)/modsyms.h $(I00)/supplement.h $(I00)/portnames.h $(I00)/arch.h $(I00)/mach.h $(I00)/uart_def.h $(I00)/leds_sys.h $(I01)/board_leds.h $(I03)/leds.h $(I00)/diag_sys.h $(I03)/dbgtrc.h $(I01)/board_headers.h $(I03)/tcv_defs.h $(I03)/sysio.h $(I03)/ualeds.h $(I03)/uart.h $(I00)/sensors_sys.h $(I03)/sensors.h $(I03)/analog_sensor.h $(I01)/board_pins.h $(I00)/pins_sys.h $(I03)/pins.h $(I02)/kernel.h $(I00)/pins_sys_in.h $(I00)/pins_sys_out.h
	mkdir -p $(TD)
	$(CC) $(CF) $(OF) $(IN) -c $(S01)/pins_sys.c -o $(TD)/pins_sys.o

$(TD)/p1irq.o : $(S01)/p1irq.c $(I01)/board_options.sys $(I03)/modsyms.h $(I00)/supplement.h $(I00)/portnames.h $(I00)/arch.h $(I00)/mach.h $(I00)/uart_def.h $(I00)/leds_sys.h $(I01)/board_leds.h $(I03)/leds.h $(I00)/diag_sys.h $(I03)/dbgtrc.h $(I01)/board_headers.h $(I03)/tcv_defs.h $(I03)/sysio.h $(I03)/ualeds.h $(I03)/uart.h $(I00)/sensors_sys.h $(I03)/sensors.h $(I03)/analog_sensor.h $(I01)/board_pins.h $(I00)/pins_sys.h $(I03)/pins.h $(I02)/kernel.h $(I01)/board_rf.h $(I00)/cc1100_sys.h $(I03)/rfleds.h $(I03)/cc1100.h $(I03)/irq_cc1100.h $(I01)/board_pins_interrupts.h
	mkdir -p $(TD)
	$(CC) $(CF) $(OF) $(IN) -c $(S01)/p1irq.c -o $(TD)/p1irq.o

$(TD)/vform.o : $(S03)/vform.c $(I01)/board_options.sys $(I03)/modsyms.h $(I00)/supplement.h $(I00)/portnames.h $(I00)/arch.h $(I00)/mach.h $(I00)/uart_def.h $(I00)/leds_sys.h $(I01)/board_leds.h $(I03)/leds.h $(I00)/diag_sys.h $(I03)/dbgtrc.h $(I01)/board_headers.h $(I03)/tcv_defs.h $(I03)/sysio.h $(I04)/form.h
	mkdir -p $(TD)
	$(CC) $(CF) $(OF) $(IN) -c $(S03)/vform.c -o $(TD)/vform.o

$(TD)/vscan.o : $(S03)/vscan.c $(I01)/board_options.sys $(I03)/modsyms.h $(I00)/supplement.h $(I00)/portnames.h $(I00)/arch.h $(I00)/mach.h $(I00)/uart_def.h $(I00)/leds_sys.h $(I01)/board_leds.h $(I03)/leds.h $(I00)/diag_sys.h $(I03)/dbgtrc.h $(I01)/board_headers.h $(I03)/tcv_defs.h $(I03)/sysio.h $(I04)/form.h
	mkdir -p $(TD)
	$(CC) $(CF) $(OF) $(IN) -c $(S03)/vscan.c -o $(TD)/vscan.o

$(TD)/__outserial.o : $(S03)/__outserial.c $(I01)/board_options.sys $(I03)/modsyms.h $(I00)/supplement.h $(I00)/portnames.h $(I00)/arch.h $(I00)/mach.h $(I00)/uart_def.h $(I00)/leds_sys.h $(I01)/board_leds.h $(I03)/leds.h $(I00)/diag_sys.h $(I03)/dbgtrc.h $(I01)/board_headers.h $(I03)/tcv_defs.h $(I03)/sysio.h
	mkdir -p $(TD)
	$(CC) $(CF) $(OF) $(IN) -c $(S03)/__outserial.c -o $(TD)/__outserial.o

$(TD)/__inserial.o : $(S03)/__inserial.c $(I01)/board_options.sys $(I03)/modsyms.h $(I00)/supplement.h $(I00)/portnames.h $(I00)/arch.h $(I00)/mach.h $(I00)/uart_def.h $(I00)/leds_sys.h $(I01)/board_leds.h $(I03)/leds.h $(I00)/diag_sys.h $(I03)/dbgtrc.h $(I01)/board_headers.h $(I03)/tcv_defs.h $(I03)/sysio.h
	mkdir -p $(TD)
	$(CC) $(CF) $(OF) $(IN) -c $(S03)/__inserial.c -o $(TD)/__inserial.o

$(TD)/pins_sys_in.o : $(S01)/pins_sys_in.c $(I01)/board_options.sys $(I03)/modsyms.h $(I00)/supplement.h $(I00)/portnames.h $(I00)/arch.h $(I00)/mach.h $(I00)/uart_def.h $(I00)/leds_sys.h $(I01)/board_leds.h $(I03)/leds.h $(I00)/diag_sys.h $(I03)/dbgtrc.h $(I01)/board_headers.h $(I03)/tcv_defs.h $(I03)/sysio.h $(I00)/sensors_sys.h $(I03)/sensors.h $(I03)/analog_sensor.h $(I01)/board_pins.h $(I00)/pins_sys.h
	mkdir -p $(TD)
	$(CC) $(CF) $(OF) $(IN) -c $(S01)/pins_sys_in.c -o $(TD)/pins_sys_in.o

$(TD)/pins_sys_out.o : $(S01)/pins_sys_out.c $(I01)/board_options.sys $(I03)/modsyms.h $(I00)/supplement.h $(I00)/portnames.h $(I00)/arch.h $(I00)/mach.h $(I00)/uart_def.h $(I00)/leds_sys.h $(I01)/board_leds.h $(I03)/leds.h $(I00)/diag_sys.h $(I03)/dbgtrc.h $(I01)/board_headers.h $(I03)/tcv_defs.h $(I03)/sysio.h $(I00)/sensors_sys.h $(I03)/sensors.h $(I03)/analog_sensor.h $(I01)/board_pins.h $(I00)/pins_sys.h
	mkdir -p $(TD)
	$(CC) $(CF) $(OF) $(IN) -c $(S01)/pins_sys_out.c -o $(TD)/pins_sys_out.o

$(TD)/kernel.o : $(S04)/kernel.c $(I01)/board_options.sys $(I03)/modsyms.h $(I00)/supplement.h $(I00)/portnames.h $(I00)/arch.h $(I00)/mach.h $(I00)/uart_def.h $(I00)/leds_sys.h $(I01)/board_leds.h $(I03)/leds.h $(I00)/diag_sys.h $(I03)/dbgtrc.h $(I01)/board_headers.h $(I03)/tcv_defs.h $(I03)/sysio.h $(I03)/ualeds.h $(I03)/uart.h $(I00)/sensors_sys.h $(I03)/sensors.h $(I03)/analog_sensor.h $(I01)/board_pins.h $(I00)/pins_sys.h $(I03)/pins.h $(I02)/kernel.h $(I03)/tcv.h
	mkdir -p $(TD)
	$(CC) $(CF) $(OF) $(IN) -c $(S04)/kernel.c -o $(TD)/kernel.o



clean :
	rm -rf $(TD)/*
