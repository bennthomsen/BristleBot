/* Configures the ADC to use the internal 1.5V reference which is output from pin 6 (P1.4) this has the advantage
that the 1.5V reference is also suitable for the measuring the internal temperature using channel 10
*/
#include "ADC.h"

void ADCConfigure(void)
{
 /* Configure ADC*/
    ADC10CTL0=SREF_0 + ADC10ON + ADC10SHT_3 + ADC10IE ; //Vcc ref, Ref on, 64 clocks for sample
    ADC10CTL1=ADC10DIV_3; //clock/4
    ADCflag = 0;
    ADCbusy = 0;
}

void ADCAcquireInternalTemp(void)
{
 /* Configure ADC Channel */
 ADC10CTL1=INCH_10;
 ADC10CTL0 |= ENC + ADC10SC;
}

int ConvertADCtoDegC(int value){
int IntDegC = ((value * 27069L - 18169625L) >> 16);
return IntDegC;
}

void ADCAcquireChannel(char channel)
{
 /* Configure ADC Channel */
 ADC10CTL1 = channel << 12;
 ADC10CTL0 |= ENC + ADC10SC;
}


// ADC10 interrupt service routine
#pragma vector=ADC10_VECTOR
__interrupt void ADC10_ISR (void)
{
  ADCvalue = ADC10MEM; // read ADC value (note this is a 10bit value stored in a 16 bit register)
  ADC10CTL0 &= ~ENC;
  ADCflag = 1;
  ADCbusy = 0;
 __bic_SR_register_on_exit(CPUOFF); // Return to active mode
}

