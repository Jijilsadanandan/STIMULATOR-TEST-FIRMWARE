

#include "Wire.h"
#include "MCP4725.h"
float voltageIn ;
int adcInput = 0;
int time_delay=2;
float peak_voltage=0;
int pulse_time=100;
unsigned long curr_time=0;
unsigned long prev_time=0;
MCP4725 MCP(0x60);  // 0x62 or 0x63



void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
 MCP.begin();
}

void loop()
{
  prev_time=millis()-time_delay;
  while (peak_voltage<=1000)
  {
    curr_time=millis();
    if((curr_time-prev_time)>=time_delay){
    if(peak_voltage==1000)
    MCP.setValue(0);
    else
    MCP.setValue(peak_voltage);
    
    peak_voltage=peak_voltage+100;
   
    adcInput = analogRead(0); //module output connect to A0
    voltageIn = (adcInput * 5 )/ 1024.0; 
   //delay(1000);
    Serial.println(voltageIn);
    }
  }
 
}
