#define HIGH_LIGHT_VAL 350
#define LOW_LIGHT_VAL 140

#define PIN_RED   5
#define PIN_BLUE  6


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int red_val;
  int blue_val;
  int read_val;

  read_val = analogRead(A0);
  read_val = constrain(read_val, LOW_LIGHT_VAL, HIGH_LIGHT_VAL);

  // Red LED
  red_val = map(read_val, LOW_LIGHT_VAL, HIGH_LIGHT_VAL, 255, 0);
  analogWrite(PIN_RED, red_val);

  // Blue LED
  blue_val = map(read_val, LOW_LIGHT_VAL, HIGH_LIGHT_VAL, 0, 255);
  analogWrite(PIN_BLUE, blue_val);

  
  
  // int sensorValue = analogRead(A0);
  // // print out the value you read:
  // Serial.println(sensorValue);

  Serial.println(read_val);
}

/* Infos

  - Photoresitance: eclairage haut = valeur en ohm basse et inversement
 
  - U2 = U x R2 / (R1 + R2) -> R1 = photoresistance
  --> ohm augmentent --> voltage diminue

*/