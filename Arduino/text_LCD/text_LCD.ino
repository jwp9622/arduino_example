// C++ code
//
#include<Wire.h>
#include<LiquidCrystal_I2C.h>
#include<Keypad.h>

//lcd 변수
LiquidCrystal_I2C lcd(0x27, 16, 2);
byte customChar[4][8]={
  {0x00, 0x0A, 0x00, 0x11, 0x0E, 0x00, 0x00},
  {0x1F, 0x11, 0x0A, 0x04, 0x0A, 0x11, 0x1F},
  {0x0A, 0x0A, 0x1F, 0x11, 0x11, 0x0E, 0x04},
  {0x0E, 0x11, 0x11, 0x1F, 0x1B, 0x1B, 0x1F}
};

//keypad 변수
const byte rows =4;
const byte cols = 4;

char keyValues[rows][cols]={
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[rows] = {9,8,7,6};
byte colPins[cols] = {5,4,3,2};

Keypad userKeypad = Keypad(makeKeymap(keyValues), 
                           rowPins, colPins, rows,cols);
char pressedKey;



void setup()
{
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.setCursor(0,0);


  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  //lcd.autoscroll();
  lcd.print("Input Number");

  lcd.setCursor(0,1);
  //lcd.autoscroll();
  //lcd.setCursor(0,1);
  //for(int i=0;i<=4;i++){
  //	lcd.print(i);
  //  delay(500);
  //}
  
}

void loop()
{
  pressedKey = userKeypad.getKey();
  if(pressedKey !=NO_KEY){
  	Serial.print("Pressed Key :");
    Serial.println(pressedKey);
    
    //숫자 출력
    lcd.print(pressedKey);
    
  }

}

