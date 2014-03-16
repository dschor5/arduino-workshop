

// BISCUIT.ino - manually actuated by serial connection
// based on "Sweep" by BARRAGAN <http://barraganstudio.com> 
// Modified by Troy Denton for educational / workshop purposes
// This example code is in the public domain.


#include <Servo.h> 

//pin for servomotor
const int PIN_BELT_SERVO = 3;
const int PIN_LIFTER_SERVO=11;

//pins for motor controller, dough extrusion motor
const int PIN_MC0 = 12;
const int PIN_MC1 = 13;
 
Servo driveServo;  // create servo object to control a servo 
                
Servo extruderServo;

//There is no concept of position in a "continuous rotation" servo - only Forward, Backward, and Stop
const int FORWARD = 20;
const int BACKWARD = 160;
const int STOP = 92;

//positions for extruder lifter assembly
const int UP = 65;
const int DOWN = 30;

int conveyorDirection = STOP;    // variable to store the servo position 

int extruderPosition=STOP;  //variable to store extruder command

int lifterPosition=UP;
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
     conveyorDirection=FORWARD;
   break;
   case '2':
     conveyorDirection=BACKWARD;
   break;
   case '3':
     conveyorDirection=STOP;
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
     lifterPosition=UP;
   break;
   case 'd':
     lifterPosition=DOWN;
   break;
  }
 }

}
void setup() 
{ 
  pinMode(PIN_MC0,OUTPUT);
  pinMode(PIN_MC1,OUTPUT);
  driveServo.attach(PIN_BELT_SERVO);  // attaches the servo on pin 9 to the servo object 
  extruderServo.attach(PIN_LIFTER_SERVO);
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
     Serial.println("Backward!");
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
  driveServo.write(conveyorDirection);
  extruderServo.write(lifterPosition);
  extruderControl();
} 
