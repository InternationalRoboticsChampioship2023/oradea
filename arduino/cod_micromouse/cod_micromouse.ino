const int MPU_addr=0x68;
double elapsedTime=0, currentTime=0, previousTime=0;
int desired_angle=0, agl = 0;

#define MSV 5
#define MS1 4
#define MS2 A2
#define MDV 6
#define MD1 8
#define MD2 7
int m_speed = 100;

void setup() {
  // put your setup code here, to run once:
  corrections_begin(MPU_addr);
  pinMode(MSV, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(MDV, OUTPUT);
  pinMode(MD1, OUTPUT);
  pinMode(MD2, OUTPUT);
  Serial.begin(9600);
}

void motors(int m1_dir, int m1_speed, int m2_dir, int m2_speed){ // dir=1=> high
  analogWrite(MSV, m1_speed);
  digitalWrite(MS1, m1_dir);
  digitalWrite(MS2, abs(m1_dir-1));
  analogWrite(MDV, m2_speed);
  digitalWrite(MD1, m2_dir);
  digitalWrite(MD2, abs(m2_dir-1));
}


void loop() {
  // put your main code here, to run repeatedly:
  previousTime = currentTime;      
  currentTime = millis();
  elapsedTime = (currentTime - previousTime) / 1000;
  agl = get_angle(elapsedTime);
  if(agl>desired_angle){
    motors(1, m_speed, 0, m_speed);
  }else if(agl<desired_angle){
    motors(0, m_speed, 1, m_speed);
  }else{
    motors(0, 0, 0, 0);
  }
  Serial.println(agl);
}
