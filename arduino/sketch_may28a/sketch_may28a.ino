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

int estado = INAT;

String serial = String(" ");

char choice = ' ';
bool choice_set = false;
int chamada_time;

bool right = false;

long post_end;
#define POST_TIME 6000

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
    if (serial.toInt()) {
      estado = CHAM;
      #ifdef TYPE_LCD
        chamada_time = serial.toInt()
      #endif
    }
  } else if (estado == CHAM && available_bytes > 0) { //termina a chamada
    read_serial();
    post_end = millis() + POST_TIME;
    estado = POST;
  } else if (estado == POST) { // retorna à inat
    
    if (millis() > post_end) {
      choice = ' ';
      choice_set = false;
      estado = INAT;
    }
  }
}

// estado = cham
void get_choice() {
  if (digitalRead(BOT_A) == LOW) {
    choice = 'A';
    #ifdef TYPE_LED
    blink_led();
    #endif
  } else if (digitalRead(BOT_B) == LOW) {
    choice = 'B';
    #ifdef TYPE_LED
    blink_led();
    #endif
  } else if (digitalRead(BOT_C) == LOW) {
    choice = 'C';
    #ifdef TYPE_LED
    blink_led();
    #endif
  } else if (digitalRead(BOT_D) == LOW) {
    choice = 'D';
    #ifdef TYPE_LED
    blink_led();
    #endif
  }
  if (debug and estado == CHAM) {
    Serial.print("Choice = ");
    Serial.println(choice);
  }
}

void write_choice() {
  if (digitalRead(BOT_CON) == LOW) {
    String output = code + String(choice);
    choice_set = true;
    #ifdef TYPE_LED
    blink_led();
    delay(200);
    blink_led();
    #endif
    Serial.println(output);
  }
}

// estado = post
void set_right() {
  char right_choice = serial[0];
  if (debug) { Serial.print("Right choice: "); Serial.println(right_choice); }
  if (right_choice == choice && choice_set) {
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
  init_lcd();
  init_led();
}

void loop() {
  if (debug) Serial.println(estado);
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
