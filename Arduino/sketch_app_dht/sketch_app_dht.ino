#include <SoftwareSerial.h>
#include "DHT.h"
#define DHTPIN 4
#define DHTTYPE DHT11

#define BTtx 7
#define BTrx 8
SoftwareSerial hc06(BTtx, BTrx);
DHT dht(DHTPIN, DHTTYPE);

byte t;
byte h;

void setup() {
  hc06.begin(9600);
  dht.begin(9600);
  Serial.begin(9600);
  Serial.println("setup");
}

void loop() {
  delay(2000);
  t = dht.readTemperature();
  h = dht.readHumidity();
  //Serial.print('d');Serial.print(',');Serial.print(t);Serial.print(',');Serial.println(h);

  if(!isnan(h) || isnan(t)) {
    hc06.print('d');
    hc06.print(',');
    hc06.print(t);
    hc06.print(',');
    hc06.print(h);
  }
}
