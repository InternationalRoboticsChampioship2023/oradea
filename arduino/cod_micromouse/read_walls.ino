int left_s_pin=0;
int front_s_pin=0;
int right_s_pin=0;
int left_s=0;
int front_s=0;
int right_s=0;
int mode=0;//0- line_sensor, 1-distance sensor

void reading_begin(int x,int y, int z, int m){
  left_s_pin=x;
  front_s_pin=y;
  right_s_pin=z;
  mode = m;
  pinMode(left_s_pin, INPUT);
  pinMode(front_s_pin, INPUT);
  pinMode(right_s_pin, INPUT);
}

int read_walls(){
  left_s=digitalRead(left_s_pin);
  front_s=digitalRead(front_s_pin);
  right_s=digitalRead(right_s_pin);
  int x = left_s*100;
  x=x+front_s*10;
  x=x+right_s;
  return x;
}
