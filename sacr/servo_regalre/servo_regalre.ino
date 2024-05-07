#include <Servo.h>

Servo myservo;  // create servo object to control a servo

void setup() {
  myservo.attach(3) ;  // attaches the servo on pin 9 to the servo object
}

void loop() {
  //110 - perpendicular base
  // 0 tray mid servo
  //90 upright
  //180 - grip
  //70 grip base
  myservo.write(110);                  // sets the servo position according to the scaled value
  delay(1000); 
  myservo.write(75);                  // sets the servo position according to the scaled value
  delay(1000);// waits for the servo to get there
  //myservo.write(0);                  // sets the servo position according to the scaled value
  //delay(1000);// waits for the servo to get there
}
