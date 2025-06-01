#include <SoftwareSerial.h>
#define POSTENTIOMETER_PIN A0
#define BTtx 7
#define BTrx 8

SoftwareSerial hc06(BTtx, BTrx);

void setup() {
  hc06.begin(9600);
  Serial.begin(9600);
  Serial.println("start");
}

void loop() {
  byte sendData[3];
  unsigned int sensorValue = analogRead(POSTENTIOMETER_PIN);
  Serial.print(sensorValue);
  Serial.print(" : ");

  sendData[0] = 'a';
  sendData[1] = sensorValue / 256;
  sendData[2] = sensorValue % 256;

  for(byte i=0;i<3;i++){
    Serial.print(sendData[i]);
    Serial.print(", ");
  }
  Serial.println (" "); 
  if(hc06.available() >0){
    byte serialData = hc06.read();
    if(serialData = 49){
      for(byte i=0;i<3;i++){
        hc06.write(sendData[i]);
      }
    }
  }

}
