#include <EasyEEPROM.h>
EasyEEPROM eeprom;

#define INIT_FLAG 0xAA
#define FLAG_ADDR 0
#define DATA_ADDR 1

int c = 0;
void setup(){
  Serial.begin(115200);
  Wire.begin();
  eeprom.begin();
  while(!Serial)delay(1);
  if(eeprom.read(FLAG_ADDR) != INIT_FLAG){
    c = 0;   
    eeprom.write(FLAG_ADDR,INIT_FLAG);
    eeprom.write(DATA_ADDR,&c,sizeof(int));  
  }else{
    eeprom.read(DATA_ADDR,&c,sizeof(int));  
  }
}

void loop() { 
  if(Serial.available() && Serial.read()=='c'){
     c=0;
     Serial.flush();
  }
  Serial.println(c++);  
  eeprom.write(DATA_ADDR,&c,sizeof(int));  
  delay(1000);  
}