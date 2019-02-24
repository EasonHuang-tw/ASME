#include <PS2X_lib.h>


/********for ps2************************/
PS2X ps2x; // create PS2 Controller Class
int error = 0; 

String Data="";
int datacounter =0;
  
void setup() {
  Serial.begin(57600);
  delay(50);
  error = ps2x.config_gamepad(13,11,10,12, true, true); //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
  // put your setup code here, to run once:
  while(error!=0){   
   if(error == 0){
     Serial.println("Found Controller, configured successful");
   }
  
  else if(error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
  
  else if(error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
  
  else if(error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
  error = ps2x.config_gamepad(13,11,10,12, true, true);
  }
}
void loop() {
  ps2x.read_gamepad(); 
  if(ps2x.Button(PSB_PAD_UP))       
  Data=Data+"W";
  if(ps2x.Button(PSB_PAD_RIGHT))   
  Data=Data+"D";
  if(ps2x.Button(PSB_PAD_LEFT))  
  Data=Data+"A";
  if(ps2x.Button(PSB_PAD_DOWN)) 
  Data=Data+"S";
  if(ps2x.Button(PSB_R1))
  Data=Data+"R";
  if(ps2x.Button(PSB_R2))
  Data=Data+"T";
  if(ps2x.Button(PSB_R3))    
  Data=Data+"K";
  if(ps2x.Button(PSB_L1))
  Data=Data+"L";
  if(ps2x.Button(PSB_L2))
  Data=Data+"M";
  if(ps2x.Button(PSB_L3))     
  Data=Data+"N";
  if(ps2x.Button(PSB_GREEN))
  Data=Data+"G";
  if(ps2x.Button(PSB_PINK))
  Data=Data+"P";
  if(ps2x.Button(PSB_RED))
  Data=Data+"C";
  if(ps2x.Button(PSB_BLUE))
  Data=Data+"B";
  char str[60];
  Data=Data+"lx"+(int)ps2x.Analog(PSS_LX);
  Data=Data+"ly"+(int)ps2x.Analog(PSS_LY);
  Data=Data+"rx"+(int)ps2x.Analog(PSS_RX);
  Data=Data+"ry"+(int)ps2x.Analog(PSS_RY);
  Serial.println(Data);
delay(150);
Data="";
}
