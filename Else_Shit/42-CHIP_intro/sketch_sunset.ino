  #define VALUE 1
#define DEL 10
int   i = 255;

void setup() {
  // put your setup code here, to run once:
  pinMode(8, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  if (digitalRead(8) == HIGH && i < 255)
  {
    i += VALUE;
    analogWrite(3, i);
    delay(DEL);
  }
  else if (digitalRead(8) == LOW && i > 0)
  {
    i -= VALUE;
    analogWrite(3, i);
    delay(DEL);
  }
}
