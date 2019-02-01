#include <PS2X_lib.h>
#include <ArduinoJson.h>

const size_t capacity = /*2*JSON_ARRAY_SIZE(2) + */JSON_OBJECT_SIZE(20);
DynamicJsonDocument doc(capacity);

/********for ps2************************/
PS2X ps2x; // create PS2 Controller Class
int error = 0; 

void setup() {
  Serial.begin(115200);
  delay(50);
  // put your setup code here, to run once:
  error = ps2x.config_gamepad(13,11,10,12, true, true);   //setup pins and settings:  GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
   if(error == 0){
     Serial.println("Found Controller, configured successful");
     Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
     Serial.println("holding L1 or R1 will print out the analog stick values.");
     Serial.println("Go to www.billporter.info for updates and to report bugs.");
   }
  
  else if(error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
  
  else if(error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");
  
  else if(error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");


}

void loop() {
  // put your main code here, to run repeatedly:

 if(error == 1) //skip loop if no controller found
  return; 

      
  JsonObject root = doc.to<JsonObject>();
  root["up"] = false;
  root["down"] = false;
  root["right"] = false;
  root["left"] = false;
  root["green"] = false;
  root["red"] = false;
  root["pink"] = false;
  root["blue"] = false;
  root["l1"] = false;
  root["l2"] = false;
  root["l3"]=false;
  root["r1"] = false;
  root["r2"] = false;
  root["r3"]=false;
  root["leftstick_X"]=128;
  root["leftstick_Y"]=128;
  root["rightstick_X"]=128;
  root["rightstick_Y"]=128;
 /* JsonArray leftstick = root.createNestedArray("leftstick");
  leftstick.add(48.75608);
  leftstick.add(2.302038);
  
  JsonArray rightstick = root.createNestedArray("rightstick");
  rightstick.add(12);
  rightstick.add(12);*/
  ps2x.read_gamepad(); 
  if(ps2x.Button(PSB_PAD_UP)) {         //will be TRUE as long as button is pressed
    /*Serial.print("Up held this hard: ");
    Serial.println(ps2x.Analog(PSAB_PAD_UP), DEC);*/
    root["up"] = true;
    }
  if(ps2x.Button(PSB_PAD_RIGHT)){
  Serial.print("Right held this hard: ");
  Serial.println(ps2x.Analog(PSAB_PAD_RIGHT), DEC);
   root["right"] = true;
  }
  if(ps2x.Button(PSB_PAD_LEFT)){
  /*Serial.print("LEFT held this hard: ");
  Serial.println(ps2x.Analog(PSAB_PAD_LEFT), DEC);*/
  root["left"] = true;
  }
  if(ps2x.Button(PSB_PAD_DOWN)){
  /*Serial.print("DOWN held this hard: ");
  Serial.println(ps2x.Analog(PSAB_PAD_DOWN), DEC);*/
  root["down"] = true;
  }   
  if(ps2x.Button(PSB_L3))
  root["l3"] = true;
  if(ps2x.Button(PSB_R3))
  root["r3"] = true;
  if(ps2x.Button(PSB_L2))
 root["l2"] = true;
  if(ps2x.Button(PSB_R2))
  root["r2"] = true;
  if(ps2x.Button(PSB_L1))
  root["l1"] = true;
  if(ps2x.Button(PSB_R1))
  root["r1"] = true;
  if(ps2x.Button(PSB_GREEN))
  root["green"] = true;
  if(ps2x.Button(PSB_PINK))
  root["pink"] = true;
  if(ps2x.Button(PSB_RED))
  root["red"] = true;
  if(ps2x.Button(PSB_BLUE))
  root["blue"] = true;
  root["leftstick_X"]=ps2x.Analog(PSS_LX);
  root["leftstick_Y"]=ps2x.Analog(PSS_LY);
  root["rightstick_X"]=ps2x.Analog(PSS_RX);
  root["rightstick_Y"]=ps2x.Analog(PSS_RY);
    
serializeJson(doc, Serial);
Serial.println("");
}
