/***
 * Millennium Library - Arduino Workshop
 * 
 * TITLE:        Example #3
 * DESCRIPTION:  Read an analog voltage.
 * AUTHOR:       Dario Schor (schor@ieee.org), Troy Denton (trdenton@gmail.com)
 * DATE:         March 22, 2014
 **/ 


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {

    // put your main code here, to run repeatedly:
    int reading = analogRead(A0);
    float voltage = reading*(5.0/1024.0);

    Serial.println(voltage);
  
    delay(500);
  
  
}
