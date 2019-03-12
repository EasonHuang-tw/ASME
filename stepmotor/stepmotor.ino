int state = 0;
void setup() {
  // put your setup code here, to run once:
<<<<<<< HEAD
attachInterrupt(digitalPinToInterrupt(interruptPin), haha, RISING);
pinMode(3,INPUT);
pinMode(4,INPUT);
=======
attachInterrupt(digitalPinToInterrupt(2), haha, RISING);
pinMode(6,INPUT);
pinMode(7,INPUT);
>>>>>>> 0e02aee97da83c4f1b1d11466e1d7982e6127f6e
pinMode(8,OUTPUT); //DIR
pinMode(9,OUTPUT); //STEP
delay(500);
Serial.begin(57600);
}

void loop() {
  // put your main code here, to run repeatedly:
<<<<<<< HEAD
  switch (state){
    case 0:
      digitalWrite(9,LOW);
      break;
    case 1:
        digitalWrite(8,HIGH);
      digitalWrite(9,HIGH);
      delayMicroseconds(70);
      digitalWrite(9,LOW);
      delayMicroseconds(70);
      break;
    case 2:
       digitalWrite(8,LOW);
      digitalWrite(9,HIGH);
      delayMicroseconds(70);
      digitalWrite(9,LOW);
      delayMicroseconds(70);
      break;
  }
=======
  Serial.println(state);
if(state==0){
  digitalWrite(9,LOW);
}
if(state==1){
  digitalWrite(8,HIGH);
  digitalWrite(9,HIGH);
  delayMicroseconds(70);
  digitalWrite(9,LOW);
  delayMicroseconds(70);  
}
if(state==2){
  digitalWrite(8,LOW);
  digitalWrite(9,HIGH);
  delayMicroseconds(70);
  digitalWrite(9,LOW);
  delayMicroseconds(70);
  
}
>>>>>>> 0e02aee97da83c4f1b1d11466e1d7982e6127f6e
}

void haha(){
  state=0;
  if(digitalRead(3)){
  state++;}
  if(digitalRead(4)){
  state++;}
  
}
