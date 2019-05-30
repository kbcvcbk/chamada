#include <LCD.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <LiquidCrystal_SI2C.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
// variável que controla se o código de aluno já foi escrito
bool initi = false;

// variáveis que controlam o código final que vai ser escrito na
// serial p/ indicar qual o aluno e qual sua escolha
int codeSize = 4;
String code;
String choice;

// pinos, a-d são os butões de escolha, con é o botão de
// confirmação e led é o led (duuuh)
int a = 2;
int b = 3;
int c = 4;
int d = 5;
int con = 6;
int led = 9;

#include <LiquidCrystal.h>
LiquidCrystal_I2C lcd(0x3F,2,1,0,4,5,6,7,3, POSITIVE);

void codeWrite(String cd) {
  code = code + cd;
  digitalWrite(led, LOW);
  delay(200);
  digitalWrite(led, HIGH);
  lcd.clear();
  //Posiciona o cursor na coluna 3, linha 0;
  lcd.setCursor(5, 0);
  //Envia o texto entre aspas para o LCD
  lcd.print("Codigo");
  lcd.setCursor(6, 1);
  lcd.print(code);
  delay(500);
}

void choiceWrite(String cd) {
  choice = cd;
  digitalWrite(led, HIGH);
  delay(200);
  digitalWrite(led, LOW);
  lcd.clear();
  //Posiciona o cursor na coluna 3, linha 0;
  lcd.setCursor(2, 0);
  //Envia o texto entre aspas para o LCD
  lcd.print("ALTERNATIVA");
  lcd.setCursor(2, 1);
  lcd.print(choice +" " + "CONFIRMA?");
  delay(500);
}

void ledSuccess() {
  digitalWrite(led, HIGH);
  delay(100);
  digitalWrite(led, LOW);
  delay(100);
  digitalWrite(led, HIGH);
  delay(100);
  digitalWrite(led, LOW);
}

void ledFail() {
  digitalWrite(led, HIGH);
  delay(500);
  digitalWrite(led, LOW);
}

void setup() {
  Serial.begin(9600);
  pinMode(a, INPUT_PULLUP);
  pinMode(b, INPUT_PULLUP);
  pinMode(c, INPUT_PULLUP);
  pinMode(d, INPUT_PULLUP);
  pinMode(con, INPUT_PULLUP);
  pinMode(led, OUTPUT);
  lcd.begin(16,2);
  lcd.clear();
  //Posiciona o cursor na coluna 3, linha 0;
  lcd.setCursor(7, 0);
  //Envia o texto entre aspas para o LCD
  lcd.print("A");
  lcd.setCursor(8, 1);
  lcd.print("Q!");
  delay(0);

}

void loop() {
  if (!initi) {
    // se o controle ainda não foi inicializado
    // limpe o código do aluno e acenda o led
    code = "";
    digitalWrite(led, HIGH);    
    int count = 0;
    // e rode o código abaixo até que
    // o código de aluno inteiro tenha
    // sido escrito.
    while (count < codeSize) {
      // se o botão estiver apertado (ou seja, for igual a LOW)
      // escreva o código e aumente o contador (que conta quanto
      // do código do aluno já foi escrito)
      if (digitalRead(a) == LOW) {
        codeWrite("A");
        count++;
      }
      if (digitalRead(b) == LOW) {
        codeWrite("B");
        count++;
      }
      if (digitalRead(c) == LOW) {
        codeWrite("C");
        count++;
      }
      if (digitalRead(d) == LOW) {
        codeWrite("D");
        count++;
      }
      
    }  
    initi = true; // o controle foi inicializado!
  }
  if (initi) {  // caso o controle já tenha sido inicializado
    // entre no modo de resposta à quiz
    digitalWrite(led, LOW);
    if (digitalRead(a) == LOW) {
      choiceWrite("A");
    }
    if (digitalRead(b) == LOW) {
      choiceWrite("B");
    }
    if (digitalRead(c) == LOW) {
      choiceWrite("C");
    }
    if (digitalRead(d) == LOW) {
      choiceWrite("D");
    }

    if (!digitalRead(con)) {
      if (choice == "") {
        // se nenhuma opção estiver selecionada,
        // envia mensagem de erro pelo led
        ledFail();
      }
                  
      else {
        // caso contrário, envia o código pela seria
        // e envia mensagem de sucesso pelo led
        Serial.println(code + " " + choice);
        lcd.clear();
        //Posiciona o cursor na coluna 3, linha 0;
        lcd.setCursor(4, 0);
        //Envia o texto entre aspas para o LCD
        lcd.print("RESPOSTA");
        lcd.setCursor(7, 1);
        lcd.print(choice);
        delay(500);
        
      }
    }
  }
}
