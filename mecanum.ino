#include <math.h> 
#define PI 3.14159265

#define PS2_DAT        53  //14
#define PS2_CMD        51  //15
#define PS2_SEL        49  //16
#define PS2_CLK        47  //17

//**************************(motor)*****************************

const int motor_LF[3]={40, 41, 7};  //(motor left  front) IN1 IN2 ENA 
const int motor_LB[3]={39, 38, 6};  //(motor left  back)  IN1 IN2 ENA 
const int motor_RF[3]={37, 36, 5};  //(motor right front) IN1 IN2 ENA 
const int motor_RB[3]={34, 35, 4};  //(motor right back)  IN1 IN2 ENA  


//****************************************************************

#include <PS2X_lib.h>  
PS2X ps2x; 
void motorstop();
void motorrun(int,int,int); //type ,power ,yaw
void motorspin(int);
float Polar_Angle(float,float);   //y,x
float Polar_Length(float,float);
int error = 0;
byte type = 0;
byte vibrate = 0;

void setup(){
 
  Serial.begin(38400);
  
  delay(300);  //added delay to give wireless ps2 module some time to startup, before configuring it
  error = ps2x.config_gamepad(true, true);
  
  if(error == 0){
    Serial.print("Found Controller, configured successful ");
  }  
  else if(error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   
  else if(error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if(error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
  type = ps2x.readType(); 
  switch(type) {
    case 0:
      Serial.print("Unknown Controller type found ");
      break;
    case 1:
      Serial.print("DualShock Controller found ");
      break;
    case 2:
      Serial.print("GuitarHero Controller found ");
      break;
	case 3:
      Serial.print("Wireless Sony DualShock Controller found ");
      break;
   }
   //*********************PIN MODE*************************
      
    for (int i = 0; i<3;i++) pinMode(motor_LF[i], OUTPUT);
    for (int i = 0; i<3;i++) pinMode(motor_LB[i], OUTPUT);
    for (int i = 0; i<3;i++) pinMode(motor_RF[i], OUTPUT);
    for (int i = 0; i<3;i++) pinMode(motor_RB[i], OUTPUT);
    motorstop();
}

void loop() {
  bool motorstate=0;
  float left_joystick_angle=0;
  float left_joystick_length=0;
  ps2x.read_gamepad();          //read controller 
  int ly = (int)ps2x.Analog(PSS_LY);
  int lx = (int)ps2x.Analog(PSS_LX);
  int rx=  (int)ps2x.Analog(PSS_RX);
  
  
  lx=(float)map(lx,0,255,-200,200);
  ly=(float)map(ly,0,255,200,-200);
  rx=(float)map(rx,0,255,-200,200);
  Serial.println(rx);
  lx==0?lx=1:1;
  ly==0?ly=1:1;
  rx==1?rx=0:1;
  if(lx==1&&ly==1)
    motorstate=0;
  else{
    motorstate=1;
    left_joystick_angle=Polar_Angle(static_cast<float>(lx),static_cast<float>(ly));
    left_joystick_length=Polar_Length(static_cast<float>(lx),static_cast<float>(ly));
    /*Serial.print("angle:");
    Serial.println(left_joystick_angle);
    Serial.print("Length:");
    Serial.println(left_joystick_length);*/
  }
  if(motorstate==0)  
    motorspin(rx);
  else{
      rx=map(rx,-200,200,-25,25);
      if(left_joystick_angle<22.5||left_joystick_angle>=337.5)
        motorrun(0,left_joystick_length<200?left_joystick_length:200,rx); //go right
      else if(left_joystick_angle>=67.5&&left_joystick_angle<112.5)
        motorrun(1,left_joystick_length<200?left_joystick_length:200,rx); //go straight
      else if(left_joystick_angle>=157.5&&left_joystick_angle<202.5)
        motorrun(2,left_joystick_length<200?left_joystick_length:200,rx); //go left
      else if(left_joystick_angle>=247.5&&left_joystick_angle<292.5)
        motorrun(3,left_joystick_length<200?left_joystick_length:200,rx); //go back
      else if(left_joystick_angle>=22.5&&left_joystick_angle<67.5)
        motorrun(4,left_joystick_length<200?left_joystick_length:200,rx); //go rightfront
      else if(left_joystick_angle>=112.5&&left_joystick_angle<157.5)
        motorrun(5,left_joystick_length<200?left_joystick_length:200,rx); //go leftfront
      else if(left_joystick_angle>=202.5&&left_joystick_angle<247.5)
        motorrun(6,left_joystick_length<200?left_joystick_length:200,rx); //go leftback
      else if(left_joystick_angle>=292.5&&left_joystick_angle<337.5)
        motorrun(7,left_joystick_length<200?left_joystick_length:200,rx); //go rightback
  }
  delay(50);  
}
void motorstop(){
  for(int i=0;i<2;i++)digitalWrite(motor_RF[i], 0);
  for(int i=0;i<2;i++)digitalWrite(motor_RB[i], 0);
  for(int i=0;i<2;i++)digitalWrite(motor_LF[i], 0);
  for(int i=0;i<2;i++)digitalWrite(motor_LB[i], 0);
};
float Polar_Angle(float x,float y){
   if(x>0&&y>0)
      return atan((float)y/(float)x)* 180 / PI;
    else if(x<0)
      return atan((float)y/(float)x)* 180 / PI+180;
    else 
      return atan((float)y/(float)x)* 180 / PI+360;
};
float Polar_Length(float x,float y){
  return sqrt(x*x+y*y);
};
void motorrun(int type,int power ,int yaw){
  switch(type){
  case 0:                                   //right
    analogWrite(motor_LB[2],power);
    analogWrite(motor_LF[2],power);
    analogWrite(motor_RF[2],power);
    analogWrite(motor_RB[2],power);
    digitalWrite(motor_RF[0], 0);
    digitalWrite(motor_RF[1], 1);
    digitalWrite(motor_RB[0], 1);
    digitalWrite(motor_RB[1], 0);
    digitalWrite(motor_LF[0], 1);
    digitalWrite(motor_LF[1], 0);
    digitalWrite(motor_LB[0], 0);
    digitalWrite(motor_LB[1], 1);
    break;
  case 1:                                 //front
    analogWrite(motor_LB[2],power);
    analogWrite(motor_LF[2],power);
    analogWrite(motor_RF[2],power);
    analogWrite(motor_RB[2],power);
    digitalWrite(motor_RF[0], 1);
    digitalWrite(motor_RF[1], 0);
    digitalWrite(motor_RB[0], 1);
    digitalWrite(motor_RB[1], 0);
    digitalWrite(motor_LF[0], 1);
    digitalWrite(motor_LF[1], 0);
    digitalWrite(motor_LB[0], 1);
    digitalWrite(motor_LB[1], 0);
    break;
  case 2:                                 //left
    analogWrite(motor_LB[2],power);
    analogWrite(motor_LF[2],power);
    analogWrite(motor_RF[2],power);
    analogWrite(motor_RB[2],power);
    digitalWrite(motor_RF[0], 1);
    digitalWrite(motor_RF[1], 0);
    digitalWrite(motor_RB[0], 0);
    digitalWrite(motor_RB[1], 1);
    digitalWrite(motor_LF[0], 0);
    digitalWrite(motor_LF[1], 1);
    digitalWrite(motor_LB[0], 1);
    digitalWrite(motor_LB[1], 0);
    break;
  case 3:                               //back
    analogWrite(motor_LB[2],power);
    analogWrite(motor_LF[2],power);
    analogWrite(motor_RF[2],power);
    analogWrite(motor_RB[2],power);
    digitalWrite(motor_RF[0], 0);
    digitalWrite(motor_RF[1], 1);
    digitalWrite(motor_RB[0], 0);
    digitalWrite(motor_RB[1], 1);
    digitalWrite(motor_LF[0], 0);
    digitalWrite(motor_LF[1], 1);
    digitalWrite(motor_LB[0], 0);
    digitalWrite(motor_LB[1], 1);
    break;
  case 4:                                 //rightfront
    digitalWrite(motor_RF[0], 0);
    digitalWrite(motor_RF[1], 1);
    digitalWrite(motor_RB[0], 1);
    digitalWrite(motor_RB[1], 0);
    digitalWrite(motor_LF[0], 1);
    digitalWrite(motor_LF[1], 0);
    digitalWrite(motor_LB[0], 0);
    digitalWrite(motor_LB[1], 1);
    analogWrite(motor_LB[2],20);
    analogWrite(motor_LF[2],power);
    analogWrite(motor_RF[2],20);
    analogWrite(motor_RB[2],power);
    break;
    case 5:                             //leftfront
    digitalWrite(motor_RF[0], 1);
    digitalWrite(motor_RF[1], 0);
    digitalWrite(motor_RB[0], 0);
    digitalWrite(motor_RB[1], 1);
    digitalWrite(motor_LF[0], 0);
    digitalWrite(motor_LF[1], 1);
    digitalWrite(motor_LB[0], 1);
    digitalWrite(motor_LB[1], 0);
    analogWrite(motor_LB[2],power);
    analogWrite(motor_LF[2],20);
    analogWrite(motor_RF[2],power);
    analogWrite(motor_RB[2],20);
    break;
    case 6:                           //leftback
     digitalWrite(motor_RF[0], 1);
    digitalWrite(motor_RF[1], 0);
    digitalWrite(motor_RB[0], 0);
    digitalWrite(motor_RB[1], 1);
    digitalWrite(motor_LF[0], 0);
    digitalWrite(motor_LF[1], 1);
    digitalWrite(motor_LB[0], 1);
    digitalWrite(motor_LB[1], 0);
    analogWrite(motor_LB[2],20);
    analogWrite(motor_LF[2],power);
    analogWrite(motor_RF[2],20);
    analogWrite(motor_RB[2],power);
    break;
    case 7:                         //rightback
    digitalWrite(motor_RF[0], 0);
    digitalWrite(motor_RF[1], 1);
    digitalWrite(motor_RB[0], 1);
    digitalWrite(motor_RB[1], 0);
    digitalWrite(motor_LF[0], 1);
    digitalWrite(motor_LF[1], 0);
    digitalWrite(motor_LB[0], 0);
    digitalWrite(motor_LB[1], 1);
    analogWrite(motor_LB[2],power);
    analogWrite(motor_LF[2],20);
    analogWrite(motor_RF[2],power);
    analogWrite(motor_RB[2],20);
    break;
    } 
}
void motorspin(int yaw){
  if(yaw==0)
    motorstop();
   else if(yaw>0){
    digitalWrite(motor_RF[0], 0);
    digitalWrite(motor_RF[1], 1);
    digitalWrite(motor_RB[0], 0);
    digitalWrite(motor_RB[1], 1);
    digitalWrite(motor_LF[0], 1);
    digitalWrite(motor_LF[1], 0);
    digitalWrite(motor_LB[0], 1);
    digitalWrite(motor_LB[1], 0);
    analogWrite(motor_LB[2],yaw);
    analogWrite(motor_LF[2],yaw);
    analogWrite(motor_RF[2],yaw);
    analogWrite(motor_RB[2],yaw);}
   else{
    yaw=-yaw;
    digitalWrite(motor_RF[0], 1);
    digitalWrite(motor_RF[1], 0);
    digitalWrite(motor_RB[0], 1);
    digitalWrite(motor_RB[1], 0);
    digitalWrite(motor_LF[0], 0);
    digitalWrite(motor_LF[1], 1);
    digitalWrite(motor_LB[0], 0);
    digitalWrite(motor_LB[1], 1);
    analogWrite(motor_LB[2],yaw);
    analogWrite(motor_LF[2],yaw);
    analogWrite(motor_RF[2],yaw);
    analogWrite(motor_RB[2],yaw);}
  }



