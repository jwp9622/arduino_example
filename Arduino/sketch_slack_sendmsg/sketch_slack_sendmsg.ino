#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

const char *ssid = "AI_academy_302";
const char *password = "0532161010";
const char *url = "https://hooks.slack.com/services/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";
#define BUTTON_PIN D3

void setup() {
  Serial.begin(115200);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  WiFi.begin(ssid, password);
  Serial.println("Connecting");

  while (WiFi.status() != WL_CONNECTED)
  {
    Serial.print(".");
    delay(200);
  }

  Serial.println("Connected to Wifi network with IP Address : ");
  Serial.println(WiFi.localIP());
  Serial.println();

}

void loop() {
  int btnValue = btn_click();
  if(btnValue ==1){
    int httpResponseCode = sendSlack("초인종 버튼이 눌렀습니다.11");
    Serial.println(httpResponseCode);
  }

}

int btn_click(){
  static int prevBtn = 0;
  static int currBtn = 0;
  currBtn = !digitalRead(BUTTON_PIN);
  if(currBtn != currBtn){
    prevBtn = currBtn;
    if(currBtn ==1)
    {
      return 1;
    }
    delay(50);
  }
  return 0;
}

int sendSlack(String strMsg){
  int httpResponseCode;
  if(WiFi.status() == WL_CONNECTED){
    WiFiClientSecure client;
    client.setInsecure();
    client.connect(url, 443);
    HTTPClient https;
    https.begin(client, url);
    https.addHeader("Content-Type", "application/json");
    httpResponseCode = https.POST("{\"test\":\"" + strMsg + "\" }");
    https.end();
  }
    return httpResponseCode;
}


