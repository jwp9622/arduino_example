#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>
#include <ArduinoJson.h>

const char *ssid = "AI_academy_302";
const char *password = "0532161010";

#define BOTtoken "7942057004:AAEJ8SLO8lowWmDiX9--gof_lVDUAf2iC0U"
#define CHAT_ID "7684636974"

X509List cert(TELEGRAM_CERTIFICATE_ROOT);

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  configTime(0, 0, "pool.ntp.org");
  client.setTrustAnchors(&cert);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
  Serial.println(WiFi.localIP());
}

void loop() {
  Serial.println("메시지 보내기---");
  // put your main code here, to run repeatedly:
  bot.sendMessage(CHAT_ID, "하이!! Wemos에서 보내는 메시지입니다. ", "");
  delay(600000);
}
