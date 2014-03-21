// BISCUIT.ino - manually actuated by serial connection
// based on "Sweep" by BARRAGAN <http://barraganstudio.com> 
// Modified by Troy Denton for educational / workshop purposes
// This example code is in the public domain.


#include <Servo.h> 

//pin for servomotor
const int PIN_SERVO = 9;
const int PIN_HEIGHT_SERVO=8;

//pins for motor controller
const int PIN_MC0 = 4;
const int PIN_MC1 = 5;
 
Servo driveServo;  // create servo object to control a servo 
                
Servo extruderServo;

//There is no concept of position in a "continuous rotation" servo - only Forward, Backward, and Stop
const int FORWARD = 20;
const int BACKWARD = 160;
const int STOP = 92;

//positions for extruder assembly
const int UP = 65;
const int DOWN = 30;

int servoPosition = STOP;    // variable to store the servo position 

int extruderPosition=STOP;  //variable to store extruder command

int extruderHeight=UP;
/*

serialEvent is a function that gets called after every iteration of loop(), but only when there is Serial 
Data available.

*/
void serialEvent()
{
 while(Serial.available())
 {
  char dummy = Serial.read(); 
  switch(dummy)
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
   case 'a':
     extruderPosition=FORWARD;
   break;
   case 'b':
     extruderPosition=BACKWARD;
   break;
   case 'c':
     extruderPosition=STOP;
   break;
   case 'u':
     extruderHeight=UP;
   break;
   case 'd':
     extruderHeight=DOWN;
   break;
  }
 }

}
void setup() 
{ 
  pinMode(PIN_MC0,OUTPUT);
  pinMode(PIN_MC1,OUTPUT);
  driveServo.attach(PIN_SERVO);  // attaches the servo on pin 9 to the servo object 
  extruderServo.attach(PIN_HEIGHT_SERVO);
  Serial.begin(9600);
  Serial.println("Starting...");
} 
 
void extruderControl()
{
 switch(extruderPosition)
 {
   case FORWARD:
     digitalWrite(PIN_MC0,LOW);
     digitalWrite(PIN_MC1,HIGH);
     Serial.println("Forward!");
   break;
   case BACKWARD:
     digitalWrite(PIN_MC0,HIGH);
     digitalWrite(PIN_MC1,LOW);
     Serial.println("BAckward!");
   break;
   case STOP:
   default:
     digitalWrite(PIN_MC0,LOW);
     digitalWrite(PIN_MC1,LOW);
     Serial.println("Stop!");
   break;
 
 } 
  
}
 
void loop() 
{ 
  driveServo.write(servoPosition);
  extruderServo.write(extruderHeight);
  extruderControl();
} 
