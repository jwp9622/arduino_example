#include <NTPClient.h>
#include <WiFiUdp.h>
#include <Wire.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include <time.h>

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); //0x3F -> 0x27

//문자열 포인터 선언
const char *ssid = "AI_academy_302";  //공유기이름
const char *password = "0532161010";  //공유기 비밀번호

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP,"kr.pool.ntp.org", 32400, 3600000);

const String url = "https://api.upbit.com/v1/ticker?markets=KRW-BTC";


void printDigits(int digits){
  // utility for digital clock display: prints preceding colon and leading 0
  Serial.print(":");
  if(digits < 10)
    Serial.print('0');
  Serial.print(digits);
}


void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid,password);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }

  timeClient.begin();

  Serial.println("-------");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  lcd.init();
  lcd.backlight();
  //lcd.setCursor(0,0);
  //lcd.print(WiFi.localIP());
    
}

void loop() {


  if(WiFi.status() == WL_CONNECTED)
  {
      WiFiClientSecure client;
      client.setInsecure();
      client.connect(url, 443);
      HTTPClient https;
      https.begin(client, url);
      int httpCode = https.GET();

      //String payload = https.getString();
      //Serial.println(payload);
      
      if (httpCode > 0)
      {
        //json 값 받아오기
        DynamicJsonDocument doc(1024);
        String payload = https.getString();
        payload = payload.substring(1,payload.length()-1);
        deserializeJson(doc, payload);
        JsonObject obj = doc.as<JsonObject>();
        long price = obj[String("trade_price")];
        
        //시리얼 모니터에 출력
        Serial.print("BTC Price:");
        Serial.println(price);

        //시리얼 모니터에 표시 NTP 시간표시
        timeClient.update();
        //Serial.println(timeClient.getFormattedTime());


        //날짜계산
        time_t eptm;
        eptm = timeClient.getEpochTime();
        struct tm* timenow;
        timenow = localtime(&eptm);
        int Yr = 1900+timenow->tm_year;
        int Month = 1+timenow->tm_mon;
        int DoM = timenow->tm_mday;
        int Hr = timenow->tm_hour;
        int Mn = timenow->tm_min;
        int Sc = timenow->tm_sec;
        Serial.printf("%4d-%02d-%02d %d:%02d:%02d\n", Yr, Month, DoM, Hr, Mn, Sc);        
        String cDate = String(String(Yr)+"."+String(Month)+"."+String(DoM)+" "+String(Hr)+":"+String(Mn)+":"+String(Sc));

        //LCD 날짜 시간 표시
        lcd.setCursor(0,0);
        //lcd.print("TIME:"); //기존 시간 표시
        //lcd.print(timeClient.getFormattedTime()); //기존 시간표시
        lcd.print(cDate); //기존 시간 표시

        //LCD에 비트코인 가격 표시
        lcd.setCursor(0,1);
        lcd.print("BTC:");
        lcd.print( comma(price));
                
      }
          
      https.end();
  }
  delay(50000);

}

//콤마 표시
String comma(long number){
  String numstr = String(number);
  int len = numstr.length();
  String result;

  for(int i=0;i<len;i++){
    result+= numstr[i];
    if( (len-i-1) % 3 ==0 && i != len-1){
      result +=",";
    }
  }
  return result;
}