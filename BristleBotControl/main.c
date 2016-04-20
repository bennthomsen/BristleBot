
#include "RealTimeClock.h"
#include "PWM.h"
#include "ADC.h"
#include "UART.h"
#include "print.h"


/* Main function */

#define EVENTSTART0 1000UL
#define EVENTDELAY0 1000UL

#define EVENTSTART1 1100UL
#define EVENTDELAY1 1000UL

#define EVENTSTART2 1200UL
#define EVENTDELAY2 2000UL

#define EVENTSTART3 1300UL
#define EVENTDELAY3 2000UL

#define TACHOSTART 1400UL
#define TACHODELAY 1000UL



static unsigned long hearton_event = EVENTSTART0;
static unsigned long tacho_event = TACHOSTART;
static unsigned long heartoff_event = MAXTIME_MS;
static unsigned long event1 = EVENTSTART1;
static unsigned long event2 = EVENTSTART2;
static unsigned long event3 = EVENTSTART3;

#define OFF 0
#define DIM 1
#define BRIGHT 2
#define ON 3
volatile char mainstate = 0;

#define LEFTLDR 0
#define RIGHTLDR 1
volatile char ADCchannel;


volatile char heartbeat;
volatile int heartrate = 1000;
# define HEARTONTIME 2

int main(void)
{

    
    P1DIR |= (BIT0);              // P1.2 to output
    P1OUT &= ~BIT0;            // Toggle LED1 on P1.0 every second (Used for testing)
 
    
    RTCConfigure();
    UARTConfigure();
    ADCConfigure();
    SwitchConfigure();
    PWMConfigure0(800);
    PWMSetWidth0_1(0);
    
  ADCbusy = 0;
    
    UARTPrintln("Program Start");
    
    while(1)
    {
        // Service Switch Presses
        if (pressSW2)
        {
            switch (mainstate) {
                case OFF:
                    UARTPrintln("Turn On Motor 1/2 power");      // Send string to UART
                    PWMSetWidth0_1(200);
                    mainstate = DIM;
                    break;
                case DIM:
                    UARTPrintln("Turn On Motor 3/4 power");      // Send string to UART
                    PWMSetWidth0_1(300);
                    mainstate = BRIGHT;
                    break;
                case BRIGHT:
                    UARTPrintln("Turn On Motor Full power");      // Send string to UART
                    PWMSetWidth0_1(400);
                    mainstate = ON;
                    break;
                case ON:
                    UARTPrintln("Turn Off Motor");      // Send string to UART
                    PWMSetWidth0_1(0);
                    mainstate = OFF;
                    break;
            }
          pressSW2 = 0;   
        }
        
        //Service timed events
        if (heartrate && (time_ms >= hearton_event))
        {
            hearton_event = time_ms+heartrate; // update event time
            P1OUT |= BIT0;              // Turn LED P1.0 on
            heartoff_event = time_ms+HEARTONTIME; // update triggered event time
        }
        
        if (heartoff_event && (time_ms >= heartoff_event))
        {
          heartoff_event = 0;  
          P1OUT &= ~BIT0;              // Turn LED P1.0 off     
        }
        
        TachoEvent();
        
        if (!(ADCbusy) && (time_ms >= event2))
        {
            event2=time_ms+EVENTDELAY2;      // Schedule repeat event
            UARTPrintln("Reading Right");      // Send string to UART
            ADCAcquireChannel(3);
            ADCchannel = RIGHTLDR;
            ADCbusy = 1;
        }
        
        if (!(ADCbusy) && (time_ms >= event3))
        {
            event3=time_ms+EVENTDELAY3;      // Schedule repeat event
            UARTPrintln("Reading Left");      // Send string to UART
            ADCAcquireChannel(4);
            ADCchannel = LEFTLDR;
            ADCbusy = 1;
        }
        
        
        // Service ADC flag
        if (ADCflag == 1)
        {
            ADCflag = 0;                     // Reset ADC flag to indicate that the event has been serviced
            switch (ADCchannel) {
              case LEFTLDR:
                  printformat("Left LDR: %i \r\n",ADCvalue);  // Send formatted ADC reading to UART
              break;
              case RIGHTLDR:
                  printformat("Right LDR: %i \r\n",ADCvalue);  // Send formatted ADC reading to UART
              break;
            }     
        }
        
        __bis_SR_register(CPUOFF + GIE); // LPM0 with interrupts enabled
    }
}
