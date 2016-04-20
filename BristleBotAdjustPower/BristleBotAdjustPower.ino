/*
  BristleBot Read Potentiometer
  
  Uses the analogRead to read the ADC value the that left and
  right tuning potentiometers are attached to and then uses this to set the motor speed
*/

#define PWRLED P2_5
#define LEFTPOT P1_6
#define RIGHTPOT P1_7

#define LEFTMOTOR P2_1
#define RIGHTMOTOR P2_4

int leftValue, rightValue;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  //Setup output pins
  pinMode(PWRLED, OUTPUT);
  pinMode(LEFTMOTOR, OUTPUT);
  pinMode(RIGHTMOTOR, OUTPUT);
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(PWRLED, HIGH);
  //Read analogue inputs. Note: the 10bit ADC gives readings from 0 to 1023 (0 to 2^10-1)
  leftValue = analogRead(LEFTPOT);    // read the input on pin P1.7
  rightValue = analogRead(RIGHTPOT);  // read the input on pin P1.6
  
  //Set motor power based on analogue input. Note: analogue write only accepts values
  //from 0 to 255 (0 to 2^8-1) so the ADC reading is divided by 4
  analogWrite(LEFTMOTOR, leftValue/4);   
  analogWrite(RIGHTMOTOR, rightValue/4);
  // print out the values you read:
  Serial.print("Right: ");
  Serial.print(rightValue);
  Serial.print(", Left: ");
  Serial.println(leftValue);
  
  
  digitalWrite(PWRLED, LOW);
  delay(100); // delay in between read and motor power update
}
