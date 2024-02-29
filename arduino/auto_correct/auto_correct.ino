#include<Wire.h>

#define ES1 2
#define ES2 A0
#define ED1 3
#define ED2 A1
int posS = 0, posD=0;

#define MSV 5
#define MS1 4
#define MS2 A2
#define MDV 6
#define MD1 8
#define MD2 7
int m_speed = 100;
 
const int MPU_addr=0x68;
double angle_read, angle_double;
int angle;
float elapsedTime, currentTime, previousTime;


void setup() {
  pinMode(ES1,INPUT);
  pinMode(ES2,INPUT);
  //attachInterrupt(digitalPinToInterrupt(ES1),ES,RISING);
  pinMode(ED1,INPUT);
  pinMode(ED2,INPUT);
  //attachInterrupt(digitalPinToInterrupt(ED1),ED,RISING);

  pinMode(MSV, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(MDV, OUTPUT);
  pinMode(MD1, OUTPUT);
  pinMode(MD2, OUTPUT);
  
  Wire.begin();
  Wire.beginTransmission(MPU_addr);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission(true);
  Serial.begin(9600);
}

/*
void ES(){
  int b = digitalRead(ES2);
  if(b > 0){
    posS++;
  }
  else{
    posS--;
  }
}


void ED(){
  int b = digitalRead(ED2);
  if(b > 0){
    posD--;
  }
  else{
    posD++;
  }
}
*/

void correction(){
  if(angle>0){
    analogWrite(MSV, m_speed);
    digitalWrite(MS1, HIGH);
    digitalWrite(MS2, LOW);
    analogWrite(MDV, m_speed);
    digitalWrite(MD1, LOW);
    digitalWrite(MD2, HIGH);
  }else if(angle<0){
    analogWrite(MSV, m_speed);
    digitalWrite(MS1, LOW);
    digitalWrite(MS2, HIGH);
    analogWrite(MDV, m_speed);
    digitalWrite(MD1, HIGH);
    digitalWrite(MD2, LOW);
  }else{
    analogWrite(MSV, 0);
    digitalWrite(MS1, LOW);
    digitalWrite(MS2, LOW);
    analogWrite(MDV, 0);
    digitalWrite(MD1, LOW);
    digitalWrite(MD2, LOW);
  }
}

void loop() {
  previousTime = currentTime;      
  currentTime = millis();
  elapsedTime = (currentTime - previousTime) / 1000;

  Wire.beginTransmission(MPU_addr);
  Wire.write(0x47);
  Wire.endTransmission(false);
  Wire.requestFrom(MPU_addr,6,true);
  angle_read=(Wire.read()<<8|Wire.read())/131.0;
  angle_read = angle_read -1.67; //-1*rezult from calc_error()
  angle_double= angle_double + angle_read * elapsedTime;
  angle = (int)angle_double;
  correction();
  Serial.print(angle);
  Serial.print("  ");
  Serial.print(posS);
  Serial.print("  ");
  Serial.print(posD);
  Serial.println();
  
}
