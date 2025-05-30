#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); //0x3F -> 0x27

//문자열 포인터 선언
const char *ssid = "AI_academy_302";  //공유기이름
const char *password = "0532161010";  //공유기 비밀번호

const String url = "https://apis.data.go.kr/B552584/ArpltnInforInqireSvc/getCtprvnRltmMesureDnsty?serviceKey=1TZUp5wb6UBqknDnt%2BYSqrqfEm35n5FyxD8akm%2FYKiHYUilapxdfALSUbR2WGn98d8YIusX2i%2F24z5nwaUvOiA%3D%3D&returnType=xml&numOfRows=1&pageNo=11&sidoName=%EB%8C%80%EA%B5%AC&ver=1.0";

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid,password);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("-------");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print(WiFi.localIP());
    
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
      if (httpCode > 0)
      {
        String payload = https.getString();
        int pm10Value = payload.indexOf("</pm10Value>");
        if(pm10Value >=0){
          String tmp_str = "<pm10Value>";
          String dust_val = payload.substring(payload.indexOf("<pm10Value>")+tmp_str.length(), pm10Value);
          Serial.print("pm10 dust:");
          Serial.println(dust_val);

          lcd.setCursor(0,1);
          lcd.print("pm10 dust:");
          lcd.print(dust_val);

        }
        //String payload = https.getString();
        //Serial.println(payload);
      }
      https.end();
  }
  delay(60000);

}
