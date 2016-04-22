#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27,16,2); // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup()
{
lcd.init(); // initialize the lcd 
lcd.backlight(); //Open the backlight
lcd.print("Welcome to "); // Print a message to the LCD.
lcd.setCursor(0,1); //newline
lcd.print("www.yfrobot.com");// Print a message to the LCD
}
void loop()
{
}

