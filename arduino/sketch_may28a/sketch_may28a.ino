/* AQ! Controle Aluno
Arduino code by kalil & felinto*/

#define TYPE TYPE_LCD

// code
#define code "AACD"

// estados
#define INAT 0
#define CHAM 1
#define POST 2

// botões
#define BOT_A 2
#define BOT_B 3
#define BOT_C 4
#define BOT_D 5
#define BOT_CON 6

// debug
#define debug false

char estado = INAT;

String choice = " ";
String serial = " ";
bool right = false;
long post_end;
int right_awnser_idx = 4;

#define POST_TIME 4000

// global
void trocar_estado() {
  int available_bytes = Serial.available();
  if (available_bytes > 0) {
    if (estado == INAT) {
      serial = Serial.readString();
      serial.trim();
      if (debug) Serial.println(serial);
      if (serial == "start") estado = CHAM;
    } else if (estado == CHAM) {
      serial = Serial.readString();
      serial.trim();
      if (debug) Serial.println(serial);
      Serial.println(serial.substring(0, 3));
      post_end = millis() + POST_TIME;
      estado = POST;
    }
  } else if (estado == POST) {
    if (millis() > post_end) estado = INAT;
  }
}

// estado = cham
void get_choice() {
  if (digitalRead(BOT_A) == LOW) {
    choice = 'A';
  } else if (digitalRead(BOT_B) == LOW) {
    choice = 'B';
  } else if (digitalRead(BOT_C) == LOW) {
    choice = 'C';
  } else if (digitalRead(BOT_D) == LOW) {
    choice = 'D';
  }
  if (debug and estado == CHAM) {
    Serial.print("Choice = ");
    Serial.println(choice);
  }
}

void write_choice() {
  if (digitalRead(BOT_CON) == LOW) {
    String output = code + choice;
    Serial.println(output);
  }
}

// estado = post
void set_right() {
  if (serial[right_awnser_idx] == choice[0]) {
    right = true;
  } else {
    right = false;
  }
}

void right_ans() {
  Serial.println("Reposta certa!");
}

void wrong_ans() {
  Serial.println("Resposta errada!");
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(BOT_A, INPUT_PULLUP);
  pinMode(BOT_B, INPUT_PULLUP);
  pinMode(BOT_C, INPUT_PULLUP);
  pinMode(BOT_D, INPUT_PULLUP);
  pinMode(BOT_CON, INPUT_PULLUP);
  #if (TYPE == TYPE_LCD)
  _initlcd();
  #endif
}

void loop() {
  if (estado == INAT) {
    trocar_estado();
    #if (TYPE == TYPE_LCD)
    #endif
    if (debug) Serial.println("INAT");
  } else if (estado == CHAM) {
    if (debug) Serial.println("CHAM");
    get_choice();
    write_choice();
    trocar_estado();
  } else {
    if (debug) Serial.println("POST");
    set_right();    // figures out if choice is right
    if (right) {
      right_ans();  // outputs right answer
    } else {
      wrong_ans();  // outputs wrong answer
    }
    trocar_estado();
  }
}
