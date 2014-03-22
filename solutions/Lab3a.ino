/***
 * Red River College - Arduino Workshop
 * 
 * TITLE:        Lab #3
 * DESCRIPTION:  Scrolling text
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


/***
 * setup()
 * Description:  Initialize the LCD.
 **/
void setup()
{
  // Set the dimensions of the LCD screen.
  lcd.begin(NUM_COLS, NUM_ROWS);
  
  // Clear the LCD screen
  lcd.clear(); 
  
  // Set the message on the screen
  lcd.setCursor(0, 0);
  lcd.print("IEEE Workshop.");
  lcd.setCursor(0, 1);
  lcd.print("I want cookies!");
}

/***
 * loop()
 * Description:  Scroll message
 **/
void loop()
{
  // Scroll text left
  for (int i = 0; i < NUM_COLS; i++) {
    // scroll one position left:
    lcd.scrollDisplayLeft(); 
    // wait a bit:
    delay(500);
  }

  // Scroll text right (past the end of the screen)
  for (int i = 0; i < NUM_COLS * 2; i++) {
    // scroll one position right:
    lcd.scrollDisplayRight(); 
    // wait a bit:
    delay(500);
  }
  
    // Scroll text back to initial position
  for (int i = 0; i < NUM_COLS; i++) {
    // scroll one position left:
    lcd.scrollDisplayLeft(); 
    // wait a bit:
    delay(500);
  }
  
  // delay at the end of the full loop:
  delay(1000);
}

