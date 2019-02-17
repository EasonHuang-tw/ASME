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
struct joystick pro;
void readdata();
void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  Serial3.begin(57600);
  Serial.println("start");
}

void loop() {
  // put your main code here, to run repeatedly:
  readdata();
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
    pro.L1=false;
    }
  if(pro.L2){
    Serial.println("L2 is pressed");
    pro.L2=false;
  }
  if(pro.L3){
    Serial.println("L3 is pressed");
    pro.L3=false;
    }
  if(pro.R1){
    Serial.println("R1 is pressed");
    pro.R1=false;
  }if(pro.R2){
    Serial.println("R2 is pressed");
    pro.R2=false;
    }
  if(pro.R3){
    Serial.println("R3 is pressed");
    pro.R3=false;
  }if(pro.circle){
    Serial.println("circle is pressed");
    pro.circle=false;
    }
  if(pro.rectangle){
    Serial.println("rectangle is pressed");
    pro.rectangle=false;
  }if(pro.cross){
    Serial.println("cross is pressed");
    pro.cross=false;
    }
  if(pro.triangle){
    Serial.println("triangle is pressed");
    pro.triangle=false;
  }
  if(pro.up){
    Serial.println("up is pressed");
    pro.up=false;
  }
  if(pro.right){
    Serial.println("right is pressed");
    pro.right=false;
  }
  if(pro.down){
    Serial.println("down is pressed");
    pro.down=false;
  }
  if(pro.left){
    Serial.println("left is pressed");
    pro.left=false;
  }
  
}


void readdata(){
  int number =0;
  int  datastate=3;            //1:L 2:R 3:lx 4:ly 5:rx 6:rx
  int datastate_last=3;
  while(1){
    if(Serial3.available()){
      char data= (char)Serial3.read();
      switch  (data){
        case 'W':
          pro.up=true;
          break;
        case 'A':
          pro.left=true;
          break;
        case 'S':
          pro.down=true;
          break;
        case 'D':
          pro.right=true;
          break;
        case 'P':
          pro.rectangle=true;
          break;
        case 'G':
          pro.triangle=true;
          break;
        case 'C':
          pro.circle=true;
          break;
        case 'B':
          pro.cross=true;
          break;
        case 'L':
          pro.L1=true;
          break;
         case 'M':
           pro.L2=true;
          break;
         case 'N':
           pro.L3=true;
          break;
        case 'R':
          pro.R1=true;
          break;
         case 'T':
          pro.R2=true;
          break;
         case 'K':
          pro.R3=true;
          break;
        case 'l':
           datastate=8;
           break;
        case 'r':
          datastate=9;
           break;
        case 'x':
          datastate==8?datastate=3:datastate=5;
          break;
        case 'y':
          datastate==8?datastate=4:datastate=6;
          break;
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
        case '0':
          number=number*10+data-'0';
          break;
        case '\n':
          datastate=0;
          break;
        default:
          break;
      }
      if(datastate!=datastate_last&&datastate!=8&&datastate!=9){
       //Serial.println(datastate_last);
        switch(datastate_last){
          
          case 3:
            pro.Lx=number;
            number=0;
            datastate_last=datastate;
            break;
          case 4:
            pro.Ly=number;
            number=0;
            datastate_last=datastate;
            break;
          case 5:
            pro.Rx=number;
            number=0;
            datastate_last=datastate;
            break;
          case 6:
            pro.Ry=number;
            number=0;
            datastate_last=datastate;
            break;
          default:
            break;  
        }
      }
      if(data=='\n')
        break;
    }
  }
}
