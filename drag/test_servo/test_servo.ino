#include <Servo.h>
Servo picior;
void setup() {
  // put your setup code here, to run once:
    picior.attach(3);
    picior.write(90);
}

void loop() {
  // put your main code here, to run repeatedly:
    delay(1000);
  picior.write(90);
  delay(1000);
  picior.write(140);
}
