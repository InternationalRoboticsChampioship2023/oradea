// Basic demo for accelerometer readings from Adafruit MPU6050

// Arduino Guide: https://RandomNerdTutorials.com/arduino-mpu-6050-accelerometer-gyroscope/

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;
float yaw=0;
int angle;
float elapsedTime, currentTime, previousTime;
sensors_event_t a, g, temp; 
int rotate_speed = 70;
int stop_speed = -20;
float error;
float desired_angle=45;

const float RTD = 57.2957795;

int ms1=4;
int ms2=13;
int md1=16;
int md2=17;

const int freq = 1000;
const int ms1Channel = 0;
const int ms2Channel = 1;
const int md1Channel = 2;
const int md2Channel = 3;
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
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  mpu.setFilterBandwidth(MPU6050_BAND_260_HZ);
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
  error = get_error();
}

void loop() {
  angle = get_angle();
  Serial.print(angle);
  Serial.println("");
  if(angle>desired_angle){
    motors(-rotate_speed, rotate_speed);
  }else if(angle<desired_angle){
    motors(rotate_speed, -rotate_speed);
  }else{
    motors(stop_speed, stop_speed);
  }
}

int get_angle(){
  previousTime = currentTime;        // Previous time is stored before the actual time read
  currentTime = millis();            // Current time actual time read
  elapsedTime = (currentTime - previousTime) / 1000; // Divide by 1000 to get seconds
  /* Get new sensor events with the readings */
  
  mpu.getEvent(&a, &g, &temp);
  yaw =  yaw + (g.gyro.z-error) *elapsedTime ;
  return -(yaw)*RTD;
  //delay(1);
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

float get_error(){
  float sum = 0.00000001;
  mpu.getEvent(&a, &g, &temp);
  for(int i = 0;i<4000;i++){
    sum = sum+g.gyro.z;
    Serial.println(sum);
  }
  sum /=4000;
  return sum;
}
