
#define PI 3.14159265

//**************************(motor)*****************************


const int motor_LF[3]={40, 41, 9};  //(motor left  front) IN1 IN2 ENA 
const int motor_LB[3]={39, 38, 6};  //(motor left  back)  IN1 IN2 ENA 
const int motor_RF[3]={47, 46, 5};  //(motor right front) IN1 IN2 ENA 
const int motor_RB[3]={34, 35, 4};  //(motor right back)  IN1 IN2 ENA  

//*************************

const int left_reel = 25;
const int right_reel = 26;
bool left_reel_flag = 0;
bool right_reel_flag = 0;

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
   int Rx=129;
   int Ry=129;
   int Lx=129;
   int Ly=129;
};


