/*
  RealTimeClock.h
  MSP430RealTimeOS
 
 Uses the watchdog timer (WDT) to produce an interrupt every 0.5ms. The elapsed time in milliseconds since the microcontroller reset is stored in the variable time_ms
 as a 32bit unsigned integer. time_ms will overflow in approximately 49 days.
 
 Also includes a software debounce for the switch S2 on the launchpad that uses the realtime clock to produce a holdoff to avoid the switching cliches.

 Created by Benn Thomsen on 18/10/2015.
*/


#ifndef MSP430G2553
#define MSP430G2553
#include <msp430g2553.h>
#endif

volatile unsigned char time500us;
volatile unsigned long time_ms;
volatile unsigned int ms;
volatile unsigned int seconds;
volatile unsigned int minutes;
volatile unsigned int hours;

volatile unsigned int tachometer;

int pressReleaseSW2;
int pressSW2;

#define MAXTIME_MS 0xFFFFFFFF
#define SW2 BIT3
#define SWITCHDELAY 100UL         // Switch debounce holdoff time in ms

#define TACHO BIT7
#define TACHOSTART 1400UL
#define TACHODELAY 1000UL

void RTCConfigure(void);
void SwitchConfigure(void);
void TachoEvent(void);
