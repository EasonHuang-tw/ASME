#include<Servo.h>
#include <math.h> 
#include"pinDefine.h"

Servo LSV;  //Left Servo
Servo RSV;  //Right Servo
Servo LBSV;
Servo RBSV;
int LSVA;  //angle
int RSVA;
int LBSVA;
int RBSVA;

struct joystick pro;
void readdata(joystick *pro);
void dataclear(joystick *pro);
//**********************************************************
void motorstop();
void motorrun(int,int,int); //type ,power ,yaw
void motorspin(int);
//**********************************************************

void flat_control(int);
int last_flat_flag =0;
int flat_flag=0;

//**********************************************************

float Polar_Angle(float,float);   //y,x
float Polar_Length(float,float);
byte vibrate = 0;


void setup(){
 
  Serial.begin(57600);
  Serial2.begin(57600);
   //*********************PIN MODE*************************
      
    for (int i = 0; i<3;i++) pinMode(motor_LF[i], OUTPUT);
    for (int i = 0; i<3;i++) pinMode(motor_LB[i], OUTPUT);
    for (int i = 0; i<3;i++) pinMode(motor_RF[i], OUTPUT);
    for (int i = 0; i<3;i++) pinMode(motor_RB[i], OUTPUT);
    for (int i = 0; i<3;i++) pinMode(motor_Reel_L[i], OUTPUT);
    for (int i = 0; i<3;i++) pinMode(motor_Reel_R[i], OUTPUT);
    for (int i = 0; i<3;i++) digitalWrite(motor_LF[i],LOW);
    for (int i = 0; i<3;i++) digitalWrite(motor_LB[i],LOW);
    for (int i = 0; i<3;i++) digitalWrite(motor_RF[i],LOW);
    for (int i = 0; i<3;i++) digitalWrite(motor_RB[i],LOW);
    for (int i = 0; i<3;i++) digitalWrite(motor_Reel_L[i],LOW);
    for (int i = 0; i<3;i++) digitalWrite(motor_Reel_R[i],LOW);
    pinMode(flat_0,OUTPUT);
    pinMode(flat_1,OUTPUT);
    pinMode(flat_2,OUTPUT);
    
    LSV.attach(LS); 
    RSV.attach(RS);
    //****************left back servo********************
    LBSV.attach(LBS);
    RBSV.attach(RBS);
    
    LSVA=5;
    RSVA=175;
    LBSVA=90;
    RBSVA=90;
  
    
    LSV.write(LSVA);
    RSV.write(RSVA);
    LBSV.write(LBSVA);
    RBSV.write(RBSVA);
    motorstop();

}

void loop() {
  bool motorstate=0;             //zero is spin  , one is run
            //zero is stop , one is out , two is in
  readdata(&pro);
  float left_joystick_angle=0;
  float left_joystick_length=0;
  int ly = pro.Ly;
  int lx = pro.Lx;
  int rx=  pro.Rx;
  
  if(pro.L1){
    if(pro.L2==false){
        digitalWrite(motor_Reel_L[0],LOW);
      digitalWrite(motor_Reel_L[1],HIGH);
      analogWrite(motor_Reel_L[2],255);
    }
  }
  if(pro.L2){
    if(pro.L1==false){
      digitalWrite(motor_Reel_L[0],HIGH);
      digitalWrite(motor_Reel_L[1],LOW);
      analogWrite(motor_Reel_L[2],255);
    }
  }
  if(pro.L2==0&&pro.L1==0){
      digitalWrite(motor_Reel_L[0],LOW);
      digitalWrite(motor_Reel_L[1],LOW);
      analogWrite(motor_Reel_L[2],0);
  
  }
  if(pro.L3){
    return;
  }
  if(pro.R1){
    
    if(pro.R2==0){
      digitalWrite(motor_Reel_R[0],HIGH);
      digitalWrite(motor_Reel_R[1],LOW);
      analogWrite(motor_Reel_R[2],255);
    }
  }
  if(pro.R2){
    
    if(pro.R1==0){
      digitalWrite(motor_Reel_R[0],LOW);
      digitalWrite(motor_Reel_R[1],HIGH);
      analogWrite(motor_Reel_R[2],255);
    }
  }
  if(pro.R2==0&&pro.R1==0){
      digitalWrite(motor_Reel_R[0],LOW);
      digitalWrite(motor_Reel_R[1],LOW);
      analogWrite(motor_Reel_R[2],0);
  }
  if(pro.R3){
  }
  if(pro.circle){
     if(RSVA>0  ){ 
      RSVA-=15;
      RSV.write(RSVA);
      }
  }
  if(pro.rectangle){
     if(RSVA<180){
      RSVA+=15;
      RSV.write(RSVA);
    }
  }
  if(pro.cross){
        LBSVA=90;
        RBSVA=90;
        LBSV.write(LBSVA);
        RBSV.write(RBSVA);
  }
  if(pro.triangle){
        LBSVA=170;
        RBSVA=10;
        LBSV.write(LBSVA);
        RBSV.write(RBSVA);
  }
  //***********************************************for flat
  if(pro.down){                    //flat_go_out
    flat_flag = 2;
  }
  else if(pro.up){                //flat_come_in
    flat_flag = 1;
  }
  else flat_flag=0;
  //**********************************************
  if(pro.right){
    if(LSVA>0){
      LSVA-=15;
      LSV.write(LSVA);
    }
  }
  if(pro.left){
    if(LSVA<180){
      LSVA+=15;
      LSV.write(LSVA);
    }
  }
  
  if(flat_flag!=last_flat_flag)flat_control(flat_flag);                                      //flat_control


  //************************************                                             motorcontrol
  lx=(float)map(lx,0,255,-200,200);
  ly=(float)map(ly,0,255,200,-200);
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
  if(motorstate==0){ 
  
     rx=(float)map(rx,0,255,-200,200);
    motorspin(rx);}
  else{
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
}
float Polar_Length(float x,float y){
  return sqrt(x*x+y*y);
}
