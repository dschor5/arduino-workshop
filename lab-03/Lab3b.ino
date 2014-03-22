/***
 * Red River College - Arduino Workshop
 * 
 * TITLE:        Lab #3b
 * DESCRIPTION:  Moving pacman with the buttons.
 * AUTHOR:       Dario Schor (schor@ieee.org)
 * DATE:         March 15, 2014
 *
 * This example uses the LiquidCrystal librady from:
 * http://arduino.cc/en/Reference/LiquidCrystal
 *
 * The display has 2 rows of 16 characters:
 * 
 *     0   1   2   3   4   5   6   7   8   9   10  11  12  13  14  15   < COLS
 *   -----------------------------------------------------------------
 *   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |  < ROW-0
 *   -----------------------------------------------------------------
 *   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |  < ROW-1
 *   -----------------------------------------------------------------
 **/ 

#include <LiquidCrystal.h>

// Size of screen
#define NUM_ROWS        2
#define NUM_COLS        16

// Custom pinout for the shield used in the workshop
#define LCD_RS_PIN      8
#define LCD_RW_PIN      13
#define LCD_EN_PIN      9
#define LCD_D4_PIN      4
#define LCD_D5_PIN      5
#define LCD_D6_PIN      6
#define LCD_D7_PIN      7

// Analog 0 reads the input from the buttons
#define READ_BUTTON     0
#define NUM_KEYS        5
#define INVALID_KEY     -1

// Each button has a different resistance value
#define KEY_RIGHT_ADC   50
#define KEY_UP_ADC      200
#define KEY_DOWN_ADC    400
#define KEY_LEFT_ADC    600
#define KEY_SELECT_ADC  800

#define KEY_RIGHT       0
#define KEY_UP          1
#define KEY_DOWN        2
#define KEY_LEFT        3


// Create instance of LiquidCrystal object
LiquidCrystal lcd(
  LCD_RS_PIN,   // Register Select
  LCD_RW_PIN,   // H-Read, L-Write
  LCD_EN_PIN,   // Enable (data strobe, active high)
  LCD_D4_PIN,   // Data pins
  LCD_D5_PIN, 
  LCD_D6_PIN, 
  LCD_D7_PIN
  );

// Analog value corresponding to each key pressed
int keyMapping[NUM_KEYS] = {
  KEY_RIGHT_ADC, 
  KEY_UP_ADC, 
  KEY_DOWN_ADC, 
  KEY_LEFT_ADC, 
  KEY_SELECT_ADC 
  };
  
int key = INVALID_KEY;

/***
 * setup()
 * Description:  Initialize the LCD.
 **/
void setup()
{
  // Clear the LCD screen
  lcd.clear(); 
  
  // Set the dimensions of the LCD screen.
  lcd.begin(NUM_COLS, NUM_ROWS);
  
  // Initialize pacman
}

/***
 * loop()
 * Description:  Read a key and print a msg to the LCD.
 **/
void loop()
{
  // Read key
  key = readKey();

  
  // If a key is pressed, print the message
  if(INVALID_KEY != key)
  {
    // Move pacman on the screen

  }
  
  // Delay before printing next message
  delay(100);
}

/***
 * readKey()
 * Description:  Find which key was pressed.
 **/
int readKey(void)
{
  int key = analogRead(READ_BUTTON);
  int index;
  
  // Find which key was pressed
  for(index = 0; index < NUM_KEYS; index++)
  {
    if(key < keyMapping[index])
    {
       return index; 
    }
  }
   
  // No key found
  return INVALID_KEY;  
}
	
