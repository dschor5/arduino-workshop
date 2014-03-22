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
  lcd.print("Press Select...");
  
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
  if (key==KEY_UP)
  {
    pullExtruder();
    while (key == KEY_UP)
    {
      adc_key_in = analogRead(0);      // read the value from the sensor 
      key = get_key(adc_key_in); 
    }
    stopExtruder();
  }
  else if (key == KEY_DOWN)
  {
    pushExtruder();
    while (key == KEY_DOWN)
    {
      adc_key_in = analogRead(0);      // read the value from the sensor 
      key = get_key(adc_key_in); 
    }
    stopExtruder();
  }
  
    
  
  switch(currentState)
  {
   case STATE_WAIT_INPUT:
     adc_key_in = analogRead(0);      // read the value from the sensor 
     key = get_key(adc_key_in);       // convert into key press
     if (key==KEY_SELECT)
     {
       currentState=STATE_MOVE_EXTRUDER;
       lcd.clear();
       lcd.print("Now Moving...");
     }
   break;
   case STATE_MOVE_EXTRUDER:
     beltPosition=BELT_FORWARD;
     if (digitalRead(PIN_TRAY_SENSOR)==LOW)
     { 
       currentState=STATE_PRINT_COOKIES;
       beltPosition=BELT_STOP;
       lcd.clear();
       lcd.print("Now Printing...");
     }
    
   break; 
   case STATE_PRINT_COOKIES:
     //scooch the belt forward a bit...
     
     //print 2 cookies
     for(int i = 0; i < 2; i++)
     {
       lifterServo.write(LIFTER_DOWN);
       delay(TIME_BETWEEN_LIFTER_AND_EXTRUDER_MS);
       pushExtruder();
       delay(TIME_EXTRUDE_COOKIE_MS);
       stopExtruder();  
       lifterServo.write(LIFTER_UP);
       delay(TIME_LIFTER_SETTLE_MS);
       beltServo.write(BELT_FORWARD);
       delay(TIME_BELT_BETWEEN_COOKIES_MS);
       beltServo.write(BELT_STOP);
     }
     
     while (digitalRead(PIN_TRAY_SENSOR)!=HIGH)
     {
       beltServo.write(BELT_FORWARD);
     }  
     currentState=STATE_FINISH;
     
   break;
   case STATE_FINISH:
     beltPosition=BELT_STOP; 
     lcd.clear();
     lcd.print("Done!");
     delay(1000);
     currentState=STATE_WAIT_INPUT;
     lcd.clear();
     lcd.print("Press Select...");

   break;
      
  }
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
