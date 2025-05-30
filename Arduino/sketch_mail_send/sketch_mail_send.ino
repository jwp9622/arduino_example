#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP_Mail_Client.h>

#define WIFI_SSID "AI_academy_302"
#define WIFI_PASSWORD "0532161010"
#define SMTP_HOST "smtp.gmail.com"

#define SMTP_PORT esp_mail_smtp_port_587

#define AUTHOR_EMAIL "jwp9622@gmai.com"
#define AUTHOR_PASSWORD "!5086qkrwjddnjs"

SMTPSession smtp;

String strSender = "WemosRIDI"
String strRecipientName = "SKY";
String RecipientMail = "jwp9622@naver.com"
String strSubject = "WemosR1D1 mail Test";
String strMsg = "구글메일에서 네이버 메일로 이메일 보낵"

#define TRIG_PIN D7
#define ECHO_PIN D6

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  Serial.print("Connecting to AP");
  Wifi.begin(WIFI_SSID, WIFI_PASSWORD);
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(200);
  }
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address : ");
  Serial.println(WiFi.localIP);
  Serial.println();

  SendEmail();
}

void loop() {
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  unsigned long duration=pulseIn(ECHO_PIN, HIGH);

  float distanceCM = ((3400.0*(float)duration)/1000000.0)/2.0;
  Serial.println(distanceCM);
  if(distanceCM > 10 && distanceCM < 30){
    Serial.println("움직임 감지");
    delay(1000);
  }
}
