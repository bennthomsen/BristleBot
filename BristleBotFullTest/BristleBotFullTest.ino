/*
  BristleBot Read Potentiometer
  
  Uses the analogRead to read the ADC value the that left and
  right tuning potentiometers are attached to and then uses this to set the motor speed
*/

#define PWRLED P2_5

#define MODESWITCH P1_3

#define LEFTLED P1_0
#define RIGHTLED P2_0

#define LEFTPOT P1_6
#define RIGHTPOT P1_7

#define LEFTLDR P1_4
#define RIGHTLDR P1_3

#define LEFTMOTOR P2_1
#define RIGHTMOTOR P2_4

int leftValue, rightValue, leftLDR, rightLDR;

// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
  
  //Setup output pins
  pinMode(PWRLED, OUTPUT);
  pinMode(LEFTLED, OUTPUT);
  pinMode(RIGHTLED, OUTPUT);
  pinMode(LEFTMOTOR, OUTPUT);
  pinMode(RIGHTMOTOR, OUTPUT);
  analogFrequency(20000);
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(PWRLED, HIGH);
  digitalWrite(LEFTLED, HIGH);
  digitalWrite(RIGHTLED, HIGH);
  //Read analogue inputs. Note: the 10bit ADC gives readings from 0 to 1023 (0 to 2^10-1)
  leftValue = analogRead(LEFTPOT);    // read the input on pin P1.7
  rightValue = analogRead(RIGHTPOT);  // read the input on pin P1.6
  
  leftLDR = analogRead(LEFTLDR);    // read the input from the left LDR
  rightLDR = analogRead(RIGHTLDR);  // read the input from the right LDR
  
  //Set motor power based on analogue input. Note: analogue write only accepts values
  //from 0 to 255 (0 to 2^8-1) so the ADC reading is divided by 4
  analogWrite(LEFTMOTOR, leftValue/4);   
  analogWrite(RIGHTMOTOR, rightValue/4);
  // print out the analogue values read:
  Serial.print("Right: Pot= ");
  Serial.print(rightValue);
  Serial.print(", LDR= ");
  Serial.print(rightLDR);
  Serial.print(", Left: Pot= ");
  Serial.print(leftValue);
  Serial.print(", LDR= ");
  Serial.println(leftLDR);
  
  digitalRead(
  digitalWrite(PWRLED, LOW);
  digitalWrite(LEFTLED, LOW);
  digitalWrite(RIGHTLED, LOW);
  delay(100); // delay in between read and motor power update
}
