# MPLAB IDE generated this makefile for use with GNU make.
# Project: RHT-device.mcp
# Date: Thu May 11 18:57:56 2023

AS = MPASMWIN.exe
CC = mcc18.exe
LD = mplink.exe
AR = mplib.exe
RM = rm

RHT-device.cof : source_TESTED.o
	$(LD) /p18F14K50 /l"C:\Program Files (x86)\Microchip\mplabc18\v3.47\lib" "source_TESTED.o" /u_CRUNTIME /z__MPLAB_BUILD=1 /o"RHT-device.cof" /M"RHT-device.map" /W

source_TESTED.o : source_TESTED.c C:/Program\ Files\ (x86)/Microchip/mplabc18/v3.47/h/delays.h C:/Program\ Files\ (x86)/Microchip/mplabc18/v3.47/h/i2c.h source_TESTED.c C:/Program\ Files\ (x86)/Microchip/mplabc18/v3.47/h/p18f14k50.h C:/Program\ Files\ (x86)/Microchip/mplabc18/v3.47/h/pconfig.h C:/Program\ Files\ (x86)/Microchip/mplabc18/v3.47/h/p18cxxx.h
	$(CC) -p=18F14K50 "source_TESTED.c" -fo="source_TESTED.o" -Ou- -Ot- -Ob- -Op- -Or- -Od- -Opa-

clean : 
	$(RM) "source_TESTED.o" "RHT-device.cof" "RHT-device.hex"

