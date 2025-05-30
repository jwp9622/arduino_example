// C++ code
//
int SIG = A0;
int G = 8;
int Y =9;
int R=10;

void setup()
{
  pinMode(G,OUTPUT);
  pinMode(Y,OUTPUT);
  pinMode(R,OUTPUT);
  Serial.begin(9600);
}


void loop()
{
  int moisture = analogRead(SIG);
  Serial.print("Soil oisture : ");
  Serial.println(moisture);
  
  digitalWrite(G, LOW);
  digitalWrite(Y, LOW);
  digitalWrite(R, LOW);
  
  if(moisture <100){
  	digitalWrite(R,HIGH);
    Serial.println(">> Dry");
  }
  else if(moisture<400){
  	digitalWrite(Y,HIGH);
    Serial.println(">> Little Wet");
  }
  else {
  	digitalWrite(G,HIGH);
    Serial.println(">> Wet");
  }
	delay(500);
  
}
