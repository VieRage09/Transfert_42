#include "DHT.h"

#define BLUEPIN 5
#define REDPIN 6
#define MOTORPIN 9
#define PHOTOPIN A0

#define THRESHOLD 0.2f
#define LOWLUM 230

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

float tMoyen = 0;
bool  flip = false;
unsigned long lastBlink = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  dht.begin();

  pinMode(REDPIN, OUTPUT);
  pinMode(BLUEPIN, OUTPUT);
  pinMode(MOTORPIN, OUTPUT);
  pinMode(PHOTOPIN, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  float surplus = checkSurplusHeat();
  
  handleLed(surplus);

  flipFlop();
  if (surplus > THRESHOLD)
  {
    if (!flip)
      digitalWrite(MOTORPIN, HIGH);
    else
      digitalWrite(MOTORPIN, LOW);
  }
  else
  {
    if (!flip)
      digitalWrite(MOTORPIN, LOW);
    else
      digitalWrite(MOTORPIN, HIGH);
  }
  
  Serial.println();
}

void  handleLed(float surplus)
{
  int freq;


  if (surplus > THRESHOLD){
    digitalWrite(BLUEPIN, LOW);

    freq = 100 / (surplus - THRESHOLD);
    if (millis() - freq > lastBlink)
    {
      lastBlink = millis();
      digitalWrite(REDPIN, HIGH);
    }
    else
      digitalWrite(REDPIN, LOW);
  }
  else
  {
    digitalWrite(REDPIN, LOW);
    digitalWrite(BLUEPIN, HIGH);
  }
}

void  flipFlop()
{
  int   read_val = analogRead(PHOTOPIN);
  if (read_val < LOWLUM)
    flip = !flip;
  Serial.print(F("Lum: "));
  Serial.println(read_val);
}

float checkSurplusHeat()
{
  float t = dht.readTemperature();

  if (isnan(t)){
    Serial.println(F("Failed to read from DHT sensor"));
    return (-1);
  }
  Serial.print(F("Heat: "));
  Serial.print(t);
  Serial.println("C");
  if (tMoyen == 0)
    tMoyen = t;
  if (t > tMoyen)
    return (t - tMoyen);
}