/*
IMPORTANT NOTES

at end of the line there are 2 caracters CR, LF (13, 10)

end document with e
*/



#include <SPI.h>
#include <SD.h>
#include <List.hpp>

File myFile;
char x;
struct instruction{
  char mode;
  int value;//in mm or degrees
};
List<instruction> instruct;

void setup() {
  Serial.begin(9600);
  SD.begin(10);
  myFile = SD.open("steps.txt", FILE_READ);
  if(myFile.available()){
    instruction aux;
    int a=0;
    bool neg=false;
    x=myFile.read();
    while(x!='e'){
      if(x!=13){
        aux.mode = x;
        a=0;
        x=myFile.read();
        if(x=='-'){
          neg = true;
          x=myFile.read();
        }
        while(x!=13){
          a=a*10+(x-'0');
          x=myFile.read();
        }
        if(neg == true){
          a=-a;
          neg = false;
        }
        aux.value = a;
      }else{
        instruct.add(aux);
        aux.mode = 0;
        aux.value=0;
        myFile.read();
        x=myFile.read();
      }
    }
  }
  myFile.close();


  for(int i=0;i<instruct.getSize();i++){
    Serial.print(instruct[i].mode);
    Serial.print(instruct[i].value);
    Serial.println();
  }
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
 
}
