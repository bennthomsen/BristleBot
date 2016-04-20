/*
  CapTouchButton
  CapTouch library example for the capacitive booster pack
  http://www.ti.com/tool/430boost-sense1
  
  This example demonstrates turning on the middle
  led when one of the four buttons is touched.

  Created 2012 by Robert Wessels from http://energia.nu
 
  This example code is in the public domain.
*/
 
#include <CapTouch.h>

#define ONOFF_BUTTON P1_0
#define LEFT_BUTTON P1_3
#define CENTRE_BUTTON P1_4
#define RIGHT_BUTTON P1_5

#define RUNLED P2_3

#define OFF 0
#define PRESSON 1
#define ON 2
#define PRESSOFF 3

uint8_t onstate = 0;
uint8_t leftspeed = 50;
uint8_t rightspeed = 50;

uint16_t measured, base;
/* Delta can be negative */
int16_t delta;

CapTouch onoff = CapTouch(ONOFF_BUTTON, TOUCH_BUTTON);
CapTouch left = CapTouch(LEFT_BUTTON, TOUCH_BUTTON);
CapTouch centre = CapTouch(CENTRE_BUTTON, TOUCH_BUTTON);
CapTouch right = CapTouch(RIGHT_BUTTON, TOUCH_BUTTON);

// Function Prototypes
void StopMotor(void);
void SetMotorSpeed(uint8_t speedleft, uint8_t speedright);

void setup() {

  pinMode(RUNLED, OUTPUT);      //define pin 11 as an output for an LED
  pinMode(P2_1, OUTPUT);      //define pin 9 as an output for PWM output to drive the left vibromotor
  pinMode(P2_4, OUTPUT);      //define pin 12 as an output for PWM output to drive the right vibromotor
  StopMotor();
  analogFrequency(20000);     //Set PWM frequency to 20 KHz
  onoff.setThreshold(5000);  // Set threshold for the touch button (0 - 15000)
  left.setThreshold(5000);  // Set threshold for the touch button (0 - 15000)
  centre.setThreshold(5000);  // Set threshold for the touch button (0 - 15000)
  right.setThreshold(5000);  // Set threshold for the touch button (0 - 15000)
  Serial.begin(9600);
  Serial.println("Initialising");
  
  digitalWrite(RUNLED, LOW);    //Turn On LED
}

void loop() {
  /* State will be 1 if any of the buttons was touched, otherwise 0 */
  onoff.isTouched();
  measured = onoff.getMeasured();
  base = onoff.getBaseline();
  delta = onoff.getDelta();
  Serial.print("Onoff "); 
  Serial.print("Base: ");
  Serial.print(base);  
  Serial.print("\tMeasured: ");
  Serial.print(measured);  
  Serial.print("\tDelta: ");
  Serial.println(delta); 
  
  left.isTouched();
  measured = left.getMeasured();
  base = left.getBaseline();
  delta = left.getDelta();
  Serial.print("Left "); 
  Serial.print("Base: ");
  Serial.print(base);  
  Serial.print("\tMeasured: ");
  Serial.print(measured);  
  Serial.print("\tDelta: ");
  Serial.println(delta); 
  
  centre.isTouched();
  measured = centre.getMeasured();
  base = centre.getBaseline();
  delta = centre.getDelta();
  Serial.print("Centre "); 
  Serial.print("Base: ");
  Serial.print(base);  
  Serial.print("\tMeasured: ");
  Serial.print(measured);  
  Serial.print("\tDelta: ");
  Serial.println(delta); 
  
  right.isTouched();
  measured = right.getMeasured();
  base = right.getBaseline();
  delta = right.getDelta();
  Serial.print("Right "); 
  Serial.print("Base: ");
  Serial.print(base);  
  Serial.print("\tMeasured: ");
  Serial.print(measured);  
  Serial.print("\tDelta: ");
  Serial.println(delta); 
  
  switch (onstate) {
   case OFF:
      if (onoff.isTouched()) {            //Check if touch pad is pressed
        onstate = PRESSON;
        digitalWrite(RUNLED, HIGH);        //Turn On LED
        //Serial.println("Starting Motors");
        SetMotorSpeed(leftspeed, rightspeed);
      }
      break;
      case PRESSON:
      if (!onoff.isTouched()) {           //Check if touch pad is not pressed
        onstate = ON;
      }
      break;
      case ON:
      if (onoff.isTouched()) {
        onstate = PRESSOFF;
        digitalWrite(RUNLED, LOW);         //Turn Off LED
        //Serial.println("Stopping Motors");
        StopMotor();
      }
      break;
      case PRESSOFF:
      if (!onoff.isTouched()) {
        onstate = OFF;
      }
      break;
  }
  delay(20);
}

void SetMotorSpeed(uint8_t speedleft, uint8_t speedright) {
  analogWrite(P2_1, speedleft); 
  analogWrite(P2_4, speedright);
}

void StopMotor(void) {
  analogWrite(P2_1, 0); 
  analogWrite(P2_4, 0);
}
  
