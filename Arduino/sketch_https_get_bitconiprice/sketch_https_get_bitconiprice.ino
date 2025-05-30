#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>

#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); //0x3F -> 0x27

//문자열 포인터 선언
const char *ssid = "AI_academy_302";  //공유기이름
const char *password = "0532161010";  //공유기 비밀번호

const String url = "https://api.upbit.com/v1/ticker?markets=KRW-BTC";

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

      String payload = https.getString();
      Serial.println(payload);
      
      
      if (httpCode > 0)
      {
        DynamicJsonDocument doc(1024);
        String payload = https.getString();
        payload = payload.substring(1,payload.length()-1);
        deserializeJson(doc, payload);
        JsonObject obj = doc.as<JsonObject>();
        long price = obj[String("trade_price")];
        
        Serial.print("BTC Price:");
        Serial.println(price);

        lcd.setCursor(0,1);
        lcd.print("BTC:");
        lcd.print(price);


      }
      

      https.end();
  }
  delay(60000);

}
