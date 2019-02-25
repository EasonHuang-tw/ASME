
void motorstop(){
  for(int i=0;i<2;i++)digitalWrite(motor_RF[i], 0);
  for(int i=0;i<2;i++)digitalWrite(motor_RB[i], 0);
  for(int i=0;i<2;i++)digitalWrite(motor_LF[i], 0);
  for(int i=0;i<2;i++)digitalWrite(motor_LB[i], 0);
};
void motorrun(int type,int power ,int yaw){
  power=255;
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
  Serial.println("go back");
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
