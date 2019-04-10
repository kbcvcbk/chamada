bool initi = false;

int codeSize = 2;
String code;

int a = 2;
int b = 3;
int con = 4;
int led = 8;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(a, INPUT_PULLUP);
  pinMode(b, INPUT_PULLUP);
  pinMode(con, INPUT_PULLUP);
  pinMode(led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (!initi) {
    code = "";
    digitalWrite(led, HIGH);
    int c = 0;
    while (c < codeSize) {
      if (!digitalRead(a)) {
        digitalWrite(led, LOW);
        delay(200);
        digitalWrite(led, HIGH);
        code = code + "0";
        c++;
      }
      if (!digitalRead(b)) {
        digitalWrite(led, LOW);
        delay(200);
        digitalWrite(led, HIGH);
        code = code + "1";
        c++;
      }
    }
    initi = true;
  }
  if (init) {
    digitalWrite(led, LOW);
    if (!digitalRead(a)) {
      digitalWrite(led, HIGH);
      Serial.println(code+"0");
      delay(200);
      digitalWrite(led, LOW);
      }
    if (!digitalRead(b)) {
      digitalWrite(led, HIGH);
      Serial.println(code+"1");
      delay(200);
      digitalWrite(led, LOW);
      }
    }
}
