/*
  RealTimeClock.c
  MSP430RealTimeOS
 
 Uses the watchdog timer (WDT) to produce an interrupt every 0.5ms and update the 32 bit time_ms variable that holds
 the elapsed time since the microcontroller was reset.
 
 Also includes a software debounce for the switch S2 on the launchpad
 
 Created by Benn Thomsen on 20/10/2015.
 Copyright (c) 2014 Benn Thomsen.
*/

#include "RealTimeClock.h"
#include "print.h"

#define INCR 1UL

volatile char button1;
unsigned long switchholdoff_event;
static unsigned long tacho_event = TACHOSTART;

void RTCConfigure(void){
  WDTCTL = WDTPW + WDTHOLD; // Stop WDT
  BCSCTL1 = CALBC1_16MHZ;   // Set DCO to 16MHz
  DCOCTL = CALDCO_16MHZ;    // Set DCO to 16MHz
  WDTCTL = WDT_MDLY_8;      // WDT configured as a 0.5ms interval timer with the 16MHz clock
  IE1 |= WDTIE;             // Enable WDT interrupt
  
  time500us = 0;
  time_ms = 0;
  ms = 0;
  seconds = 0;
  minutes = 0;
  hours = 0;
}

void SwitchConfigure(void){
/* Define input pin functionality for switches */
    P1SEL &= ~(SW2 | TACHO);
    P1SEL2 &= ~(SW2 | TACHO);
    P1DIR &= ~(SW2 | TACHO);  // Set switch pin as an input
    P1OUT |= SW2;    // Set pull up resistor on for button
    P1REN |= SW2;    // Enable pullup or pulldown resistors
    P1IES |= (SW2 | TACHO);    // Enable Interrupt to trigger on the falling edge (high (unpressed) to low (pressed) transition)
    P1IFG &= ~(SW2 | TACHO);   // Clear the interrupt flag for the button
    P1IE |= (SW2 | TACHO);      // Enable interrupts on port 1 for the button
    
    pressReleaseSW2 = 0;
    pressSW2 = 0;
    switchholdoff_event = 0;
    
    tachometer = 0;
}

void TachoEvent(void){
        if (tacho_event && (time_ms >= tacho_event)) {
          tacho_event=time_ms+TACHODELAY;      // Schedule repeat event
          printformat("Tacho: %i \r\n",tachometer);  // Send formatted ADC reading to UART
          tachometer = 0;  
        }
}

#pragma vector=WDT_VECTOR
__interrupt void watchdog_timer (void){
  if(++time500us == 2){
    time500us = 0;
    time_ms = time_ms + INCR;
      if (++ms == 1000){
          ms = 0;
         //P1OUT ^= BIT0;            // Toggle LED1 on P1.0 every second (Used for testing)
          if (++seconds == 60){
              seconds = 0;
              if (++minutes == 60){
                  minutes = 0;
                  if (++hours == 24){
                      hours = 0;
                  }
              }
          }
      }
   if (switchholdoff_event && (time_ms >= switchholdoff_event))
      {
        switchholdoff_event = 0;  
        P1IE |= button1;     // Enable interrupts on port 1 for the button     
      }
    __bic_SR_register_on_exit(CPUOFF);  /* Exit Low Power Mode 0 */
  }
}

/* Port 1 interrupt to service the button press */
#pragma vector=PORT1_VECTOR
__interrupt void PORT1_ISR(void) {
    P1IE = 0x00; // Disable All Port 1 interrupts
    if (P1IFG & TACHO) {
      P1IFG &= ~TACHO;               // Clear the interrupt flag for the tacho input
      tachometer++;
      P1IE |= TACHO;                // Enable Tacho interrupt
    }
    
    button1 = P1IFG & SW2;   // Read PORT1 interrupt flag to determine source pin masking off Switch Inputs
    if (button1){
        P1IFG &= ~button1;               // Clear the interrupt flag for the button
        
        if (P1IES & button1) {
            P1IES &= ~button1;           // Clear edge select to detect rising edge
            pressSW2 = button1;
        }
        else {
            P1IES |= button1;            // Set edge select to detect falling edge
            pressReleaseSW2 = button1;
        }  
      switchholdoff_event = time_ms + SWITCHDELAY;
    }
    else P1IE |= SW2;                // Enable Button interrupt
}

