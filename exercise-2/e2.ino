/***
 * Millennium Library - Arduino Workshop
 * 
 * TITLE:        Example #2
 * DESCRIPTION:  Read a switch, blink an LED
 * AUTHOR:       Dario Schor (schor@ieee.org), Troy Denton (trdenton@gmail.com)
 * DATE:         March 22, 2014
 **/ 

int switchPin = 7;
int LEDPin = 13;
void setup() {
  // put your setup code here, to run once:
  pinMode(switchPin,INPUT);
  pinMode(LEDPin,OUTPUT);
  digitalWrite(LEDPin,LOW);
}

void loop() {
  // put your main code here, to run repeatedly:
  int switch_value = digitalRead(switchPin);
  if(switch_value==LOW)
  {
   digitalWrite(LEDPin,HIGH);
   delay(1000);
   digitalWrite(LEDPin,LOW);
   delay(1000);
  }
  delay(100);
}
