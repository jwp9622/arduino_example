#include <ESP8266WiFi.h>
#define LED D10
//#include <WiFiUdp.h>

//#define RED_LED D10
//#define YELLOW_LED D9
//#define GREEN_LED D8
//#define BUTTON_1 D4
//#define BUTTON_2 D3


const char *ssid = "AI_academy_302";
const char *password = "0532161010";
int ledState = LOW;
WiFiServer server(80);


void setup() {

  Serial.begin(115200);
  Serial.println("");
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected : ");
  server.begin();
  Serial.print("Use this URL : ");
  Serial.println(WiFi.localIP());
  pinMode(LED, OUTPUT);

}

void loop() {
  WiFiClient client = server.available();
  if(!client){
    return;
  }
  Serial.println(F("new client"));
  client.setTimeout(5000); //default is 1000
  String request = client.readStringUntil('\r');
  Serial.println(F("request: "));
  Serial.println(request);
  if(request.indexOf("/LED=ON") != -1){
    digitalWrite(LED, HIGH);
    ledState = HIGH;
  }else if(request.indexOf("/LED=OFF") != -1){
    digitalWrite(LED, LOW);
    ledState = LOW;
  }

  while(client.available()){
    client.read();
  }
  client.println("HTTP/1.1 200 OK");
  client.println("Contet-Type : text/html");
  client.println("");
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("LED STATE:");
  if(ledState = HIGH){
    client.println("On");
  }else{
    client.println("Off");
  }
  client.println("<br><br>");
  client.println("click <a href=\"LED=ON\">here</a>LED ON<br>");
  client.println("click <a href=\"LED=OFF\">here</a>LED OFF<br>");
  client.println("</html>");
  Serial.println(F("Disconnecting from client"));

}



