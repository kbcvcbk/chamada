#ifdef TYPE_LCD
#include <LCD.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal_SI2C.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE);
String vetor [10];
#endif
void init_lcd() {
#ifdef TYPE_LCD
  lcd.begin (16,2);
  lcd.clear();
  lcd.setCursor(7, 0);
  lcd.print("A");
  lcd.setCursor(8, 1);
  lcd.print("Q!");
#endif
}

