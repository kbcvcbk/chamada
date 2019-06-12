// TESTE - CONTROLE ALUNO VERSÃO LED RGB
// Projeto AQ! por grupo Presente
// Teste escrito por Kalil <kbcv@cesar.school>

#define BOT_A 2
#define BOT_B 3
#define BOT_C 4
#define BOT_D 5
#define BOT_CON 6

// global
#define SERIAL 0
#define COLOR 1
#define BUTTON 2
String serial;
int state = COLOR;

//led vars
#define LED_R 9
#define LED_G 10
#define LED_B 11

int * current_color;
int colors[5];

// led = common gnd
//int roxo[3] = {150, 0, 255};
//int larj[3] = {200, 220, 0};
//int verm[3] = {120, 0, 0};
//int verd[3] = {0, 120, 0};
//int none[3] = {0, 0, 0};

//led = common 5V
int roxo[3] = {140, 255, 0};
int larj[3] = {70, 20, 255};
int verm[3] = {130, 255, 255};
int verd[3] = {255, 130, 255};
int none[3] = {255, 255, 255};

void setup_serial() {
  Serial.begin(9600);
  Serial.println("Serial inicializada com sucesso!!");
}

void setup_led() {
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
  colors[0] = &roxo;
  colors[1] = &larj;
  colors[2] = &verm;
  colors[3] = &verd;
  colors[4] = &none;
}

void setup_button() {
  for (int i = BOT_A; i <= BOT_CON; i++) {
    pinMode(i, INPUT_PULLUP);
  }
}

void setup() {
  setup_serial();
  setup_led();
  setup_button();
}

void led_color_change(int* color) {
  current_color = color;
  led_color_set(color);
}

void led_color_set(int* color) {
  analogWrite(LED_R, color[0]);
  analogWrite(LED_G, color[1]);
  analogWrite(LED_B, color[2]);
}

void led_blink() {
  led_color_set(none);
  delay(200);
  led_color_set(current_color);
}

void loop() {
  int bytes = Serial.available();
  if (bytes > 0)
  {
    serial = Serial.readString();
    serial.trim();
    if (serial == "color")
    {
      state = COLOR;
      Serial.println("Mudando estado para COLOR");
    }
    else if (serial == "button")
    {
      state = BUTTON;
      Serial.println("Mudando estado para BUTTON");
    }
    else if (serial == "serial")
    {
      state = SERIAL;
      Serial.println("Mudando estado para SERIAL");
    }
  }
  switch (state) {
    case COLOR:
      for (int i; i < 5; i++)
      {
        led_color_change(colors[i]);
        delay(1000);
        led_blink();
        delay(400);
      }
      break;
    case BUTTON:
      for (int i = 2; i <= 6; i++)
        if (!digitalRead(i)) {
          Serial.print("Botão ");
          switch (i) {
            case 2: Serial.println("A"); break;
            case 3: Serial.println("B"); break;
            case 4: Serial.println("C"); break;
            case 5: Serial.println("D"); break;
            case 6: Serial.println("confirma"); break;
          }
          delay(300);
        }
      break;
    case SERIAL:
      led_color_change(none);
      if (bytes > 0) {
        Serial.print("Lido da serial: ");
        Serial.println(serial);
      }
  }
}
