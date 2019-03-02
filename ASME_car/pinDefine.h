
#define PI 3.14159265

//**************************(motor)*****************************


const int motor_LF[3]={40, 41, 9};  //(motor left  front) IN1 IN2 ENA 
const int motor_LB[3]={39, 38, 6};  //(motor left  back)  IN1 IN2 ENA 
const int motor_RF[3]={47, 46, 5};  //(motor right front) IN1 IN2 ENA 
const int motor_RB[3]={34, 35, 4};  //(motor right back)  IN1 IN2 ENA  

//*************************(Reel)*****************************

const int motor_Reel_L[3]={32,33,10};
const int motor_Reel_R[3]={30,31,11};

//************************(flat)***********************************

const int flat_0 = 20;
const int flat_1 = 21;
const int flat_2 = 22;

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
