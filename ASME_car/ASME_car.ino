#include <math.h> 
#include"pinDefine.h"
struct joystick pro;
void readdata(joystick *pro);
//**********************************************************
void motorstop();
void motorrun(int,int,int); //type ,power ,yaw
void motorspin(int);
void reel( bool , bool , int );  // flag_up, flag_down ,pin   
float Polar_Angle(float,float);   //y,x
float Polar_Length(float,float);
byte vibrate = 0;
void setup(){
 
  Serial.begin(57600);
  Serial3.begin(57600);
   //*********************PIN MODE*************************
      
    for (int i = 0; i<3;i++) pinMode(motor_LF[i], OUTPUT);
    for (int i = 0; i<3;i++) pinMode(motor_LB[i], OUTPUT);
    for (int i = 0; i<3;i++) pinMode(motor_RF[i], OUTPUT);
    for (int i = 0; i<3;i++) pinMode(motor_RB[i], OUTPUT);
    motorstop();
}

void loop() {
  
  bool motorstate=0;
  readdata(&pro);
  float left_joystick_angle=0;
  float left_joystick_length=0;
  int ly = pro.Ly;
  int lx = pro.Lx;
  int rx=  pro.Rx;
  
  if(pro.L1){
    Serial.println("L1 is pressed");
    Serial.print("lx:");
     Serial.print(pro.Lx);
     Serial.print("ly:");
     Serial.print(pro.Ly);
     Serial.print("rx:");
     Serial.print(pro.Rx);
     Serial.print("ry:");
     Serial.println(pro.Ry);
    left_reel_flag = true;
    pro.L1=false;
    }
    else  left_reel_flag = false;
  if(pro.L2){
    //Serial.println("L2 is pressed");
    pro.L2=false;
  }
  if(pro.L3){
    Serial.println("L3 is pressed");
    pro.L3=false;
    }
  if(pro.R1){
    //Serial.println("R1 is pressed");
    pro.R1=false;
  }if(pro.R2){
    //Serial.println("R2 is pressed");
    pro.R2=false;
    }
  if(pro.R3){
    //Serial.println("R3 is pressed");
    pro.R3=false;
  }if(pro.circle){
    //Serial.println("circle is pressed");
    pro.circle=false;
    }
  if(pro.rectangle){
    //Serial.println("rectangle is pressed");
    pro.rectangle=false;
  }if(pro.cross){
    //Serial.println("cross is pressed");
    pro.cross=false;
    }
  if(pro.triangle){
    //Serial.println("triangle is pressed");
    pro.triangle=false;
  }
  if(pro.up){
    //Serial.println("up is pressed");
    pro.up=false;
  }
  if(pro.right){
    //Serial.println("right is pressed");
    pro.right=false;
  }
  if(pro.down){
    //Serial.println("down is pressed");
    pro.down=false;
  }
  if(pro.left){
    //Serial.println("left is pressed");
    pro.left=false;
  }
  
  lx=(float)map(lx,0,255,-200,200);
  ly=(float)map(ly,0,255,200,-200);
  rx=(float)map(rx,0,255,-200,200);
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
      if(left_joystick_angle<22.5||left_joystick_angle>=337.5){
        motorrun(0,left_joystick_length<200?left_joystick_length:200,rx); //go right
        Serial.println("go right");
      }
      else if(left_joystick_angle>=67.5&&left_joystick_angle<112.5){
        motorrun(1,left_joystick_length<200?left_joystick_length:200,rx); //go straight
        Serial.println("go straight");
      }
      else if(left_joystick_angle>=157.5&&left_joystick_angle<202.5){
        motorrun(2,left_joystick_length<200?left_joystick_length:200,rx); //go left
        Serial.println("go left");
      }
      else if(left_joystick_angle>=247.5&&left_joystick_angle<292.5){
        motorrun(3,left_joystick_length<200?left_joystick_length:200,rx); //go back
        
      }
      else if(left_joystick_angle>=22.5&&left_joystick_angle<67.5)
        motorrun(4,left_joystick_length<200?left_joystick_length:200,rx); //go rightfront
      else if(left_joystick_angle>=112.5&&left_joystick_angle<157.5)
        motorrun(5,left_joystick_length<200?left_joystick_length:200,rx); //go leftfront
      else if(left_joystick_angle>=202.5&&left_joystick_angle<247.5)
        motorrun(6,left_joystick_length<200?left_joystick_length:200,rx); //go leftback
      else if(left_joystick_angle>=292.5&&left_joystick_angle<337.5)
        motorrun(7,left_joystick_length<200?left_joystick_length:200,rx); //go rightback
  }
  
}
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



