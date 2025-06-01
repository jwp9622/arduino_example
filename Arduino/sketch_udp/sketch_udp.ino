#include <ESP8266WiFi.h>
#include <WiFiUdp.h>


#define RED_LED D10
#define YELLOW_LED D9
#define GREEN_LED D8
#define BUTTON_1 D4
#define BUTTON_2 D3


const char *ssid = "AI_academy_302";
const char *password = "0532161010";

unsigned int localPort = 8888;
char packetBuffer[UDP_TX_PACKET_MAX_SIZE +1];
WiFiUDP Udp;

//#define PORT 1000
//WiFiClient client;
//WiFiServer server(PORT);

//#define RED_LED D2
//#define YELLOW_LED D3
//#define GREEN_LED D4

void setup() {

  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    Serial.println(".");
    delay(200);
  }
  Serial.println("Connected! IP address : ");
  Serial.println(WiFi.localIP());
  Serial.printf("UDP server on port %d\n", localPort);
  Udp.begin(localPort);
  
  //delay(200);
  //server.begin();
  pinMode(RED_LED, OUTPUT);
  pinMode(YELLOW_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(BUTTON_1, OUTPUT);
  pinMode(BUTTON_2, OUTPUT);

}

void loop() {
  int packetSize = Udp.parsePacket();
  if(packetSize){
    int n = Udp.read(packetBuffer, UDP_TX_PACKET_MAX_SIZE);
    packetBuffer[n] = 0;
    Serial.println(packetBuffer);
    Serial.println("--------");

    String strData = String(packetBuffer);
    Serial.println(strData);
    if(strData.indexOf("RED_ON") >= 0) digitalWrite(RED_LED,HIGH);
    else if(strData.indexOf("RED_OFF") >=0) digitalWrite(RED_LED,LOW);
    else if(strData.indexOf("YELLOW_ON") >=0) digitalWrite(YELLOW_LED,HIGH);
    else if(strData.indexOf("YELLOW_OFF") >=0) digitalWrite(YELLOW_LED,LOW);
    else if(strData.indexOf("GREEN_ON") >=0) digitalWrite(GREEN_LED,HIGH);
    else if(strData.indexOf("GREEN_OFF") >=0) digitalWrite(GREEN_LED,LOW);

  
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write("Communication success\n");
    Udp.endPacket();
  }

  if(btn_1_click() == 1){
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write("button 1 click\n");
    Udp.endPacket();
    delay(50);
  }

  if(btn_2_click() == 1){
    Udp.beginPacket(Udp.remoteIP(), Udp.remotePort());
    Udp.write("button 2 click\n");
    Udp.endPacket();
    delay(50);
  }


  /*
  while(!client.connected()){
    client = server.available();
  }
  client.println("Data transfer over TcP communication is successful!!");

  if(client.connected()){
    if(client.available()){
      String strData = client.readStringUntil('\n');
      Serial.println(strData);
      if(strData.indexOf("RED_ON") >= 0) digitalWrite(RED_LED,HIGH);
      else if(strData.indexOf("RED_OFF") >=0) digitalWrite(RED_LED,HIGH);
      else if(strData.indexOf("YELLOW_ON") >=0) digitalWrite(YELLOW_LED,LOW);
      else if(strData.indexOf("YELLOW_OFF") >=0) digitalWrite(YELLOW_LED,LOW);
      else if(strData.indexOf("GREEN_ON") >=0) digitalWrite(GREEN_LED,HIGH);
      else if(strData.indexOf("GREEN_OFF") >=0) digitalWrite(GREEN_LED,LOW);
    }
  } 
  */

  //delay(10000);
  
}

int btn_1_click(){
  static int prevBtn = 0;
  static int currBtn = 0;
  currBtn = !digitalRead(BUTTON_1);
  if(currBtn != prevBtn){
    prevBtn = currBtn;
    if(currBtn ==1) return 1;
  }
  return 0;
}

int btn_2_click(){
  static int prevBtn = 0;
  static int currBtn = 0;
  currBtn = !digitalRead(BUTTON_2);
  if(currBtn != prevBtn){
    prevBtn = currBtn;
    if(currBtn ==1) return 1;
  }
  return 0;
}



