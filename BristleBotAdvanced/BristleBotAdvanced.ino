/*
  BristleBot Read Potentiometer
  
  Uses the analogRead to read the ADC value the that left and
  right tuning potentiometers are attached to and then uses this to set the motor speed
*/

#define PWRLED P2_5

#define MODESWITCH P1_5

#define LEFTLED P1_0
#define RIGHTLED P2_0

#define LEFTPOT P1_6
#define RIGHTPOT P1_7

#define LEFTLDR P1_4
#define RIGHTLDR P1_3

#define LEFTMOTOR P2_1
#define RIGHTMOTOR P2_4

int leftValue, rightValue, leftLDR, rightLDR, LDRleftCurrent, LDRrightCurrent, LDRdiff;
int leftAve, rightAve, leftDiff, rightDiff, leftMotor, rightMotor;

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
  
  pinMode(MODESWITCH, INPUT);
  
  analogFrequency(20000);
  leftValue = analogRead(LEFTPOT);    // read the input on pin P1.7
  rightValue = analogRead(RIGHTPOT);  // read the input on pin P1.6
  leftAve = analogRead(LEFTLDR);    // read the input from the left LDR
  rightAve = analogRead(RIGHTLDR);  // read the input from the right LDR
  rightMotor = 0;
  leftMotor = 0;
      leftAve = leftLDR;
    rightAve = rightLDR;
  
}

// the loop routine runs over and over again forever:
void loop() {
  

  
    if(digitalRead(MODESWITCH)){
    Serial.println("Mode 1: Follow Light");
    
    LDRleftCurrent = analogRead(LEFTLDR);
    LDRrightCurrent = analogRead(RIGHTLDR);
    //leftAve = 0.9*leftAve + 0.1*LDRleftCurrent;
    //rightAve = 0.9*rightAve + 0.1*LDRrightCurrent;
    
    
    Serial.print("LDR LeftCurr=");
    Serial.print(LDRleftCurrent);
    Serial.print("LeftAve=");
    Serial.print(leftAve);
    Serial.print("RightCurr=");
    Serial.print(LDRrightCurrent);
    Serial.print("RightAve=");
    Serial.print(rightAve);
    
    if (LDRleftCurrent > (leftAve+10)) analogWrite(RIGHTMOTOR, 0);
    else analogWrite(RIGHTMOTOR, rightValue);
        if (LDRrightCurrent > (rightAve+10)) analogWrite(LEFTMOTOR, 0);
    else analogWrite(LEFTMOTOR, leftValue);

    
  }
  else {
    Serial.println("Mode 0");
    digitalWrite(PWRLED, HIGH);
    digitalWrite(LEFTLED, HIGH);
    digitalWrite(RIGHTLED, HIGH);
    //Read analogue inputs. Note: the 10bit ADC gives readings from 0 to 1023 (0 to 2^10-1)
    leftValue = analogRead(LEFTPOT);    // read the input on pin P1.7
    rightValue = analogRead(RIGHTPOT);  // read the input on pin P1.6
    
    leftLDR = analogRead(LEFTLDR);    // read the input from the left LDR
    rightLDR = analogRead(RIGHTLDR);  // read the input from the right LDR
    
    leftAve = leftLDR;
    rightAve = rightLDR;
    
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
    
    digitalWrite(LEFTLED, LOW);
    digitalWrite(RIGHTLED, LOW);
    digitalWrite(PWRLED, LOW);
  }
  
  
  delay(300); // delay in between read and motor power update
}
