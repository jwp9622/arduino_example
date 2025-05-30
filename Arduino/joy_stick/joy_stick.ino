int Joy_x = A0;
int Joy_y = A1;
int Joy_z = 2;

void setup() {
  // put your setup code here, to run once:

  pinMode(Joy_z, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int x = analogRead(Joy_x);
  int y = analogRead(Joy_y);
  int z = digitalRead(Joy_z);

  Serial.print("X:");
  Serial.print(x);
  Serial.print(", Y:");
  Serial.print(y);
  Serial.print(", Z:");
  Serial.print(z);

  if(z == 0)
    Serial.println("     Pressed!!");
  else
    Serial.println("     Nothing!!");
  delay(500);

}
