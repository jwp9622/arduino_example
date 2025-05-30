#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); //0x3F -> 0x27

//문자열 포인터 선언
const char *ssid = "AI_academy_302";  //공유기이름
const char *password = "0532161010";  //공유기 비밀번호

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP,"kr.pool.ntp.org", 32400, 3600000);

void setup() {

  // put your setup code here, to run once:
  Serial.begin(9600);
  
  WiFi.begin(ssid,password);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  timeClient.begin();
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("NTP TIME");
}

void loop() {

  // put your main code here, to run repeatedly:
  timeClient.update();
  Serial.println(timeClient.getFormattedTime());
  lcd.setCursor(0,1);
  lcd.print(timeClient.getFormattedTime());
  delay(1000);

}
