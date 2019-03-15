void dataclear(joystick *pro){
   pro->circle=false;
   pro->cross=false;
   pro->rectangle=false;
   pro->triangle=false;
   pro->up=false;
   pro->down=false;
   pro->left=false;
   pro->right=false;
   pro->R1=false;
   pro->R2=false;
   pro->R3=false;
   pro->L1=false;
   pro->L2=false;
   pro->L3=false;
   pro->Rx=128;
   pro->Ry=128;
   pro->Lx=128;
   pro->Ly=128;
  }
void readdata(joystick *pro){
  dataclear(pro);
  int number =0;
  int  datastate=3;            //1:L 2:R 3:lx 4:ly 5:rx 6:rx
  int datastate_last=3;
  while(1){
    if(Serial2.available()){
      char data= (char)Serial2.read();
      switch  (data){
        case 'W':
          pro->up=true;
          break;
        case 'A':
          pro->left=true;
          break;
        case 'S':
          pro->down=true;
          break;
        case 'D':
          pro->right=true;
          break;
        case 'P':
          pro->rectangle=true;
          break;
        case 'G':
          pro->triangle=true;
          break;
        case 'C':
          pro->circle=true;
          break;
        case 'B':
          pro->cross=true;
          break;
        case 'L':
          pro->L1=true;
          break;
         case 'M':
           pro->L2=true;
          break;
         case 'N':
           pro->L3=true;
          break;
        case 'R':
          pro->R1=true;
          break;
         case 'T':
          pro->R2=true;
          break;
         case 'K':
          pro->R3=true;
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
            pro->Lx=number;
            number=0;
            datastate_last=datastate;
            break;
          case 4:
            pro->Ly=number;
            number=0;
            datastate_last=datastate;
            break;
          case 5:
            pro->Rx=number;
            number=0;
            datastate_last=datastate;
            break;
          case 6:
            pro->Ry=number;
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
  //delay(50);
}
