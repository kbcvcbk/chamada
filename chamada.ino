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

void setup() {
  Serial.begin(9600);
  pinMode(a, INPUT_PULLUP);
  pinMode(b, INPUT_PULLUP);
  pinMode(c, INPUT_PULLUP);
  pinMode(d, INPUT_PULLUP);
  pinMode(con, INPUT_PULLUP);
  pinMode(led, OUTPUT);
}

void loop() {
  if (!initi) { // se o controle ainda não foi inicializado
    code = "";  // limpe o código do aluno
    digitalWrite(led, HIGH);  // acenda o led
    int count = 0;
    while (count < codeSize) {  // e rode o código abaixo até que
                                // o código de aluno inteiro tenha
                                // sido escrito.
      if (!digitalRead(a)) {
        digitalWrite(led, LOW);
        delay(200);
        digitalWrite(led, HIGH);
        code = code + "00";
        count++;
      }
      if (!digitalRead(b)) {
        digitalWrite(led, LOW);
        delay(200);
        digitalWrite(led, HIGH);
        code = code + "01";
        count++;
      }
      if (!digitalRead(c)) {
        digitalWrite(led, LOW);
        delay(200);
        digitalWrite(led, HIGH);
        code = code + "10";
        count++;
      }
      if (!digitalRead(d)) {
        digitalWrite(led, LOW);
        delay(200);
        digitalWrite(led, HIGH);
        code = code + "11";
        count++;
      }
    }
    initi = true;
  }
  if (initi) {  // caso o controle já tenha sido atualizado
                // entre no modo de resposta à quiz
    digitalWrite(led, LOW);
    if (!digitalRead(a)) {
      digitalWrite(led, HIGH);
      choice = "00";
      delay(200);
      digitalWrite(led, LOW);
    }
    if (!digitalRead(b)) {
      digitalWrite(led, HIGH);
      choice = "01";
      delay(200);
      digitalWrite(led, LOW);
    }
    if (!digitalRead(c)) {
      digitalWrite(led, HIGH);
      choice = "10";
      delay(200);
      digitalWrite(led, LOW);
    }
    if (!digitalRead(d)) {
      digitalWrite(led, HIGH);
      choice = "11";
      delay(200);
      digitalWrite(led, LOW);
    }

    if (!digitalRead(con)) {
      if (choice == "") {
        digitalWrite(led, HIGH);
        delay(500);
        digitalWrite(led, LOW);
      } else {
        digitalWrite(led, HIGH);
        Serial.println(code + choice);
        delay(100);
        digitalWrite(led, LOW);
        delay(100);
        digitalWrite(led, HIGH);
        delay(100);
        digitalWrite(led, LOW);
      }
    }
  }
}
