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

// Constants for pacman
#define PACMAN_CLOSE    0x0
#define PACMAN_OPEN     0x1
#define PACMAN_FOOD     0x2
#define PACMAN_DELAY    500

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

// Pacman with the mouth closed
byte pacmanCloseDef[8] = {
  0b00000,
  0b01110,
  0b11011,
  0b11111,
  0b11111,
  0b01110,
  0b00000,
  0b00000
};

// Pacman with the mouth opened
byte pacmanOpenDef[8] = {
  0b00000,
  0b01110,
  0b10100,
  0b11000,
  0b11100,
  0b01110,
  0b00000,
  0b00000
};

// Pacman food
byte dotDef[8] = {
  0b00000,
  0b00000,
  0b00000,
  0b01100,
  0b01100,
  0b00000,
  0b00000,
  0b00000
};
 
// Coordinates to keep track of pacman on the screen
int x = 0;
int px = 0;
 
 
/***
 * setup()
 * Description:  Init display and pacman characters.
 **/
void setup(void) 
{
  // Create custom characters for pacman
  lcd.createChar(PACMAN_CLOSE, pacmanCloseDef);
  lcd.createChar(PACMAN_OPEN,  pacmanOpenDef);
  lcd.createChar(PACMAN_FOOD,  dotDef);
  
  // Initialize the LCD
  lcd.begin(16, 2);

  // Fill the display with some food
  fill();
}
 
 
/***
 * loop()
 * Description:  Eat the food!
 **/
void loop(void) 
{
  // Animate pacman to eat the food
  anim();
  
  // Advance to next position
  x++;
  
  // If reached the end, then reset
  if(x > 15)
  {
    x = 0;
    fill();
  }
}
 
 
/***
 * fill()
 * Description:  Initialize the food on the screen.
 **/
void fill(void)
{
  // Set LCD position and alternate food, no-food characters
  lcd.setCursor(0,0);
  lcd.write((byte)PACMAN_CLOSE);
  for(int j=0;j<7;j++)
  {
    lcd.write(" ");
    lcd.write(PACMAN_FOOD);
  }
}
 
/***
 * anim()
 * Description:  Animate pacman eating one piece of food.
 **/
void anim(void)
{
  // Clear the prev position
  lcd.setCursor(px,0);
  lcd.write(" ");
  
  // Draw pacman with the mouth closed
  lcd.setCursor(x,0);
  lcd.write((byte)PACMAN_CLOSE);
  delay(PACMAN_DELAY);
  
  // Draw pacman with the mouth open
  lcd.setCursor(x,0);
  lcd.write((byte)PACMAN_OPEN);
  delay(PACMAN_DELAY);
  px = x;
}
