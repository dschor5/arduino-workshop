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

void setup() 
{ 
  pinMode(PIN_SENSOR,INPUT);
  driveServo.attach(PIN_BELT_SERVO);  // attaches the servo on pin 9 to the servo object 
  
} 
 
 
void loop() 
{ 
  adc_key_in = analogRead(0);      // read the value from the sensor 
  key = get_key(adc_key_in);       // convert into key press
  if (key==KEY_RIGHT)
    driveServo.write(BACKWARD);
  else if (key== KEY_LEFT)
    driveServo.write(FORWARD);
  else
    driveServo.write(STOP);

  delay(100);	//check 10 times a second
  
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
