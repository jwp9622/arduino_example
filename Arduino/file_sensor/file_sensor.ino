int ledPin = 13;
int buzzerPin = 6;
int flamePin = 2;

void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(flamePin, INPUT);

  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int pin = digitalRead(flamePin);

  Serial.print("flamePin=");
  Serial.println(pin);

  if(digitalRead(flamePin) == HIGH){
    digitalWrite(ledPin, HIGH);
    digitalWrite(buzzerPin, HIGH);
    delay(1000);    
  }else{
    digitalWrite(ledPin, LOW);
    digitalWrite(buzzerPin, LOW);
  }
  delay(1000);

}
