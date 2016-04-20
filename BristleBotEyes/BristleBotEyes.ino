/*
 This code displays the readings obtained from the two light dependent
 resistors (LDR) on the BristleBot. The readings from the Analogue to Digital
 Converter (ADC) are returned via the serial USB connection.
 
 The LDRs are connected to pins 5 and 6 corresponding to ports P1.3 and P1.4.
 
 Note when uploading if you have previously used the serial monitor then you might need
 to disconnect and then reconnect the USB cable just to release the port.
 
 Benn Thomsen, October 2015
 */
 
#define RIGHTSENSOR P1_3
#define LEFTSENSOR P1_4

int RightSensor, LeftSensor;   // variables to hold sensor readings

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600); 
}

void loop() {
  // read the analogue in value:
  RightSensor = analogRead(RIGHTSENSOR); 
  LeftSensor = analogRead(LEFTSENSOR);
          

  // print the results to the serial monitor:
  Serial.print("Right = " );                       
  Serial.print(RightSensor); 
  Serial.print(", Left = " );                       
  Serial.println(LeftSensor);  
  
  // wait 500 milliseconds before the next loop
  delay(100);                     
}
