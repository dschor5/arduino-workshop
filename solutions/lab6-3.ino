// Lab 6 - continuous rotation servo
// Modified by Troy Denton for educational / workshop purposes
// based on "Sweep" by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.


#include <Servo.h> 
 
Servo driveServo;  // create servo object to control a servo 
                

//There is no concept of position in a "continuous rotation" servo - only Forward, Backward, and Stop
const int PIN_BELT_SERVO = 11;
const int FORWARD = 20;
const int BACKWARD = 160;
const int STOP = 92;
int servoPosition = STOP;    // variable to store the servo position 

//our sensor pin
const int PIN_SENSOR = 2;

void setup() 
{ 
  pinMode(PIN_SENSOR,INPUT);
  driveServo.attach(PIN_BELT_SERVO);  // attaches the servo on pin 9 to the servo object 
  
} 
 
 
void loop() 
{ 
  while(digitalRead(PIN_SENSOR)==HIGH)
  {
    driveServo.write(FORWARD);
  }
  driveServo.write(STOP);
  
} 
