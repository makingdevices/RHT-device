# MPLAB IDE generated this makefile for use with GNU make.
# Project: RHT-device.mcp
# Date: Wed Aug 10 19:33:32 2022

AS = MPASMWIN.exe
CC = mcc18.exe
LD = mplink.exe
AR = mplib.exe
RM = rm

RHT-device.cof : source_TESTED.o
	$(LD) /p18LF14K50 /l"C:\Program Files (x86)\Microchip\mplabc18\v3.47\lib" "source_TESTED.o" /u_CRUNTIME /z__MPLAB_BUILD=1 /o"RHT-device.cof" /M"RHT-device.map" /W

source_TESTED.o : source_TESTED.c ../../../../../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.47/h/delays.h ../../../../../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.47/h/i2c.h source_TESTED.c ../../../../../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.47/h/p18f14k50.h ../../../../../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.47/h/pconfig.h ../../../../../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.47/h/p18cxxx.h ../../../../../../../../Program\ Files\ (x86)/Microchip/mplabc18/v3.47/h/p18lf14k50.h
	$(CC) -p=18LF14K50 "source_TESTED.c" -fo="source_TESTED.o" -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

clean : 
	$(RM) "source_TESTED.o" "RHT-device.cof" "RHT-device.hex"

