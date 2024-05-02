#include <Servo.h>

byte servoPin1 = 6;
byte servoPin2 = 5;
Servo servo1;
Servo servo2;

void setup() {
  
 Serial.begin(9600);
 servo1.attach(servoPin1);
 servo2.attach(servoPin2);

 servo1.writeMicroseconds(2000); // send "stop" signal to ESC.
 servo2.writeMicroseconds(2000);
 delay(7000); // delay to allow the ESC to recognize the stopped signal
 servo1.writeMicroseconds(1000); // send "stop" signal to ESC.
 servo2.writeMicroseconds(1000);
}

void loop() {
}
