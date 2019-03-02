void flat_control(int flag){
    if(flag==0){         //stop
      
      digitalWrite(flat_1,LOW);
      digitalWrite(flat_2,LOW);
      delay(5);
      digitalWrite(flat_0,HIGH);        //interrupt
      Serial.println("stop");
    }
    else if(flag==1){   //out
      
      digitalWrite(flat_1,HIGH);
      digitalWrite(flat_2,LOW);
      delay(100);
      digitalWrite(flat_0,HIGH);        //interrupt
      
      Serial.println("out");
    }
    else if(flag==2){  //in
      digitalWrite(flat_1,HIGH);
      digitalWrite(flat_2,HIGH);
      delay(100);
      digitalWrite(flat_0,HIGH);        //interrupt
      Serial.println("in");
    }
    last_flat_flag=flag;
    delay(100);
    digitalWrite(flat_0,LOW);
  }
