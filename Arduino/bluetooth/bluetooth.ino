#include <SoftwareSerial.h> //소프트웨어시리얼 라이브러리 추가
SoftwareSerial hc06(2,3);//소프트웨어시리얼  hc06 객체 선언

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  hc06.begin(9600); //소프트웨어시리얼 통신 동기화
}

void loop() {
  // put your main code here, to run repeatedly:
  if(hc06.available()){  //블루투스 모듈로 데이터가 전송되면
    Serial.write(hc06.read());  //시리얼 모니터 창에 출력
  }
  if(Serial.available()){ //시리얼 모니터에서 데이터가 입력되면
    hc06.write(Serial.read());  //블루투스 모듈로 데이터 전송
  }

}
