/*
  Fade
 
  This example shows how to fade an LED on pin 14
  using the analogWrite() function.
 
  Hardware Required:
  * MSP-EXP430G2 LaunchPad
  
  This example code is in the public domain.
 
*/

int motorspeed = 100;    // how bright the LED is



  void setup()  { 
    // declare pin 14 to be an output:
    pinMode(P1_0, OUTPUT);
    pinMode(P2_1, OUTPUT);
    pinMode(P2_4, OUTPUT);
    /* Set PWM frequency to 20 KHz */
    analogFrequency(20000);
    
    digitalWrite(P1_0, HIGH);
/* PWM on P2.1 (aka pin 9) with 50% duty cycle */
    analogWrite(P2_1, motorspeed); 
    analogWrite(P2_4, motorspeed);
  } 
  
  void loop()  { 


                              
  }
