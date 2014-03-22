#include <Servo.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 13, 9, 4, 5, 6, 7);


/*--- timing constants ---*/
const float BELT_CM_SEC = 8.33;   //8.33cm/sec

const int TIME_BETWEEN_LIFTER_AND_EXTRUDER_MS = 500;
const int TIME_EXTRUDE_COOKIE_MS = 8000;
const int TIME_LIFTER_SETTLE_MS =  1000;
const int TIME_BELT_BETWEEN_COOKIES_MS = 900;
/*--- timing constants ---*/

/*--- variables used for keypresses ---*/
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
/*--- variables used for keypresses ---*/



/*--- outputs for h bridge controller ---*/
const int PIN_MC0=12;
const int PIN_MC1=13;
/*--- outputs for h bridge controller ---*/

/*--- variables for optical sensor ---*/
const int PIN_TRAY_SENSOR = 2;
/*--- variables for optical sensor ---*/


/*-- Servo motor variables --*/
const int BELT_FORWARD = 20;
const int BELT_BACKWARD = 160;
const int BELT_STOP = 92;
int beltPosition;

const int LIFTER_UP=65;
const int LIFTER_DOWN=30;
int lifterPosition;

const int PIN_BELT_SERVO = 11;
const int PIN_LIFTER_SERVO = 3;
Servo beltServo;
Servo lifterServo;
/*-- Servo motor variables --*/

/*--- State machine variables ---*/
const int STATE_WAIT_INPUT = 0;
const int STATE_MOVE_EXTRUDER = 1;
const int STATE_PRINT_COOKIES = 2;
const int STATE_FINISH = 3;

int currentState;
/*--- State machine variables ---*/


/*--- extruder motor functions ---*/
void pushExtruder()
{
 digitalWrite(PIN_MC0,HIGH);
 digitalWrite(PIN_MC1,LOW);
}

void pullExtruder()
{
 digitalWrite(PIN_MC1,HIGH);
 digitalWrite(PIN_MC0,LOW);
}

void stopExtruder()
{
 digitalWrite(PIN_MC0,LOW);
 digitalWrite(PIN_MC1,LOW); 
}

/*--- extruder motor functions ---*/


void setup()
{
  currentState = STATE_WAIT_INPUT;

  pinMode(PIN_TRAY_SENSOR,INPUT);
  pinMode(PIN_MC0,OUTPUT);
  pinMode(PIN_MC1,OUTPUT);
  
  lcd.clear(); 
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Manual Mode...");
  
  beltServo.attach(PIN_BELT_SERVO);
  beltPosition = BELT_STOP;
  
  lifterServo.attach(PIN_LIFTER_SERVO);
  lifterPosition = LIFTER_UP;

  stopExtruder();
}

void loop()
{
  adc_key_in = analogRead(0);      // read the value from the sensor 
  key = get_key(adc_key_in); 

  //control conveyor belt

  if(key==KEY_LEFT)
    beltPosition = BELT_FORWARD;
  else if (key==KEY_RIGHT)
    beltPosition = BELT_BACKWARD;
  else
    beltPosition = BELT_STOP;

  //control lifter

  if(key==KEY_UP)
    lifterPosition=LIFTER_UP;
  else if (key == KEY_DOWN)
    lifterPosition=LIFTER_DOWN;
   
  //control Extruder 
  if (key==KEY_SELECT)
    pushExtruder();
  else
    stopExtruder();
  
  
  beltServo.write(beltPosition);
  lifterServo.write(lifterPosition);
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
