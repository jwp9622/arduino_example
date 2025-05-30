// C++ code
//
// 기울기 센터 작
int TILT = 8;
int GLED = 6;
int RLED = 5;

void setup()
{
  Serial.begin(9600);
  pinMode(TILT, INPUT_PULLUP);
  pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  int tiltVal = digitalRead(TILT);
  Serial.print("Readed Value =");
  Serial.println(tiltVal);
  if(tiltVal == LOW){
  	digitalWrite(LED_BUILTIN,HIGH);
    delay(500);
  }else{
    digitalWrite(LED_BUILTIN,LOW);
    delay(500);
  }
}