#include <SoftwareSerial.h>
#define LED_PIN 13
#define BTtx 7
#define BTrx 8

SoftwareSerial hc06(BTtx, BTrx);

char data = 0;

void setup() {
  hc06.begin(9600);
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  Serial.println("....");
}

void loop() {
  if(hc06.available() > 0){
    data = hc06.read();
  }
  if(data == '0'){
    digitalWrite(LED_PIN, LOW);
    Serial.println("LED OFF");
  }
  else if(data == '1'){
    digitalWrite(LED_PIN, HIGH);
    Serial.println("LED ON");

  }
  data = 0;

}
