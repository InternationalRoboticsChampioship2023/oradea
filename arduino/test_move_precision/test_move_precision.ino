#define output2A 2//interupt pin
#define output2B A0
#define M2speed 6
#define M2a 8
#define M2b 9

float transform = 3.33333333; //counter is 54 at 180 degrees rotation
float counter = 0;  
int motor_speed = 70; 
int angle;
float motor_angle;

void setup() {
  
  // put your setup code here, to run once:
  pinMode (output2A,INPUT);
  pinMode (output2B,INPUT);
  pinMode (M2speed,OUTPUT);
  pinMode (M2a,OUTPUT);
  pinMode (M2b,OUTPUT);
  Serial.begin (9600);
  attachInterrupt(digitalPinToInterrupt(output2A),Encoder2,RISING); 
}



void loop() {
  motor_angle= (int)(counter*transform);
  Serial.println(motor_angle);
  angle = 180;
  // put your main code here, to run repeatedly:
  if(motor_angle<angle){
    digitalWrite(M2a, HIGH);
    digitalWrite(M2b, LOW);
    analogWrite (M2speed, motor_speed);
  }else if(motor_angle>angle){
    digitalWrite(M2a, LOW);
    digitalWrite(M2b, HIGH);
    analogWrite (M2speed, motor_speed);
  }else{
    digitalWrite(M2a, LOW);
    digitalWrite(M2b, LOW);
    analogWrite (M2speed, motor_speed);     
  }
}


void Encoder2(){
  int b = digitalRead(output2B);
  if(b > 0){
    counter++;
  }
  else{
    counter--;
  }
}
