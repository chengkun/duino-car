#include "U8glib.h"

U8GLIB_ST7920_128X64_1X u8g(10,9,8);

const int A = 2;
const int B = 3;
const int C = 4;
const int D = 5;
const int E = 6;
const int F = 7;
//const int A0 = 0;
//const int A1 = 1;

int buttonA = 0;
int buttonB = 0;
int buttonC = 0;
int buttonD = 0;
int buttonE = 0;
int buttonF = 0;

int valueHori = 0;
int valueVerti = 0;
int valuePotent = 0;

String button="k";
String oldButton="k";

String inputString = "";
boolean stringComplete = false;
boolean oldStringComplete = false;
String  strDataP[8]="";
String  result[8]="";

int led = 13;

String forward;

#include <LCD12864RSPI.h>
#define AR_SIZE( a ) sizeof( a ) / sizeof( a[0] )
typedef unsigned char uchar;

uchar show0[]={0xCE,0xF7,0xB1,0xB1,0xC5,0xA9,0xC1,0xD6,0xBF,0xC6,0xBC,0xBC,0xB4,0xF3,0xD1,0xA7};//极客工坊
uchar show1[]={0xBB,0xFA,0xB5,0xE7,0xD1,0xA7,0xD4,0xBA};

void setup(){
  Serial.begin(9600);
  Serial.println("Joystick test");

  forward = String("Forward");

  pinMode(A,INPUT);
  pinMode(B,INPUT);
  pinMode(C,INPUT);
  pinMode(D,INPUT);
  pinMode(E,INPUT);
  pinMode(F,INPUT);
  //u8g.setRot90();
  
  logoDis();
}
void logoDis(){
  LCDA.Initialise();
  LCDA.CLEAR();
  delay(100);
  LCDA.DisplayString(0,0,show0,AR_SIZE(show0));//第一行第三格开始，显示文字极客工坊
  delay(100);
  LCDA.DisplayString(2,2,show1,AR_SIZE(show1));;//第三行第二格开始，显示文字geek-workshop
  delay(1000);

}

