#define VR_PIN A0
#define LED_PIN D2

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int vrValue = analogRead(VR_PIN);
  Serial.print(vrValue);
  Serial.print(",");
  int ledValue = map(vrValue, 0, 1024, 0, 255);
  Serial.println(ledValue);
  analogWrite(LED_PIN, ledValue);
}
