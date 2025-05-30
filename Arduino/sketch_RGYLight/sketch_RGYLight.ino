#define RED_LED D4
#define YELLOW_LED D3
#define GREEN_LED D2

int prevBtn = 0;
int currBtn =0;
int leadState = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);

  //pinMode(RED_LED, OUTPUT);
  //pinMode(YELLOW_LED,OUTPUT);
  //pinMode(GREEN_LED, OUTPUT);
}

void loop() {

  /*
  if(Serial.available() > 0)
  {
    char sData = Serial.read();
    if(sData =='r') digitalWrite(RED_LED,HIGH);
    else if(sData == 'y') digitalWrite(YELLOW_LED,HIGH);
    else if(sData == 'g') digitalWrite(GREEN_LED,HIGH);
    else if(sData == 'o')
    {
      digitalWrite(RED_LED,LOW);
      digitalWrite(YELLOW_LED,LOW);
      digitalWrite(GREEN_LED,LOW);
    }


  if(Serial.available() > 0){
    String StrData = Serial.readStringUntil('\n');
    if(StrData.indexOf("RED_ON") >= 0)           digitalWrite(RED_LED, HIGH);
    if(StrData.indexOf("RED_OFF") >= 0)     digitalWrite(RED_LED, LOW);
    if(StrData.indexOf("YELLOW_ON") >= 0)   digitalWrite(YELLOW_LED, HIGH);
    if(StrData.indexOf("YELLOW_OFF") >= 0)  digitalWrite(YELLOW_LED, LOW);
    if(StrData.indexOf("GREEN_ON") >= 0)    digitalWrite(GREEN_LED, HIGH);
    if(StrData.indexOf("GREEN_OFF") >= 0)   digitalWrite(GREEN_LED, LOW);
   }
  */

  currBtn = !digitalREad(BUTTON_PIN);
  if(currBtn !=prevBtn)
  {
    prevBtn = currBtn;
    if(currBtn ==1)
    {
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState);
    }
    delay(50);
  }
}
