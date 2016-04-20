/*
BristleBot Dual motor speed control
*/

// define pin assignments
#define PWRLED P2_5

#define RIGHTMOTOR P2_4
#define LEFTMOTOR P2_1


void setup() {                
  // initialize the digital pin as an output.
  pinMode(PWRLED, OUTPUT);   
  pinMode(RIGHTMOTOR, OUTPUT); 
  pinMode(LEFTMOTOR, OUTPUT); 
  
  analogFrequency(20000);    // Set the pulse frequency of the PWM motor drive signal
  
  analogWrite(RIGHTMOTOR,0);  //Set the Right motor power (0-255)
  analogWrite(LEFTMOTOR,0);   //Set the Left motor power (0-255)
}
   
// the loop routine runs over and over again forever:
void loop() {
  
  // Heartbeat (2 second period)
  digitalWrite(PWRLED, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(1000);               // wait for a second
  digitalWrite(PWRLED, HIGH);    // turn the LED off by making the voltage LOW
  delay(1000);               // wait for a second
}
