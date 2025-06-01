#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <PubSubClient.h>

const int ledPin = D8;
//const int echoPin = D7;
const char *ssid = "AI_academy_302";
const char *password = "0532161010";
const char *mqtt_server = "test.mosquitto.org";
const int mqttPort = 1883;
const String clientId = "daegu-daheeIot-2025";
const char *mqttTopic = "daheeIot-2025/iot/wemos/led";
long lastMsgTime = 0;

WiFiClient wemosD1R1;
PubSubClient client(wemosD1R1);

//#define LED D10
//#include <WiFiUdp.h>

//#define RED_LED D10
//#define YELLOW_LED D9
//#define GREEN_LED D8
//#define BUTTON_1 D4
//#define BUTTON_2 D3
//int ledState = LOW;
//WiFiServer server(80);


void setup() {

  Serial.begin(115200);
  Serial.println("");
  Serial.print("Connecting to : ");
  WiFi.begin(ssid, password);

  while(WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected : ");
  Serial.print("IP 주소 : ");
  Serial.println(WiFi.localIP());

  client.setServer(mqtt_server, mqttPort);
  client.setCallback(callback);
  pinMode(ledPin,OUTPUT);
  //pinMode(echoPin, INPUT);
  //pinMode(trigPin, OUTPUT);
  //digitalWrite(trigPin, LOW);
  //delayMicroseconds(2);

}
void loop() {
  if(!client.connected()){
    reconnect();
  }
  client.loop();
  /*
  long now = millis();
  if(now - lastMsgTime > 1000){
    lastMsgTime = now;
    float sensorValue = readUltrasonicSensor();
    char sensorString[8];
    dtostrf(sensorValue, 1, 2, sensorString);
    client.publish("daegu-daheeIot-2025/iot/wemos",sensorString);
  }
  */
}

void callback(char *topic, byte *payload, unsigned int length){
  Serial.print("receivedmessage:");
  Serial.print(topic);
  Serial.print(" ");
  for(int i =0;i<length;i++){
    Serial.print((char)payload[i]);
  }
  Serial.println();

  if(strcmp(topic, mqttTopic) == 0){
    if(payload[0] == '1'){
      digitalWrite(ledPin, HIGH);
    }else if(payload[0] == '0'){
      digitalWrite(ledPin, LOW);
    }
  }
}

void reconnect(){
  while(!client.connected()){
    Serial.print("MQTT 연결 시도 중...");
    Serial.print("클라이이언트 ID:");
    Serial.println(clientId);
    if(client.connect(clientId.c_str())){
      Serial.println("연결됨");
      client.subscribe(mqttTopic);
    }else{
      Serial.print("실패, rc=");
      Serial.print(client.state());
      Serial.println("5초 후 다시 시도");
      delay(5000);
    }
  }
}

/*
float readUltrasonicSensor(){
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  pinMode(echoPin, INPUT);
  float duration = pulseIn(echoPin, HIGH);
  float distance = duration * 0.0343 / 2.0;
  Serial.print("Distance : ");
  Serial.print(distance);
  Serial.println("(cm) ");
  return distance;
}
*/

