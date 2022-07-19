#include "Wire.h"
#include "MCP4725.h"
#define STEP_PULSE "STEP"
bool stepflag=false;
float voltageIn ;
int adcInput = 0;
float MCP4725_reading;
bool dac_high=false;
char inputString[50];         // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete
int i=0;
byte index=0;
float on_time=0;
float num_pulse=3;
float num_cycles=0;
float dac_input=0;
float step_voltage=0;
char *strings[3]; 
unsigned long  prev_time=0;
unsigned long  curr_time=0;
unsigned long  time_diff=0;
MCP4725 MCP(0x60);  
/*void step_pulse()
{
  float volt=0;
  Serial.println("stepping");
   curr_time=millis();
   prev_time=curr_time-on_time;
   while(stepflag)
   {
     while(volt<5)
     {
      volt++;
      MCP.setValue(volt);
      adcInput = analogRead(0); //module output connect to A0
      voltageIn = (adcInput * 5 )/ 1024.0; 
     Serial.println("voltageIn");
    // Serial.println(voltageIn);
     }
    MCP.setValue(0); 
    adcInput = analogRead(0); //module output connect to A0
    voltageIn = (adcInput * 5 )/ 1024.0; 

   // Serial.println(voltageIn);
    stepflag=false;
   }
   
}*/
void setup() {
  // initialize serial:
  Serial.begin(9600);
   MCP.begin();
  // reserve 200 bytes for the inputString:
  //inputString.reserve(200);
}

void loop() {
  unsigned long  curr_time=millis();
  MCP.setValue(0);
  // print the string when a newline arrives:
  if (stringComplete) {
    i=0;
    //Serial.println(inputString);
    // clear the string:
     char*  token = strtok(inputString," ");
      while( token != NULL ) {
      //Serial.println( token ); //printing each token
      strings[index]=token;
      //Serial.println(strings[index]);
      index++;
      token = strtok(NULL, " ");
      //inputString = "";
      //memset(inputString,0,10);
     stringComplete = false;
  }
  //Serial.println(strings[0]);
//if(strcmp(STEP_PULSE,strings[0])){on_time=atof(strings[1]);step_voltage=atof(strings[2]);stepflag=true;step_pulse();}

on_time=atof(strings[1]);
num_cycles=atof(strings[2]);
dac_input=atof(strings[0]);
MCP.setValue(dac_input);
//Serial.println(on_time);
//Serial.println(num_pulse);
//Serial.println(dac_input);
memset(inputString,0,50);
   //index=0;
}
   curr_time=millis();
   prev_time=curr_time-on_time;
  while(num_cycles>0){
    num_pulse=3;
  while(num_pulse>0){
    curr_time=millis();
  if((curr_time-prev_time)>=on_time)
     {
      time_diff=curr_time-prev_time;
      
       prev_time=curr_time;
        //Serial.println(num_pulse);
      num_pulse--;
      //Serial.println(num_pulse);
      if(!dac_high){
      MCP.setValue(0);dac_high=true;
                   }
      else {MCP.setValue(dac_input);dac_high=false;}
     }
    // curr_time=millis();
     
adcInput = analogRead(0); //module output connect to A0
voltageIn = (adcInput * 5 )/ 1024.0; 
//delay(1000);
Serial.println(voltageIn);
}
num_cycles--;
dac_high=false;
  }


dac_high=false;
index=0;
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = char(Serial.read());
    //add it to the inputString:
    //Serial.println(inChar);
    inputString[i] = inChar;
   /// Serial.println(inputString);
     i++;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      //Serial.println("donr");
       //Serial.println(inputString);
      stringComplete = true;
    }
    //i++;
  }
  //Serial.println(inputString);
  //i=0;
}
