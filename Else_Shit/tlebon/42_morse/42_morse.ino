#define MORSE_LG_PAUSE 1000
#define MORSE_SH_PAUSE 100
#define PINNO 7
void setup() {
  // put your setup code here, to run once:
  pinMode(7, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
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