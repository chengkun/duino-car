//int PUL = 6;
//int DIR = 7;
//int LED = 13;
//int value = 0;
//boolean state = true;
//
//void testSetup()
//{
//  pinMode(PUL, OUTPUT);
//  pinMode(DIR, OUTPUT);
//}
//
//void testPlat()
//{
//  value = analogRead(A7);
//  if(value < 200){
//    up();
//    state = true;
//  } else if(value > 200 && value < 990){
//    down();
//    state = false;
//  }else if(value > 990){
//    if(state == true){
//      up();
//    }
//    else if(state == false){
//      down();
//    }
//  }
//}
//void up(){
//  digitalWrite(DIR, HIGH);
//  digitalWrite(PUL, HIGH);
//  delayMicroseconds(800);
//  digitalWrite(PUL,LOW);
//  delayMicroseconds(800);
//}
//void down(){
//  digitalWrite(DIR, LOW);
//  digitalWrite(PUL, HIGH);
//  delayMicroseconds(800);
//  digitalWrite(PUL,LOW);
//  delayMicroseconds(800);
//}
// driving the rear test platform to working and collecting the data.
void testDown(){
  while(testState == true){
    float cm1 = echo_duration/58.0;
    float cm2 = (int(cm1 * 100.0))/100.0;
    Serial.println(cm2);
    if (cm2 > 4.50 && cm2 < 50.00){
      down(200);
    }
    if (cm2 < 4.50 ){
      //gpsData();
//      delay(2000);
//      start();
//      testState = false;
      break;
    }
  }
}

void testUp(){
  while(testState == true){
    start();
    testState = false;
  }
}

void start(){
  if(analogRead(A7)<990){
    //for(int j=0; j<400; j++){
      down(400);
    //}
  }
  while(analogRead(A7) > 990) {
    up();
  }
  if(analogRead(A7)<990){
    down(200);
  }
}

void down(int n){
  for(int i=0;i<n;i++){
    digitalWrite(DIR, HIGH);
    digitalWrite(PUL, HIGH);
    delayMicroseconds(800);
    digitalWrite(PUL,LOW);
    delayMicroseconds(800);
    //xianwei();
  }
}
void xianwei(){
  if(analogRead(A7) < 990 && analogRead(A7) > 200){
    stepperStop();
  }
}
void up(){
  digitalWrite(DIR, LOW);
  digitalWrite(PUL, HIGH);
  delayMicroseconds(800);
  digitalWrite(PUL,LOW);
  delayMicroseconds(800);
}
void stepperStop(){
}
