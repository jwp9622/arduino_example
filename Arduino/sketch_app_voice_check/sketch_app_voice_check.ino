#include <SoftwareSerial.h>
#define RED_LED_PIN 12
#define BLUE_LED_PIN 13
#define BTtx 7
#define BTrx 8

SoftwareSerial hc06(BTtx, BTrx);
void setup() {
  hc06.begin(9600);
  Serial.begin(9600);
  pinMode(RED_LED_PIN, OUTPUT);
  pinMode(BLUE_LED_PIN, OUTPUT);
  Serial.println("블루투스 연결");  
}

void loop() {
  //Serial.println("loop start");  
  //Serial.println(hc06.available());  

  if(hc06.available() > 0){

    Serial.println(hc06.available());
    byte data = hc06.read();
    Serial.println(data);
    if(data == 1) {
      digitalWrite(BLUE_LED_PIN, HIGH);
      Serial.println("BLUE_LED on");
    }
    else if(data == 2) {
      digitalWrite(BLUE_LED_PIN, LOW);
      Serial.println("BLUE_LED off");
    }
    else if(data == 3) {
      digitalWrite(RED_LED_PIN, HIGH);
      Serial.println("RED_LED on");
    }
    else if(data == 4) {
      digitalWrite(RED_LED_PIN, LOW);
      Serial.println("RED_LED off");
    }
    else if(data == 5) {
      digitalWrite(BLUE_LED_PIN, HIGH);
      digitalWrite(RED_LED_PIN, HIGH);
      Serial.println("ALL_LED on");
    }
    else if(data == 6) {
      digitalWrite(BLUE_LED_PIN, LOW);
      digitalWrite(RED_LED_PIN, LOW);
      Serial.println("ALL_LED off");
    }

    data = 0;
  }

}
