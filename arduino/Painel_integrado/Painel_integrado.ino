#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE);
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

void setup() {
  lcd.begin(16,2);
  lcd.setBacklight(LOW);
  lcd.clear();
  lcd.setCursor(7, 0);
  lcd.print("A");
  lcd.setCursor(8, 1);
  lcd.print("Q!");
}

void loop() {
  
}

