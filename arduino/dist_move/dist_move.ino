#include<Wire.h>
 
const int MPU_addr=0x68;
double GyZ, GyZError,z;
int angle,desired_angle=0;
float elapsedTime, currentTime, previousTime;

#define MSV 5
#define MS1 A2
#define MS2 4
#define MDV 6
#define MD1 8
#define MD2 7
int m_speed = 100;

#define EnSA 2 // pin2 of the Arduino
#define EnSB A0
#define EnDA 3 // pin2 of the Arduino
#define EnDB A1
int pulses=0,a;
double wheel_circ = 9.11, rev;
int pulsesRev;

void setup(){
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission(true);

  Wire.beginTransmission(MPU_addr);
  Wire.write(0x1B);                   // Talk to the GYRO_CONFIG register (1B hex)
  Wire.write(0x18);                   // Set the register bits as 00011000 (2000deg/s full scale)
  Wire.endTransmission(true);
  
  pinMode(MSV, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(MDV, OUTPUT);
  pinMode(MD1, OUTPUT);
  pinMode(MD2, OUTPUT);
  Serial.begin(9600);
  pinMode(EnSA,INPUT); // sets the Encoder_output_A pin as the input
  pinMode(EnSB,INPUT); // sets the Encoder_output_B pin as the input
  attachInterrupt(digitalPinToInterrupt(EnSA),MSEn,RISING);
  //calc_error();
  delay(1000);
  
}

void MSEn(){
  a = digitalRead(EnSB);
  if(a > 0){
    pulses++;
  }
  else{
    pulses--;
  }
}

void move_dist(double dist){//in cm
  rev = dist/wheel_circ;
  pulsesRev = int(rev*102);//102 pulses/rev for encoder
  if(pulsesRev > pulses){
    analogWrite(MSV, m_speed);
    digitalWrite(MS1, HIGH);
    digitalWrite(MS2, LOW);
    analogWrite(MDV, m_speed);
    digitalWrite(MD1, HIGH);
    digitalWrite(MD2, LOW);
  }else if(pulsesRev < pulses){
    analogWrite(MSV, m_speed);
    digitalWrite(MS1, LOW);
    digitalWrite(MS2, HIGH);
    analogWrite(MDV, m_speed);
    digitalWrite(MD1, LOW);
    digitalWrite(MD2, HIGH);
  }else{
    analogWrite(MSV, 0);
    digitalWrite(MS1, LOW);
    digitalWrite(MS2, HIGH);
    analogWrite(MDV, 0);
    digitalWrite(MD1, LOW);
    digitalWrite(MD2, HIGH);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  move_dist(10);
  Serial.print(pulsesRev);
  Serial.print(" ");
  Serial.print(pulses);
  Serial.println();
}
