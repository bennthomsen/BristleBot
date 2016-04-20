/*
  Blink
  The basic Energia example.
  Turns on an LED on for one second, then off for one second, repeatedly.
  Change the LED define to blink other LEDs.
  
  Hardware Required:
  * LaunchPad with an LED
  
  This example code is in the public domain.
*/

// most launchpads have a red LED
#define LEFTMOTOR 12

//see pins_energia.h for more LED definitions
#define RIGHTMOTOR0 11
#define GREENLED 14


#define SWITCH 5
  
// the setup routine runs once when you press reset:
void setup() { 
  pinMode(RIGHTMOTOR0, OUTPUT);
  pinMode(LEFTMOTOR, OUTPUT);
  pinMode(GREENLED, OUTPUT);
  
}

// the loop routine runs over and over again forever:
void loop() {
       
    digitalWrite(RIGHTMOTOR0, HIGH);
   digitalWrite(LEFTMOTOR, HIGH);
   digitalWrite(GREENLED, HIGH);
delay(2000);
    digitalWrite(RIGHTMOTOR0, LOW);
   digitalWrite(LEFTMOTOR, LOW);
   digitalWrite(GREENLED, LOW);
    delay(2000);

}
