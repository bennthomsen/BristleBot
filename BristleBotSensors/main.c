#include "UART.h"
#include "print.h"

#define PWRLED BIT5
#define RIGHTMOTOR BIT4              // LCD Shield Switch 1 (P2.4)
#define LEFTMOTOR BIT1              // LCD Shield Switch 1 (P2.4)

#define IRLED BIT6

#define RIGHTPROX BIT4
#define LEFTPROX BIT5
#define PROX (LEFTPROX | RIGHTPROX)

int count = 0;
char input = 0;

int main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop WDT
    BCSCTL1 = CALBC1_16MHZ; // Set DCO to 1MHz
    DCOCTL = CALDCO_16MHZ; // Set DCO to 1MHz
    
    UARTConfigure();
    
    P2DIR |= PWRLED;               // Set P2.4 as output
    P2OUT |= PWRLED;
    //P2OUT &= ~PWRLED;
    
    P1SEL &= ~ PROX;
    P1SEL2 &= ~ PROX;
    P1DIR &= ~ PROX;  // Set switch pin as an input
    P1OUT |= PROX;    // Set pull up resistor on for button
    P1REN |= PROX;    // Enable pullup or pulldown resistors
    P1IES &= ~PROX;    // Enable Interrupt to trigger on the rising edge
    P1IFG &= ~PROX;   // Clear the interrupt flag for the button
    
    
  /* Configure timer A1 as a pulse width modulator */
    TA1CCR0 = 420;             // Set maximum count value to determine PWM Frequency = SMCLK/TACCR0 (1MHz/1000 = 1kHz)
    TA1CCR1 = 0;             // Initialise counter compare value 1 to control Duty Cycle = TACCR1/TACCR0 (500/1000 = 50%)
    TA1CCR2 = 0;             // Initialise counter compare value 1 to control Duty Cycle = TACCR1/TACCR0 (500/1000 = 50%)
    
    TA1CCTL2 = OUTMOD_7;          // Set output to on when counter resets and off when counter equals TACCR1. Normal PWM.
    TA1CCTL1 = OUTMOD_7;          // Set output to on when counter resets and off when counter equals TACCR1. Normal PWM.
    TA1CTL = TASSEL_2 + MC_1;     // Use the SMCLK to clock the counter and set to count up mode
    
    P2DIR |= RIGHTMOTOR;               // Set P2.4 as output
    P2SEL |= RIGHTMOTOR;               // Select output P2.4 to be TA1.2
    P2SEL2 &= ~RIGHTMOTOR;             // Select output P2.4 to be TA1.2
    
    P2DIR |= LEFTMOTOR;               // Set P2.1 as output
    P2SEL |= LEFTMOTOR;               // Select output P2.1 to be TA1.1
    P2SEL2 &= ~LEFTMOTOR;             // Select output P2.1 to be TA1.1
    
    /* Configure timer A0 as a pulse width modulator */
    TA0CCR0 = 422;             // Set maximum count value to determine PWM Frequency = SMCLK/TACCR0 (1MHz/1000 = 1kHz)
    TA0CCR1 = 5;             // Initialise counter compare value 1 to control Duty Cycle = TACCR1/TACCR0 (500/1000 = 50%)
    
    TA0CCTL1 = OUTMOD_7;          // Set output to on when counter resets and off when counter equals TACCR1. Normal PWM.
    TA0CTL = TASSEL_2 | MC_1 | TAIE;     // Use the SMCLK to clock the counter and set to count up mode
    P1IE = PROX;     // Enable interrupts on port 1 for the proximaty sensor
    
    //TA0CCTL0 = CM_1 | CCIS_0 | SCS | CAP | CCIE ;    // Raising Edge + CCI0A + Sync + Capture Mode + Interrupt enable
     //P1SEL |= BIT5; //set this bit as Input Capture (TA0.CCI0A)
    
    P1DIR |= IRLED;               // Set P1.6 as output
    P1SEL |= IRLED;               // Select output P1.6 to be TA0.1
    P1SEL2 &= ~IRLED;             // Select output P1.6 to be TA0.1
    
    WDTCTL = WDT_MDLY_8;        // Start and set watchdog timer (WDT) to trigger every 0ms
    //IFG1 &= ~WDTIFG;                // Clear the interrupt flag for the WDT
    IE1 |= WDTIE;                   // enable WDT interrupt

    
    __bis_SR_register(CPUOFF + GIE); // LPM0 with interrupts enabled
    
}

// WDT Interrupt Service Routine used to de-bounce button press
#pragma vector=WDT_VECTOR
__interrupt void WDT_ISR(void)
{
    //IFG1 &= ~WDTIFG;                 // clear WDT interrupt flag
    count++;
    if(count > 240){
     P2OUT |= PWRLED;
     TA0CTL = MC_0;
     P2OUT &= ~IRLED;
     
     P1IFG &= ~PROX;   // Clear the interrupt flag for the button
     P1IE &= ~PROX;     // Enable interrupts on port 1 for the proximaty sensor
     
    }
    
    if(count > 2240){
      count=10;
     P2OUT &= ~PWRLED;
     TA0CTL = TASSEL_2 + MC_1;
     P1IFG &= ~PROX;   // Clear the interrupt flag for the button
     P1IE = PROX;     // Enable interrupts on port 1 for the proximaty sensor
     
    }

}

#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A (void)
    {
        UARTSendString("Capture"); 
    }
 
 /* Port 1 interrupt to service the button press */
#pragma vector=PORT1_VECTOR
__interrupt void PORT1_ISR(void)
{
    input = P1IFG & PROX;
    switch(input){
      case RIGHTPROX:
        P1IE &= ~RIGHTPROX;                // Disable Button interrupt
        P1IFG &= ~RIGHTPROX;               // Clear the interrupt flag for the button
        printformat("Right: %4i \r\n", count);
        break;
      case LEFTPROX:
        P1IE &= ~LEFTPROX;                // Disable Button interrupt
        P1IFG &= ~LEFTPROX;               // Clear the interrupt flag for the button
        printformat("Left: %4i \r\n", count);
        break;
      case PROX:
        P1IE &= ~PROX;                // Disable Button interrupt
        P1IFG &= ~PROX;               // Clear the interrupt flag for the button
        printformat("Both: %4i \r\n", count);
        break;
    }
}
