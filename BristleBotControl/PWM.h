#ifndef MSP430G2553
#define MSP430G2553
#include <msp430g2553.h>
#endif

#define  PWM1_6 BIT6   // TA0.1
#define  PWM2_6 BIT6   // TA0.1

#define PWM2_1 BIT1   // TA1.1
#define PWM2_2 BIT2   // TA1.1
#define PWM2_4 BIT4   // TA1.2
#define PWM2_5 BIT5   // TA1.2

void PWMConfigure0(int count);
void PWMConfigure1(int count);
void PWMSetWidth0_1(int width);
void PWMSetWidth1_1(int width);
void PWMSetWidth1_2(int width);
