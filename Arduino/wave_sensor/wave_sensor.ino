// C++ code
//
#include <Adafruit_LiquidCrystal.h>
Adafruit_LiquidCrystal lcd(0x20);

int TRIG = 9;
int ECHO = 8;

void setup()
{
  pinMode(TRIG,OUTPUT);
  pinMode(ECHO, INPUT);
  Serial.begin(9600);
    
  lcd.begin(16,2);
}

String message;

void loop()
{
  digitalWrite(TRIG, LOW);
  delayMicroseconds(5);
  digitalWrite(TRIG, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG, LOW);
  
  long duration = pulseIn(ECHO, HIGH);
  float distance = (float)(340.0*duration/10000.0)/2.0;
  
  //시리얼 모니터에 출력하기
  Serial.print("Duration=");
  Serial.println(duration); //출력하기
  Serial.println("us");
  Serial.print("Distance=");
  Serial.println(distance); //출력하기
  Serial.println("cm");
  Serial.println("-----------------");
  
  lcd.clear();
  lcd.print("Duration=");
  lcd.print(duration);
  
  lcd.setCursor(0,1);
  lcd.print("Distance=");
  lcd.print(distance);

  delay(1000);
  
  

}