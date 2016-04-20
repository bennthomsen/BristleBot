#ifndef MSP430G2553
#define MSP430G2553
#include <msp430g2553.h>
#endif

volatile int ADCvalue;
volatile char ADCflag;
volatile char ADCbusy;

void ADCConfigure(void);
void ADCAcquireInternalTemp(void);
int ConvertADCtoDegC(int value);
void ADCAcquireChannel(char channel);

