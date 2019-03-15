int state = 0;
int interruptPin=2;
void setup() {
  // put your setup code here, to run once:
attachInterrupt(digitalPinToInterrupt(interruptPin), haha, RISING);
pinMode(3,INPUT);
pinMode(4,INPUT);
attachInterrupt(digitalPinToInterrupt(2), haha, RISING);
pinMode(6,INPUT);
pinMode(7,INPUT);
pinMode(8,OUTPUT); //DIR
pinMode(9,OUTPUT); //STEP
delay(500);
Serial.begin(57600);
}

void loop() {
  // put your main code here, to run repeatedly:
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
}

void haha(){
  state=0;
  if(digitalRead(3)){
  state++;}
  if(digitalRead(4)){
  state++;}
  
}
