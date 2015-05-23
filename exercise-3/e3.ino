/***
 * Millennium Library - Arduino Workshop
 * 
 * TITLE:        Example #3
 * DESCRIPTION:  Print to the serial console
 * AUTHOR:       Dario Schor (schor@ieee.org), Troy Denton (trdenton@gmail.com)
 * DATE:         March 22, 2014
 **/ 


int switchPin = 7;
int LEDPin = 13;

int numPushes=0;
void setup() {
  // put your setup code here, to run once:
  pinMode(switchPin,INPUT);
  pinMode(LEDPin,OUTPUT);
  digitalWrite(LEDPin,LOW);
  
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int switch_value = digitalRead(switchPin);
  if(switch_value==LOW)
  {
   numPushes = numPushes + 1;
   Serial.print("BUTTON PUSHED ");
   Serial.print(numPushes);
   Serial.println(" TIMES!");
   delay(250);
  }

}
