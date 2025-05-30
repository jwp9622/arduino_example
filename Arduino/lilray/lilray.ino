// C++ code
//

int en12=7;
int in1 = 6;
int in2 = 5;

void setup()
{
	pinMode(LED_BUILTIN, OUTPUT);
}

void loop()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);
  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);

}
