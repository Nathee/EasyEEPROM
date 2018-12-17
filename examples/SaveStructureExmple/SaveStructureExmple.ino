#include <EasyEEPROM.h>
EasyEEPROM eeprom;

#define DATA_ADDR 0

struct AppSetting{
    int vInt;
    float vFloat;
    char vString[50];
};

int c = 0;
void setup(){
  Serial.begin(115200);
  Wire.begin();
  eeprom.begin();
  while(!Serial)delay(1);//Waiting for serial monitor connected.
  
  struct AppSetting s1 = {1234,2345.67,"Test save structure to eeprom\0"};
  eeprom.write(DATA_ADDR,&s1,sizeof(AppSetting));

  struct AppSetting s2;
  eeprom.read(DATA_ADDR,&s2,sizeof(AppSetting));

  Serial.println("Read cnfig data from EEPROM");
  Serial.print("vInt = ");
  Serial.println(s1.vInt);
  Serial.print("vFloat = ");
  Serial.println(s1.vFloat);
  Serial.print("vString = ");
  Serial.println(s1.vString);
}

void loop() {  
}