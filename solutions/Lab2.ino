/***
 * Red River College - Arduino Workshop
 * 
 * TITLE:        Example #1
 * DESCRIPTION:  Blink an LED.
 * AUTHOR:       Dario Schor (schor@ieee.org)
 * DATE:         March 15, 2014
 **/ 

#define PIN 13

char message[] = "cookies";
char morse[26][5] = {
  ".-  ",  // A
  "-...",  // B
  "-.-.",  // C
  "-.. ",  // D
  ".   ",  // E
  "..-.",  // F
  "--. ",  // G
  "....",  // H
  "..  ",  // I
  ".---",  // J
  "-.- ",  // K
  ".-..",  // L
  "--  ",  // M
  "-.  ",  // N
  "--- ",  // O
  ".--.",  // P
  "--.-",  // Q
  ".-. ",  // R
  "... ",  // S
  "-   ",  // T
  "..- ",  // U
  "...-",  // V
  ".--",   // W
  "-..-",  // X
  "-.--",  // Y
  "--.."   // Z
  };
  
int currLetter = 0;
const int maxSymbols = 4;

/***
 * setup()
 * Description:  Initialize LED pin output.
 **/
void setup() 
{                
  // Use built-in pin 13 as the LED output.
  pinMode(PIN, OUTPUT);  
  currLetter = 0;  
  
  // Set serial port for testing output
  Serial.begin(9600);
}

/***
 * loop()
 * Description:  Turn LED on/off every 1 second.
 **/
void loop() 
{
  Serial.println(message[currLetter]);
  sendLetter(message[currLetter]);
  currLetter = (currLetter + 1) % strlen(message); 
}

/***
 * sendLetter()
 * Description: Send a letter in morse code.
 **/
void sendLetter(char letter)
{
  int i = 0;
  while(morse[letter-'a'][i] != ' ' && i < maxSymbols)
  {
     if(morse[letter-'a'][i] == '.')
     {
       dot();
     }
     else if(morse[letter-'a'][i] == '-')
     {
       dash();
     } 
     i++;
  }
  delay(300);
}

/***
 * dot()
 * Description: Sends a morse code dot to PIN.
 **/
void dot(void)
{
    // Fill in the code for the dot
    // ON for 200ms
    // OFF for 200ms
    digitalWrite(PIN, HIGH);
    delay(200);
    digitalWrite(PIN, LOW);
    delay(200);
}

/***
 * dash()
 * Description: Sends a morse code dash to PIN.
 **/
void dash(void)
{
    // Fill in the code for the dash
    // ON for 500ms
    // OFF for 200ms
    digitalWrite(PIN, HIGH);
    delay(500);
    digitalWrite(PIN, LOW);
    delay(200);
}
