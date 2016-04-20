/*
  BristleBot Read Potentiometer
  
  Uses the analogRead to read the ADC value the that left and
  right tuning potentiometers are attached to. The measured values
  are sent back via the serial port.
*/

#define LEFTPOT P1.6
#define RIGHTPOT P1.7

int leftValue, rightValue;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
  leftValue = analogRead(LEFTPOT);   // read the input on pin P1.7
  rightValue = analogRead(RIGHTPOT);  // read the input on pin P1.6
  // print out the values you read:
  Serial.print("Right: ");
  Serial.print(rightValue);
  Serial.print(", Left: ");
  Serial.println(leftValue);
  delay(500); // delay in between read
}
