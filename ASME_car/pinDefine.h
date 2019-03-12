#define PI 3.14159265
//**************************(motor)*****************************


const int motor_LF[3]={49,48,5};  //(motor left  front) IN1 IN2 ENA 
const int motor_LB[3]={51,50,2};  //(motor left  back)  IN1 IN2 ENA 
const int motor_RF[3]={47,46,4};  //(motor right front) IN1 IN2 ENA 
const int motor_RB[3]={53,52,3};  //(motor right back)  IN1 IN2 ENA  

//*************************(Reel)*****************************

const int motor_Reel_R[3]={44,45,6};
const int motor_Reel_L[3]={42,43,8};

//************************(flat)***********************************

const int flat_0 = 22;
const int flat_1 = 23;
const int flat_2 = 24;

//**********************Servo*********************************

const int LS = 12;
const int RS = 13;


//***************************read data******************************
struct joystick {
   bool circle=false;
   bool cross=false;
   bool rectangle=false;
   bool triangle=false;
   bool up=false;
   bool down=false;
   bool left=false;
   bool right=false;
   bool R1=false;
   bool R2=false;
   bool R3=false;
   bool L1=false;
   bool L2=false;
   bool L3=false;
   int Rx=128;
   int Ry=128;
   int Lx=128;
   int Ly=128;
};
