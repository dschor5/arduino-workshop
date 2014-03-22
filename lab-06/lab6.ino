// Lab 6 - continuous rotation servo
// Modified by Troy Denton for educational / workshop purposes
// based on "Sweep" by BARRAGAN <http://barraganstudio.com> 
// This example code is in the public domain.


#include <Servo.h> 
 
Servo driveServo;  // create servo object to control a servo 
                

//There is no concept of position in a "continuous rotation" servo - only Forward, Backward, and Stop
const int PIN_SERVO = 11;
const int FORWARD = 20;
const int BACKWARD = 160;
const int STOP = 92;
int servoPosition = STOP;    // variable to store the servo position 

const int KEY_SELECT = 4;
const int KEY_LEFT = 3;
const int KEY_DOWN = 2;
const int KEY_UP = 1;
const int KEY_RIGHT = 0;
const int KEY_NONE = -1; 
const int NUM_KEYS = 5;

int adc_key_val[NUM_KEYS] = {50, 200, 400, 600, 800 };
int adc_key_in;
int key = KEY_NONE;

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
  //TODO 6.1: use serial input to control servo
 }

}
void setup() 
{ 
  pinMode(PIN_SENSOR,INPUT);
  driveServo.attach(PIN_SERVO);  // attaches the servo on pin 9 to the servo object 
  Serial.begin(9600);
  Serial.println("Starting...");
  
} 
 
 
void loop() 
{ 
  //TODO 6.2: use LCD keys to control servo
  //TODO 6.3: make servo stop when optical sensor is covered, use digitalRead(PIN_SENSOR)
  driveServo.write(servoPosition);
} 

// Convert ADC value to key number
int get_key(unsigned int input)
{
    int k;
   
    for (k = 0; k < NUM_KEYS; k++) {
      if (input < adc_key_val[k])
        return k;
    }
   
    if (k >= NUM_KEYS)             // No valid key pressed
      k = -1;

    return k;
}
