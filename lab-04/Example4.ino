/***
 * Red River College - Arduino Workshop
 * 
 * TITLE:        Example #4
 * DESCRIPTION:  Reading a sensor.
 * AUTHOR:       Dario Schor (schor@ieee.org)
 * DATE:         March 15, 2014
 **/ 
 
/***
 * setup()
 * Description:  Initialize serial monitor.
 **/
void setup() {
  // Initialize monitor with 9600 baud rate.
  Serial.begin(9600);
  pinMode(13, OUTPUT);  
  digitalWrite(13, HIGH);
}

/***
 * loop()
 * Description:  Read an analog value and print it to the monitor.
 **/
void loop() {
  // Read sensor analog value from port A0
  int sensorValue = analogRead(A0);
  // Print value to the serial monitor
  Serial.println(sensorValue);
}
