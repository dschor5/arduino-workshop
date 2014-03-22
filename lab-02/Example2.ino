/***
 * Red River College - Arduino Workshop
 * 
 * TITLE:        Example #1
 * DESCRIPTION:  Blink an LED.
 * AUTHOR:       Dario Schor (schor@ieee.org)
 * DATE:         March 15, 2014
 **/ 


/***
 * setup()
 * Description:  Initialize LED pin output.
 **/
void setup() {                
  // Use built-in pin 13 as the LED output.
  pinMode(13, OUTPUT);     
}

/***
 * loop()
 * Description:  Turn LED on/off every 1 second.
 **/
void loop() {
  // Turn LED on 
  digitalWrite(13, HIGH);
  // Wait 1 second
  delay(1000);
  // Turn LED off
  digitalWrite(13, LOW);
  // Wait 1 second
  delay(1000);
}
