#include <EasyEEPROM.h>
#include <EEPCircularBuffer.h>
#include <SimpleTask.h>

EasyEEPROM eeprom; //Create instance

#define DATA_ADDR 1
#define ANALOG_PIN  A0

#if defined(__STM32F1__)
#define ADC_BIT   12
#else 
#define ADC_BIT   10
#endif

struct ADCRecord{
  uint32_t timestamp; 
  float adcValue;
};

EEPCircularBuffer<ADCRecord> cb(0x10,200);//0x10:Start EEPROM Address, 200 : Number of maximum records
void readAdc();
void readCommand();
const int adc_max = (1<<ADC_BIT)-1;
const float Vref = 3.3;

void setup(){
  Serial.begin(115200);
  Wire.begin();
  eeprom.begin();
  cb.format();
  
#if defined(__STM32F1__)
  pinMode(ANALOG_PIN,INPUT_ANALOG);
#endif

  Task.create(readAdc,1000);
  Task.create(readCommand,10);
}

void loop() {  
  Task.loop();
}

void readAdc(){
  struct ADCRecord rec = {millis()/1000,Vref*(float)analogRead(ANALOG_PIN)/adc_max};
 cb.insert(rec);
}

void readCommand(){
  if(Serial.available() && Serial.read()=='r'){  
    while(!cb.isEmpty()){
      struct ADCRecord rec = cb.getFirst();      
      cb.moveStart();
      Serial.print("timestamp:");
      Serial.print(rec.timestamp);
      Serial.print("\t\tADC:");
      Serial.println(rec.adcValue,2);
    }    
    Serial.println("-------------------------------------------");    
    Serial.flush();
  }  
}