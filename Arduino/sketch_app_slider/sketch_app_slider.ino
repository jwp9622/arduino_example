#include <SoftwareSerial.h>

#define RGB_RED_PIN 9
#define RGB_GREEN_PIN 10
#define RGB_BLUE_PIN 11
#define BTtx 7
#define BTrx 8
SoftwareSerial BT(BTtx, BTrx);

void setup() {
  BT.begin(9600);
  Serial.begin(9600);
  Serial.println("setup");
}

void loop() {
  
  if(BT.available() >0){
    unsigned int data1 = BT.read();
    unsigned int data2 = BT.read();
    unsigned int final_data = data1 + (data2*256);
    Serial.println(final_data);
    if(final_data >=1000 && final_data <= 2255){
      analogWrite(RGB_RED_PIN, final_data - 1000);
    }else if(final_data >=2000 && final_data <= 2255){
      analogWrite(RGB_GREEN_PIN, final_data - 2000);
    }else if(final_data >=3000 && final_data <= 3255){
      analogWrite(RGB_GREEN_PIN, final_data - 3000);
    }
  
  }

}
