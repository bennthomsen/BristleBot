/*
  BristleBot Read Potentiometer
  
  Uses the analogRead to read the ADC value the that left and
  right tuning potentiometers are attached to. The measured values
  are sent back via the serial port.
*/

#define PWRLED P2_5
#define RIGHTLED P1_0
#define LEFTLED P2_0
#define LEFTPOT P1_6
#define RIGHTPOT P1_7

int leftValue, rightValue;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  pinMode(PWRLED, OUTPUT);
  pinMode(LEFTLED, OUTPUT);
  pinMode(RIGHTLED, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(PWRLED, HIGH);
  
  leftValue = analogRead(LEFTPOT);   // read the input on pin P1.7
  rightValue = analogRead(RIGHTPOT);  // read the input on pin P1.6
  
  // turn on front LEDs if analog value from the potentiometer is greater than 512
  if (leftValue > 512){
    digitalWrite(LEFTLED, HIGH);
  }
  else {
    digitalWrite(LEFTLED, LOW);
  }
  
    if (rightValue > 512){
    digitalWrite(RIGHTLED, HIGH);
  }
  else {
    digitalWrite(RIGHTLED, LOW);
  }

    
  // print out the values you read:
  Serial.print("Right: ");
  Serial.print(rightValue);
  Serial.print(", Left: ");
  Serial.println(leftValue);
  digitalWrite(PWRLED, LOW);
  delay(500); // delay in between read
}
