#define s_left_pin A3
#define s_front_pin A6
#define s_right_pin A7

void setup() {
  // put your setup code here, to run once:
  pinMode(s_left_pin, INPUT);
  pinMode(s_front_pin, INPUT);
  pinMode(s_right_pin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(analogRead(s_left_pin));
  Serial.print("  ");
  Serial.print(analogRead(s_front_pin));
  Serial.print("  ");
  Serial.print(analogRead(s_right_pin));
  Serial.println();
}
