#include <ESP8266WiFi.h>

const char *ssid = "AI_academy_302";
const char *password = "0532161010";

#define PORT 1000

WiFiClient client;
WiFiServer server(PORT);

#define RED_LED D10
#define YELLOW_LED D9
#define GREEN_LED D8

void setup() {

  Serial.begin(115200);
  WiFi.begin(ssid, password);
  while(WiFi.status() != WL_CONNECTED){
    Serial.println("Connecting to WiFi..");
    delay(200);
  }
  Serial.println("");
  Serial.println(WiFi.localIP());
  Serial.print("Port : ");
  Serial.println(PORT);
  Serial.println("TCP Communication Test");
  delay(200);
  server.begin();

  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

}

void loop() {
  while(!client.connected()){
    client = server.available();
  }
  //client.println("Data transfer over TcP communication is successful!!");

  if(client.connected()){
    if(client.available()){
      String strData = client.readStringUntil('\n');
      Serial.println(strData);
      if(strData.indexOf("RED_ON") >= 0) digitalWrite(RED_LED,HIGH);
      else if(strData.indexOf("RED_OFF") >=0) digitalWrite(RED_LED,LOW);
      else if(strData.indexOf("YELLOW_ON") >=0) digitalWrite(YELLOW_LED,HIGH);
      else if(strData.indexOf("YELLOW_OFF") >=0) digitalWrite(YELLOW_LED,LOW);
      else if(strData.indexOf("GREEN_ON") >=0) digitalWrite(GREEN_LED,HIGH);
      else if(strData.indexOf("GREEN_OFF") >=0) digitalWrite(GREEN_LED,LOW);
    }
  } 

  //delay(10000);

}

