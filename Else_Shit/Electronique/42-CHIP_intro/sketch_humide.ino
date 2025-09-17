#include "DHT.h"

#define DHTPIN 2

#define REDPIN 6
#define BLUEPIN 5

#define THRESHOLD 70.0f

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();

  pinMode(REDPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  delay(2000);

  float h = dht.readHumidity();

  if (isnan(h)){
    Serial.println(F("Failed to read humidity from dht"));
    return ;
  }

  if (h > THRESHOLD){
    digitalWrite(REDPIN, LOW);
    digitalWrite(BLUEPIN, HIGH);
  }
  else
  {
    digitalWrite(REDPIN, HIGH);
    digitalWrite(BLUEPIN, LOW);
  }
  Serial.print(F("Humidity: "));
  Serial.print(h);
  Serial.println("%");
}
