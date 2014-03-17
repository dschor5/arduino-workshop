#include <Servo.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 13, 9, 4, 5, 6, 7);

//variables used for keypresses
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
int oldkey = KEY_NONE;


//Servo Control variables
int stepSize = 1;
int servoPosition = 90;

Servo myServo;

void setup()
{
  lcd.clear(); 
  lcd.begin(16, 2);
  myServo.attach(3);
  printStatus();
}

void printStatus()
{
  lcd.clear();
  lcd.print("Step size: ");//size is 11 characters
  lcd.setCursor(11,0);  //move to 11th position and print the step size
  lcd.print(stepSize);  
  lcd.setCursor(0,1);
  lcd.print("Position:  ");//size is 11 characters
  lcd.setCursor(11,1);  //move to 11th position and print the position
  lcd.print(servoPosition);

}


void loop()
{
  adc_key_in = analogRead(0);      // read the value from the sensor 
  key = get_key(adc_key_in);       // convert into key press
 
  if (key != oldkey) //only do something on a new keypress
  { 
    switch(key)
    {
      case KEY_UP:
        stepSize++;
        if (stepSize > 45)
          stepSize=45;
      break;
      case KEY_DOWN:
        stepSize--;
        if (stepSize < 0)
          stepSize=0;
      break;
      case KEY_RIGHT:
        servoPosition += stepSize;
        if (servoPosition > 179)
          servoPosition=179;
      break;
      case KEY_LEFT:
        servoPosition -= stepSize;
        if (servoPosition < 0)
          servoPosition=0;
      break;

    } 
    printStatus();
  }

  oldkey = key;
  myServo.write(servoPosition);
  delay(100);
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
