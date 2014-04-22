#include <TimerOne.h>
#include <SD.h>
#include <TinyGPS.h>
#include <TN901.h>
#include <U8glib.h>
#include "DHT.h"
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
  //start();                                            // Initialize the testPlatform
  
  Timer1.initialize(TIMER_US);                        // Initialise timer 1
  Timer1.attachInterrupt( timerIsr );                 // Attach interrupt to the timer service routine 
  attachInterrupt(echo_int, echo_interrupt, CHANGE);  // Attach interrupt to the sensor echo input
  tn901Setup();
  dht.begin();
}

void loop(){
  
  readSoilData();
  readTN();
  gpsData();
  //readGPSdata = readGPS(gps, TinyGPS::GPS_INVALID_F_ANGLE);
  
  //displaySoil();
  displayAll();
  saveSD_test();
  
  if( Serial2.available()){
    char ch = Serial2.read();
    switch(ch){
      case 'A':
        Serial2.println("34.41294,108.06941,00002000,131658,0.12,0.93");
        saveSD_test();
        ledAct();
        break;
      case 'B':
        Serial2.println("34.42345,108.07364,00002000,131660,0.34,10.12");
        ledAct();
        break;
      case 'X':
        forward();
        Serial2.println("Forward");
        ledAct();
        break;
      case 'W':
        backward();
        Serial2.println("Backward");
        ledAct();
        break;
      case 'U':
        Serial2.println("Turn left");
        ledAct();
        break;
      case 'Z':
        Serial2.println("Turn left");
        ledAct();
        break;
      case 'V':
        Serial2.println("Turn right");
        ledAct();
        break;
      case 'Y':
        Serial2.println("Turn right");
        ledAct();
        break;
      case 'T':
        stopCar();
        Serial2.println("STOP");
        ledAct();
        break;
      case 'D':
        stopCar();
        Serial2.println("Testing");
        testState = true;
        test();
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
