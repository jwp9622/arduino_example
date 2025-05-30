#include<Stepper.h>
const int stepsPerRevolution = 2048;
Stepper stepper(stepsPerRevolution, 8, 10, 9, 11);

void setup() {
  // put your setup code here, to run once:
  stepper.setSpeed(10);

}

void loop() {
  // put your main code here, to run repeatedly:
  stepper.step(stepsPerRevolution);
  delay(1000);
  stepper.step(-stepsPerRevolution);
  delay(1000);

}
