const byte interruptPin = 2;
int state = 0;
void setup() {
  // put your setup code here, to run once:
pinMode(interruptPin,INPUT_PULLUP);
attachInterrupt(digitalPinToInterrupt(interruptPin), haha, RISING);
pinMode(6,INPUT);
pinMode(7,INPUT);
pinMode(8,OUTPUT); //DIR
pinMode(9,OUTPUT); //STEP
delay(500);
Serial.begin(57600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(state);
if(state==0){delay(100);}
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
}
void haha(){
  state=0;
  if(digitalRead(6)==HIGH){
  state++;}
  if(digitalRead(7)==HIGH){
  state++;}
  
}