void ledAct(){
  digitalWrite(led,HIGH);
  delay(100);
  digitalWrite(led,LOW);
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

void drawInput(){
    u8g.setFont(u8g_font_helvB08);
    u8g.setPrintPos(0,20);
    u8g.print(inputString);
}

void reflashLCD(){
  if(stringComplete){
    digitalWrite(led,HIGH);
    u8g.firstPage();
    do{
      drawInput();
    }while(u8g.nextPage());
    inputString = "";
    stringComplete = false;
    digitalWrite(led,LOW);
  }
}

void draw(String button, String *result, int valueHori, int valueVerti) {
  if(button!="t"||(valueHori>516&&valueHori<520)||(valueVerti>509&&valueVerti<512)){
    u8g.firstPage();  
    do {
        u8g.setFont(u8g_font_helvR08);
        u8g.setPrintPos(0,20);
        u8g.drawStr(0,10,"Now you press the button");
        u8g.print(button);
        u8g.setPrintPos(20,20);
        u8g.print(valueHori);
        u8g.setPrintPos(50,20);
        u8g.print(valueVerti);
        u8g.setPrintPos(80,20);
        u8g.print(valuePotent);
        //print the data from sensor
        //if(result[0] != "Forward "||result[0] != "Backward "||result[0] != "Turn left"||result[0] != "Turn right"){
        /*
        if(inputString.length() < 15){
          u8g.drawStr(40,64,"Now: ");
          u8g.setPrintPos(64,64);
          u8g.print(inputString);
        } else {
          u8g.drawStr(40,64,"Now: ");
          u8g.drawStr(64,64,"Wait");
        }*/
          u8g.setPrintPos(0,30);
          u8g.print(result[0]);
          u8g.setPrintPos(60,30);
          u8g.print(result[1]);
          u8g.setPrintPos(0,40);
          u8g.print(result[2]);
          u8g.setPrintPos(60,40);
          u8g.print(result[3]);
          u8g.setPrintPos(0,50);
          u8g.print(result[4]);
          u8g.setPrintPos(60,50);
          u8g.print(result[5]);
          /*
          u8g.setPrintPos(0,60);
          u8g.print(result[6]);
          u8g.setPrintPos(60,60);
          u8g.print(result[7]);
          */
        //} else {
        

        
    } while( u8g.nextPage() );
    
    #ifdef DEBUG_U8GLIB_SERIAL
    Serial.print("U press the button "); //DEBUG_U8GLIB_SERIAL if you know what you are doing ^_*
    Serial.println(button);              //in config.h file
    for(int i = 0; i < 8; i++){
      if(result[i]!= ""){
        Serial.println(result[i]);
      }
    }
    #endif
    delay(200);
  }


}

void printSerial(String *strDataP){
  if(stringComplete!=0){
    digitalWrite(led,HIGH);
    for(int i=0;i<8;i++){
      if(strDataP[i]!=0){
        //strDataP[i].indexof("\n");
        //strDataP[i]=strDataP[i].substring(0,strDataP[i].indexof("\n");
        if(strDataP[i].endsWith("\n")){
          strDataP[i]=strDataP[i].substring(0,strDataP[i].indexOf("\n"));
          Serial.println(strDataP[i]);
        } else {
          Serial.println(strDataP[i]);
        }
      }
    }
    inputString="";
    stringComplete = false;
    digitalWrite(led,LOW);
  }
}

void handleData(String *strDataP, String *result){
  if(stringComplete!=0 ){
    digitalWrite(led,HIGH);
    for(int i=0;i<8;i++){
      if(strDataP[i]!=0){
        if(strDataP[i].endsWith("\n")){
          strDataP[i]=strDataP[i].substring(0,strDataP[i].indexOf("\n"));
          result[i] = strDataP[i];
          //Serial.println(strDataP[i]);
        } else {
          result[i] = strDataP[i];
          //Serial.println(strDataP[i]);
        }
      }
    }
  /*
  if(result[0].equalsIgnoreCase("Forward")){
    for(int k=1; k<8; k++){
      result[k]="";
    }
  }
  */
  inputString="";
  stringComplete = false;
  //oldStringComplete = stringComplete;
  digitalWrite(led,LOW);
  }
}

void stringSplit(String inputString,String *strDataP){
  if(stringComplete!=0){
  String  message = inputString; // holds text not yet split
  int     commaPosition;  // the position of the next comma in the string
  String  *strData= strDataP;
  int i=0;
  do
  {
      commaPosition = message.indexOf(',');
      if(commaPosition != -1)
      {
          strData[i]=message.substring(0,commaPosition);
          //Serial.println( strData[i]);
          i++;
          message = message.substring(commaPosition+1, message.length());
      }
      else
      {  // here after the last comma is found
         if(message.length() > 0)
           strData[i]=message;
           //Serial.println(strData[i]);  // if there is text after the last comma,
                                     // print it
      }
   }
   while(commaPosition >=0);
  }
}

void loop(){
  valueHori = analogRead(A0);
  valueVerti = analogRead(A1);
  valuePotent = analogRead(A2);
  
  //if(digitalRead()
  if(valueVerti > 600){
    if(valueHori < 300){
      button = "Z"; //turn left
    } 
    else if(valueHori > 600){
      button = "Y"; //turn right
    }
    else{
      button = "X"; //forward
    }
  }
  else if(valueVerti < 300){
    button = "W";  //backward
  }
  else{
    if(valueHori > 600){
      button = "V"; //turn right
    }
    else if(valueHori < 300){
      button = "U"; //turn left
    }
    else{
      button = "T"; // stop
    }
  }
  if(digitalRead(A)==LOW){
    button = "A";
  }
  else if(digitalRead(B)==LOW){
    button = "B";
  }
  else if(digitalRead(C)==LOW){
    button = "C";
  }
  else if(digitalRead(D)==LOW){
    button = "D";
  }
  else if(digitalRead(E)==LOW){
    button = "E";
  }
  else if(digitalRead(F)==LOW){
    button = "F";
  }

  if(button != oldButton){
    Serial.println(button);
    oldButton = button;
  }
  else {
    //Serial.println('T');
  }

  stringSplit(inputString,strDataP);
  handleData(strDataP,result);
  draw(button,result,valueHori,valueVerti);
}
