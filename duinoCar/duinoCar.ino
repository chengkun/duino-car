#include <TimerOne.h>
#include <SD.h>
#include <TinyGPS.h>
#include <TN901.h>
#include <U8glib.h>
#include "config.h"


void setup(){
  Serial.begin(9600);   // Debug port
  Serial2.begin(9600);  // APC 220 port
  Serial3.begin(4800);  // read GPS port

  if(!SD.begin(sdCS)){
    Serial.println("Card failed, or not present");
  }else{
    Serial.println("Card initialized.");
  }
  
  pinMode(led,OUTPUT);
  
  pinMode(throttle,OUTPUT);
  pinMode(switchPin,OUTPUT);
  digitalWrite(switchPin,LOW);

  pinMode(PUL, OUTPUT);
  pinMode(DIR, OUTPUT);
  
  pinMode(trigPin, OUTPUT);                           // Trigger pin set to output
  pinMode(echoPin, INPUT);                            // Echo pin set to input
  pinMode(onBoardLED, OUTPUT);                        // Onboard LED pin set to output
  start();                                            // Initialize the testPlatform
  
  Timer1.initialize(TIMER_US);                        // Initialise timer 1
  Timer1.attachInterrupt( timerIsr );                 // Attach interrupt to the timer service routine 
  attachInterrupt(echo_int, echo_interrupt, CHANGE);  // Attach interrupt to the sensor echo input
  tn901Setup();
}

void loop(){

  if( Serial2.available()){
    char ch = Serial2.read();
    if(ch == 'A'){
      Serial2.println("34.41294,108.06941,00002000,131658,0.12,0.93");
      ledAct();
    }
    else if(ch == 'B'){
      Serial2.println("34.42345,108.07364,00002000,131660,0.34,10.12");
      ledAct();
    }
    else if(ch == 'X'){
      forward();
      Serial2.println("Forward");
      ledAct();
    }
    else if(ch == 'W'){
      backward();
      Serial2.println("Backward");
      ledAct();
    }
    else if(ch == 'U' || ch == 'Z'){
      Serial2.println("Turn left");
      ledAct();
    }
    else if(ch == 'V' || ch == 'Y'){
      Serial2.println("Turn right");
      ledAct();
    }
    else if(ch == 'T'){
      stopCar();
      Serial2.println("STOP");
      ledAct();
    }
    else if(ch == 'D'){
      stopCar();
      Serial2.println("Testing");
      testState = true;
      test();
    }
    else if(ch == 'C'){
    }
  }
}

void serialEvent(){
  while(Serial.available()){
    char inChar = (char)Serial.read();
    inputString +=inChar;
    if(inChar == '\n'){
      stringComplete = true;
    }
  }
}











