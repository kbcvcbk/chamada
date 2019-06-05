#ifdef TYPE_LED
#define LED_R 11
#define LED_G 10
#define LED_B 9
#endif

int* current_color;

int roxo[3] = {150, 0, 255};
int larj[3] = {200, 220, 0};
int verm[3] = {120, 0, 0};
int verd[3] = {0, 120, 0};
int none[3] = {0, 0, 0};

void init_led() {
#ifdef TYPE_LED
  pinMode(LED_R, OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_B, OUTPUT);
#endif
}

void update_led_state() {
#ifdef TYPE_LED
  if (estado == INAT) {
    change_color(none);
  } else if (estado == CHAM && !choice_set) {
    change_color(larj);
  } else if (estado == CHAM && choice_set) {
    change_color(roxo);
  } else if (estado == POST && right) {
    change_color(verd);
  } else if (estado == POST && !right) {
    change_color(verm);
  }
#endif
}

void change_color (int* color) {
#ifdef TYPE_LED
  current_color = color;
  led_color_change(color);
#endif
}

#ifdef TYPE_LED
void led_color_change(int* color) {
  analogWrite(LED_R, color[0]);
  analogWrite(LED_G, color[1]);
  analogWrite(LED_B, color[2]);
}

void blink_led() {
  led_color_change(none);
  delay(200);
  led_color_change(current_color);
}
#endif
