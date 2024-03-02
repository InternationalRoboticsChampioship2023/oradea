/*
IMPORTANT NOTES

at end of the line there are 2 caracters CR, LF (13, 10)

end document with blank line (last line to have te 2 caracters mentioned above)
*/



#include <SPI.h>
#include <SD.h>

File myFile;
char x, prevx;
bool mode_sel=false;
int a=0;
void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  SD.begin(10);
  myFile = SD.open("test.txt", FILE_READ);
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
  if(myFile.available()){
    x=myFile.read();
    if(x=='_'){
      Serial.print(prevx);
      Serial.print("mode");
      mode_sel=true;
      a=0;
    }else if(int(x)==13){
      mode_sel=false;
      myFile.read();
      Serial.print(a);
        Serial.println("value");
    }else{
      if(mode_sel == true){
        a =a*10+((int)x-48);
      }
    }
    prevx=x;
  }
  
}
