// C++ code
//
int LED = 7;
int PIR = 8;
int val =0;

void setup()
{
  pinMode(LED,OUTPUT);
  pinMode(PIR,INPUT);
  Serial.begin(9600);
}


void loop()
{
  val = digitalRead(PIR);
  Serial.print("val=");
  Serial.println(val);
  
  if(val == HIGH){
  	digitalWrite(LED, HIGH);
    Serial.println("Welcome!");
  }
  else{
  	digitalWrite(LED,LOW);
    Serial.println("Nothing");
  }
 // delay(1000);
  
}
