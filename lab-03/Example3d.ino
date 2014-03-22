/***
 * Red River College - Arduino Workshop
 * 
 * TITLE:        Example #3
 * DESCRIPTION:  Custom characters for pacman.
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

char temp;
int  x;

 
/***
 * setup()
 * Description:  Init display and serial port
 **/
void setup(void) 
{
  // Initialize the LCD
  lcd.begin(16, 2);

  // Setup serial port
  Serial.begin(9600);
  
  // Init variables
  temp = ' ';
  x = 0;
}
 
 
/***
 * loop()
 * Description:  Write user input to the LCD.
 **/
void loop(void) 
{
  if(Serial.available() > 0)
  {
    // Read a byte
    temp = Serial.read();
    
    // Update position on screen
    lcd.setCursor(x, 0);
    
    // Write byte
    lcd.write(temp);
    
    // Set next position
    // This will override what you currently have
    // once you write more than 16 characters
    x = (x + 1) % NUM_COLS;
  }
}
 

