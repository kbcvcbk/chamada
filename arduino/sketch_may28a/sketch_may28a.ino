/* AQ! Controle Aluno
  Arduino code by kalil & felinto*/

#define TYPE_LED

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
bool choice_set = false;
String serial = " ";
bool right = false;
long post_end;
int right_awnser_idx = 4;

#define POST_TIME 4000

// global
void read_serial() {
  serial = Serial.readString();
  serial.trim();
  if (debug) Serial.println(serial);
}
void trocar_estado() {
  int available_bytes = Serial.available();
  if (available_bytes > 0 && estado == INAT) { // começa a chamada
    read_serial();
    if (serial == "start") estado = CHAM;
  } else if (estado == CHAM && available_bytes > 0) { //termina a chamada
    read_serial();
    post_end = millis() + POST_TIME;
    estado = POST;
  } else if (estado == POST) { // retorna à inat
    if (millis() > post_end) estado = INAT;
  }
}

// estado = cham
void get_choice() {
  if (digitalRead(BOT_A) == LOW) {
    choice = 'A';
    choice_set = true;
  } else if (digitalRead(BOT_B) == LOW) {
    choice = 'B';
    choice_set = true;
  } else if (digitalRead(BOT_C) == LOW) {
    choice = 'C';
    choice_set = true;
  } else if (digitalRead(BOT_D) == LOW) {
    choice = 'D';
    choice_set = true;
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

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(BOT_A, INPUT_PULLUP);
  pinMode(BOT_B, INPUT_PULLUP);
  pinMode(BOT_C, INPUT_PULLUP);
  pinMode(BOT_D, INPUT_PULLUP);
  pinMode(BOT_CON, INPUT_PULLUP);
#ifdef TYPE_LCD
  init_lcd();
#endif
}

void loop() {
  trocar_estado();
  update_led_state();
  if (estado == INAT) {
  } else if (estado == CHAM) {
    get_choice();
    write_choice();
  } else {
    set_right();
  }
}
