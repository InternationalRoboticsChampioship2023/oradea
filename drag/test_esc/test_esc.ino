#include <Servo.h>

byte servoPin1 = 6;
byte servoPin2 = 5;
Servo servo1;
Servo servo2;

void setup() {
  
 Serial.begin(9600);
 servo1.attach(servoPin1);
 servo2.attach(servoPin2);

 servo1.writeMicroseconds(1000); // send "stop" signal to ESC.
 servo2.writeMicroseconds(1000);
 delay(7000); // delay to allow the ESC to recognize the stopped signal
 servo1.writeMicroseconds(1100); // Send signal to ESC.
    servo2.writeMicroseconds(1100);
    delay(500);
  servo1.writeMicroseconds(1000); // Send signal to ESC.
    servo2.writeMicroseconds(1000);
}

void loop() {
  /*
  Serial.println("Enter PWM signal value 1100 to 1900, 1500 to stop");
  
  while (Serial.available() == 0);
  
  int val = Serial.parseInt(); 
  
  if(val < 1000 || val > 1900)
  {
    Serial.println("not valid");
  }
  else
  {
    Serial.println(val);
    servo1.writeMicroseconds(val); // Send signal to ESC.
    servo2.writeMicroseconds(val);
  }
  */
}
