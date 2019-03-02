const byte interruptPin = 2;
void setup() {
  // put your setup code here, to run once:
pinMode(interruptPin,RISING);
pinMode(8,OUTPUT);
pinMode(9,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
digitalWrite(9,HIGH);
delayMicroseconds(70);
digitalWrite(9,LOW);
delayMicroseconds(70);
}
