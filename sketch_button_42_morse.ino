#define PINNO LED_BUILTIN
#define MORSE_SH_PAUSE 100
#define MORSE_LG_PAUSE 1000


void setup() {
  // put your setup code here, to run once:
  pinMode(PINNO, OUTPUT);

  pinMode(2, INPUT_PULLUP);
  pinMode(7, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(2), isr_42, HIGH);
}


void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(7, HIGH);
  // 4
  short_morse();
  short_morse();
  short_morse();
  short_morse();
  long_morse();
  // 2
  short_morse();
  short_morse();
  long_morse();
  long_morse();
  long_morse();
}

void isr_42() {
  if (digitalRead(2) == HIGH)
  {
    digitalWrite(7, HIGH);
  }
  else
  {
    digitalWrite(7, LOW);
  }
}

void  short_morse(){
  digitalWrite(PINNO, HIGH);
  delay(MORSE_SH_PAUSE);
  digitalWrite(PINNO, LOW);
  delay(MORSE_LG_PAUSE);
}

void long_morse(){
  digitalWrite(PINNO, HIGH);
  delay(MORSE_LG_PAUSE);
  digitalWrite(PINNO, LOW);
  delay(MORSE_LG_PAUSE);
}