#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

const float RTD = 57.2957795;

Adafruit_MPU6050 mpu;
float angle=0;
float elapsedTime, currentTime, previousTime;
sensors_event_t a, g, temp; 
int rotate_speed = 70;
int stop_speed = -20;
float error=0;

int ms1=4;
int ms2=13;
int md1=16;
int md2=17;
#define EncoderS 34 
#define EncoderD 36
int Count_pulsesS = 0;
int Count_pulsesD = 0;
int avg;
int pls;
float diam = 91.1061, val=0;
int vs, vd;

const int freq = 1000;
const int ms1Channel = 0;
const int ms2Channel = 1;
const int md1Channel = 2;
const int md2Channel = 3;
const int resolution = 8;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  mpu.begin();
  mpu.setGyroRange(MPU6050_RANGE_1000_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_260_HZ);
  get_error();
  pinMode(ms1, OUTPUT);
  pinMode(ms2, OUTPUT);
  pinMode(md1, OUTPUT);
  pinMode(md2, OUTPUT);
  digitalWrite(ms1, LOW);
  digitalWrite(ms2, LOW);
  digitalWrite(md1, LOW);
  digitalWrite(md2, LOW);
  ledcSetup(ms1Channel, freq, resolution);
  ledcSetup(ms2Channel, freq, resolution);
  ledcSetup(md1Channel, freq, resolution);
  ledcSetup(md2Channel, freq, resolution);
  ledcAttachPin(ms1, ms1Channel);
  ledcAttachPin(ms2, ms2Channel);
  ledcAttachPin(md1, md1Channel);
  ledcAttachPin(md2, md2Channel);
  attachInterrupt(digitalPinToInterrupt(EncoderS),DC_MotorS,RISING);
  attachInterrupt(digitalPinToInterrupt(EncoderD),DC_MotorD,RISING);
}

void loop() {
  // put your main code here, to run repeatedly:
  /*
  Serial.print(Count_pulsesS);
  Serial.print(",");
  Serial.print(Count_pulsesD);
  Serial.print(",");
  Serial.print(angle);
  Serial.println("");
  */
  val = 91;
  pls = (val*110)/diam;
  vs =0;
  vd=0;
  if(avg<pls){
    vs += 70;
    vd += 70;
  }else if(avg>pls){
    vs-=70;
    vd-=70;
  }
  correction();
  motors(vs, vd);
}

void correction(){
  get_angle(angle);
  if(angle>0){
    vs -=30;
  }else if(angle<0){
    vd-=30;
  }
}

void get_angle(float& yaw){
  previousTime = currentTime;        // Previous time is stored before the actual time read
  currentTime = millis();            // Current time actual time read
  elapsedTime = (currentTime - previousTime) / 1000; // Divide by 1000 to get seconds
  /* Get new sensor events with the readings */
  Serial.print(g.gyro.z);
  Serial.print(" ");
  Serial.println(angle);
  mpu.getEvent(&a, &g, &temp);
  yaw -= (g.gyro.z-error) *elapsedTime*RTD ;
}

void motors(int vst, int vdr){
  if(vst >= 0){
    ledcWrite(ms2Channel, vst);
    ledcWrite(ms1Channel, 0);
  }else{
    ledcWrite(ms2Channel, 0);
    ledcWrite(ms1Channel, abs(vst));
  }
  if(vdr >= 0){
    ledcWrite(md2Channel, vdr);
    ledcWrite(md1Channel, 0);
  }else{
    ledcWrite(md2Channel, 0);
    ledcWrite(md1Channel, abs(vdr));
  }
}

void get_error(){
  mpu.getEvent(&a, &g, &temp);
  for(int i = 0;i<2000;i++){
    error +=g.gyro.z;
  }
  error /=2000;
}

void DC_MotorS(){
  int ES = 35;
  pinMode(ES, INPUT);
  if(digitalRead(ES)==HIGH){
    Count_pulsesS--; 
  }else{
    Count_pulsesS++; 
  }
  avg = (Count_pulsesS + Count_pulsesD)/2;
}
void DC_MotorD(){
  int ED = 39;
  pinMode(ED, INPUT);
  if(digitalRead(ED)==HIGH){
    Count_pulsesD++; 
  }else{
    Count_pulsesD--;
  }
  avg = (Count_pulsesS + Count_pulsesD)/2;
}
