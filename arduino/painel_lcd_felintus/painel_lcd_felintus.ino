#include <LCD.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal_SI2C.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Inicializa o display no endereco 0x27
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE);
//LiquidCrystal_I2C lcd(0x38,16,2);
String vetor [10];

void setup()
{
lcd.begin (16,2);
//lcd.init();
}

void loop()
{
 lcd.setCursor(3,0);
 lcd.print("COMI O CU");
 lcd.setCursor(0,1);
 lcd.print("DE QUEM TA LENDO");
}
