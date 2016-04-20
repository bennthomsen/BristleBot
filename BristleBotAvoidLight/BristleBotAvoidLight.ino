/*
BristleBot Dual motor speed control
*/

// define pin assignments
#define PWRLED P2_5

#define RIGHTMOTOR P2_4
#define LEFTMOTOR P2_1

#define RIGHTSENSOR P1_3
#define LEFTSENSOR P1_4

int RightSensor, LeftSensor;   // variables to hold sensor readings

void setup() {                
  // initialize the digital pin as an output.
  pinMode(PWRLED, OUTPUT);   
  pinMode(RIGHTMOTOR, OUTPUT); 
  pinMode(LEFTMOTOR, OUTPUT); 
  
  analogFrequency(20000);    // Set the pulse frequency of the PWM motor drive signal
  
  analogWrite(RIGHTMOTOR,50);  //Set the Right motor power (0-255)
  analogWrite(LEFTMOTOR,50);   //Set the Left motor power (0-255)
}
   
// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(PWRLED, HIGH);    // turn the LED on by making the voltage HIGH
  RightSensor = analogRead(RIGHTSENSOR); 
  LeftSensor = analogRead(LEFTSENSOR);
  
  if (RightSensor > 500){
  analogWrite(RIGHTMOTOR,100);  //Set the Right motor power (0-255)
  }
  else{
    analogWrite(RIGHTMOTOR,0);  //Set the Right motor power (0-255)
  }
  
  if (LeftSensor > 500){
  analogWrite(LEFTMOTOR,100);  //Set the Right motor power (0-255)
  }
  else{
    analogWrite(LEFTMOTOR,0);  //Set the Right motor power (0-255)
  }
  digitalWrite(PWRLED, LOW);    // turn the LED off by making the voltage LOW
  delay(100);                   // wait for a 100ms
  
}
