/***
 * Red River College - Arduino Workshop
 * 
 * TITLE:        Example #3
 * DESCRIPTION:  Printing Text
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

// Variable to alternate messages
boolean msgFlag;


/***
 * setup()
 * Description:  Initialize the LCD.
 **/
void setup()
{
  // Initialize flag for printing messages
  msgFlag = false;
  
  // Clear the LCD screen
  lcd.clear(); 
  
  // Set the dimensions of the LCD screen.
  lcd.begin(NUM_COLS, NUM_ROWS);
}

/***
 * loop()
 * Description:  Print a message to the screen.
 **/
void loop()
{
  // Clear the LCD screen
  lcd.clear();
  
  // Set position to col=0, row=0
  lcd.setCursor(0, 0);
  
  // Print message to the first line
  lcd.print("IEEE Workshop.");
  
  // Set position to col=0, row=1
  lcd.setCursor(0, 1);
  
  // Print different messages on each iteration of the loop
  if(false == msgFlag)
  {
    lcd.print("Troy!");
  }
  else
  {
    lcd.print("I want cookies!");
  }
  
  // Switch between messages
  msgFlag = !msgFlag;
  
  // Delay between messages
  delay(750);
}

