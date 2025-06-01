#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL6q8gYButs"
#define BLYNK_TEMPLATE_NAME "Quickstart Template"
#define BLYNK_AUTH_TOKEN "_-QW8_jbLDiT_fc5pfb9FqGDeuebcf3-"
#define ledPin D4
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

BLYNK_WRITE(V0){
  int pinValue = param.asInt();
  Serial.print("V0로 전송된 값 : ");
  Serial.println(pinValue);
  if(pinValue == 0){
    digitalWrite(ledPin, LOW);
  }else if (pinValue == 1){
    digitalWrite(ledPin, HIGH);
  }
}

char ssid[] = "AI_academy_302";
char pass[] = "0532161010";

void setup() {
  Serial.begin(9600);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
}

void loop() {
  Blynk.run();
}
