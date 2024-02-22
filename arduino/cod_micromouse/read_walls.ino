int left_s_pin=0;
int front_s_pin=0;
int right_s_pin=0;
int trig_pin= 0;
int left_s=0;
int front_s=0;
int right_s=0;
int mode=0;//0- line_sensor, 1-distance sensor

void reading_begin(int trig, int x,int y, int z, int m){
  left_s_pin=x;
  front_s_pin=y;
  right_s_pin=z;
  mode = m;
  pinMode(trig_pin, OUTPUT);
  pinMode(left_s_pin, INPUT);
  pinMode(front_s_pin, INPUT);
  pinMode(right_s_pin, INPUT);
}

int read_walls(){
  if(mode == 1){
    // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
    // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
    digitalWrite(trig_pin, LOW);
    delayMicroseconds(5);
    digitalWrite(trig_pin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig_pin, LOW);

    left_s = pulseIn(left_s_pin, HIGH, 30);
    front_s = pulseIn(front_s_pin, HIGH, 30);
    right_s = pulseIn(right_s_pin, HIGH, 30);
  }else{
    left_s=digitalRead(left_s_pin);
    front_s=digitalRead(front_s_pin);
    right_s=digitalRead(right_s_pin);
  }
  int x = left_s*100;
  x=x+front_s*10;
  x=x+right_s;
  return x;
}
