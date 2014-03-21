// Lab 6 - continuous rotation servo
// Modified by Troy Denton for educational / workshop purposes
// based on "Sweep" by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.


#include <Servo.h> 
 
Servo driveServo;  // create servo object to control a servo 
                

//There is no concept of position in a "continuous rotation" servo - only Forward, Backward, and Stop
const int FORWARD = 20;
const int BACKWARD = 160;
const int STOP = 92;
int servoPosition = STOP;    // variable to store the servo position 

//our sensor pin
const int PIN_SENSOR = 2;
/*

serialEvent is a function that gets called after every iteration of loop(), but only when there is Serial 
Data available.

*/
void serialEvent()
{
 while(Serial.available())
 {
  char inChar = Serial.read(); 
  switch(inChar)
  {
   case '1':
     servoPosition=FORWARD;
   break;
   case '2':
     servoPosition=BACKWARD;
   break;
   case '3':
     servoPosition=STOP;
   break;
  }
 }

}
void setup() 
{ 
  pinMode(PIN_SENSOR,INPUT);
  driveServo.attach(9);  // attaches the servo on pin 9 to the servo object 
  Serial.begin(9600);
  Serial.println("Starting...");
  
} 
 
 
void loop() 
{ 
  driveServo.write(servoPosition);
} 
