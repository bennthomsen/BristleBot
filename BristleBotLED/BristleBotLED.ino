/*
BristleBot Dual motor speed control
*/

// define pin assignments
#define PWRLED P2_5

void setup() {                
  // initialize the digital pin as an output.
  pinMode(PWRLED, OUTPUT);   
}
   
// the loop routine runs over and over again forever:
void loop() {
  
  // Heartbeat (2 second period)
  digitalWrite(PWRLED, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(100);               // wait for a second
  digitalWrite(PWRLED, HIGH);    // turn the LED off by making the voltage LOW
  delay(100);               // wait for a second
}
