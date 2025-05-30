#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <RtcDS1302.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); //0x3F -> 0x27
ThreeWire myWire(4,5,2);
RtcDS1302<ThreeWire> Rtc(myWire);
#define countof(a) (sizeof(a) / sizeof(a[0]))

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  lcd.init();
  Serial.print("Compiled:");
  Serial.print(__DATE__);
  Serial.print("\t");
  Serial.println(__TIME__);
  Rtc.Begin();
  RtcDateTime compiled = RtcDateTime(__DATE__, __TIME__);
  Rtc.SetDateTime(compiled);
}

void loop() {
  // put your main code here, to run repeatedly:
  char datestring[16];
  char timestring[16];
  RtcDateTime now = Rtc.GetDateTime();  //모듈의 현재 시간

  snprintf_P(datestring,countof(datestring), PSTR("  %04u.%02u.%02u"),
              now.Year(), now.Month(), now.Day());
  snprintf_P(timestring,countof(timestring), PSTR("  %02u.%02u.%02u"),
            now.Hour(), now.Minute(), now.Second());
                        
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print(datestring);
  lcd.setCursor(0,1);
  lcd.print(timestring);
  lcd.setCursor(0,10);
  Serial.println(String(datestring)+"\t"+String(timestring));
  delay(1000);
}
