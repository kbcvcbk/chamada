#ifdef TYPE_LED
#define LED_R 9
#define LED_G 10
#define LED_B 11
#endif
void update_led_state() {
#ifdef TYPE_LED
  if (estado == INAT) {
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, LOW);
  } else if (estado == CHAM && choice_set) {
    digitalWrite(LED_R, HIGH);
    digitalWrite(LED_G, HIGH);
    digitalWrite(LED_B, LOW);
  } else if (estado == CHAM && !choice_set) {
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, LOW);
    digitalWrite(LED_B, HIGH);
  } else if (estado == POST && right) {
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, HIGH);
    digitalWrite(LED_B, LOW);
  } else if (estado == POST && !right) {
    digitalWrite(LED_R, LOW);
    digitalWrite(LED_G, HIGH);
    digitalWrite(LED_B, LOW);
  }
#endif
}

