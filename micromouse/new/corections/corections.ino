// Basic demo for accelerometer readings from Adafruit MPU6050

// Arduino Guide: https://RandomNerdTutorials.com/arduino-mpu-6050-accelerometer-gyroscope/

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;
float yaw=0, angle;
float elapsedTime, currentTime, previousTime;
int rotate_speed = 70;
int stop_speed = -20;

const float RTD = 57.2957795;

int ms1=15;
int ms2=2;
int md1=0;
int md2=4;

const int freq = 1000;
const int msChannel = 0;
const int mdChannel = 1;
const int resolution = 8;
void setup(void) {
  Serial.begin(115200);
  while (!Serial) {
    delay(10); // will pause Zero, Leonardo, etc until serial console opens
  }

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }

  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  pinMode(ms1, OUTPUT);
  pinMode(ms2, OUTPUT);
  pinMode(md1, OUTPUT);
  pinMode(md2, OUTPUT);
  ledcSetup(msChannel, freq, resolution);
  ledcSetup(mdChannel, freq, resolution);
}

void loop() {
  //angle = get_angle();
  angle = 100;
  Serial.print(angle);
  Serial.println("");
  if(angle>0){
    motors(-rotate_speed, rotate_speed);
  }else if(angle<0){
    motors(rotate_speed, -rotate_speed);
  }else{
    motors(stop_speed, stop_speed);
  }
}

float get_angle(){
  previousTime = currentTime;        // Previous time is stored before the actual time read
  currentTime = millis();            // Current time actual time read
  elapsedTime = (currentTime - previousTime) / 1000; // Divide by 1000 to get seconds
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp; 
  mpu.getEvent(&a, &g, &temp);
  yaw =  yaw - g.gyro.z *elapsedTime;
  return yaw*RTD;
}
void motors(int vst, int vdr){
  if(vst >= 0){
    ledcDetachPin(ms1);
    digitalWrite(ms1, LOW);
    ledcWrite(msChannel, vst);
    ledcAttachPin(ms2, msChannel);
  }else{
    ledcDetachPin(ms2);
    digitalWrite(ms2, LOW);
    ledcWrite(msChannel, abs(vst));
    ledcAttachPin(ms1, msChannel);
  }
  if(vdr >= 0){
    ledcDetachPin(md1);
    digitalWrite(md1, LOW);
    ledcWrite(mdChannel, vdr);
    ledcAttachPin(md2, mdChannel);
  }else{
    ledcDetachPin(md2);
    digitalWrite(md2, LOW);
    ledcWrite(mdChannel, abs(vdr));
    ledcAttachPin(md1, mdChannel);
  }
}
