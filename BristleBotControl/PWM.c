 #include "PWM.h"
 
 void PWMConfigure0(int count){
    /* Configure timer A0 as a pulse width modulator */
    TA0CCR0 = count;           // Set maximum count value to determine PWM Frequency = SMCLK/TACCR0 (16MHz/count)
    TA0CCR1 = 0;             // Initialise counter compare value 1 to control Duty Cycle = TACCR1/TACCR0 (0/count = 0%)
    
    TA0CCTL1 = OUTMOD_7;          // Set output to on when counter resets and off when counter equals TACCR1. Normal PWM.
    TA0CTL = TASSEL_2 | ID_0 | MC_1;     // Use the SMCLK to clock the counter, divider: SMCLK/1, and set to count up mode
   // P1IE = PROX;     // Enable interrupts on port 1 for the proximaty sensor   
    //TA0CCTL0 = CM_1 | CCIS_0 | SCS | CAP | CCIE ;    // Raising Edge + CCI0A + Sync + Capture Mode + Interrupt enable
     //P1SEL |= BIT5; //set this bit as Input Capture (TA0.CCI0A)
    
    P1DIR |= PWM1_6;               // Set P1.6 as output
    P1SEL |= PWM1_6;               // Select output P1.6 to be TA0.1
    P1SEL2 &= ~PWM1_6;             // Select output P1.6 to be TA0.1
 }
 
 void PWMConfigure1(int count){
 /* Configure timer A1 as a pulse width modulator */
    TA1CTL = TASSEL_2 |ID_0 | MC_1 ;     // Use the SMCLK to clock the counter, divider: SMCLK/1, and set to count up mode
    TA1CCR0 = count;             // Initialise counter compare 0 to set maximum count value to determine PWM Frequency = SMCLK/TACCR0 (16MHz/800 = 20kHz)
    
    TA1CCR1 = 0;                // Initialise counter compare 1 to control Duty Cycle = TACCR1/TACCR0 (0%)
    TA1CCTL1 = OUTMOD_7;        // Set output to on when counter resets and off when counter equals TACCR1. Normal PWM.
    
    TA1CCR2 = 0;                // Initialise counter compare 2 to control Duty Cycle = TACCR2/TACCR0 (0%)
    TA1CCTL2 = OUTMOD_7;        // Set output to on when counter resets and off when counter equals TACCR2. Normal PWM.
     
    P2DIR |= PWM2_4;               // Set P2.4 as output
    P2SEL |= PWM2_4;               // Select output P2.4 to be Timer A1 counter compare register 1 (TA1.2)
    P2SEL2 &= ~PWM2_4;             // Select output P2.4 to be Timer A1 counter compare register 1 (TA1.2)
    
    P2DIR |= PWM2_1;               // Set P2.1 as output
    P2SEL |= PWM2_1;               // Select output P2.1 to be Timer A1 counter compare register 1 (TA1.1)
    P2SEL2 &= ~PWM2_1;             // Select output P2.1 to be Timer A1 counter compare register 1 (TA1.1)     
    }
    

 
  void PWMSetWidth0_1(int width){
   TA0CCR1 = width;
 }
 
 void PWMSetWidth1_1(int width){
   TA1CCR1 = width;
 }
 
  void PWMSetWidth1_2(int width){
   TA1CCR2 = width;
 }
