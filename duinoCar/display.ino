//void displaySoil() {
//    dis.firstPage();  
//    do {
//        dis.setFont(u8g_font_helvR08);
//        dis.drawStr(0,10,"Soil mositure data");
//        
//        dis.drawStr(0,20,"No.1: ");
//        dis.setPrintPos(30,20);
//        dis.print(soil11);
//        
//        dis.drawStr(0,30,"No.2: ");
//        dis.setPrintPos(30,30);
//        dis.print(soil22);
//        
//        dis.drawStr(0,40,"No.3: ");
//        dis.setPrintPos(30,40);
//        dis.print(soil33);
//        
//        dis.drawStr(0,50,"No.4: ");
//        dis.setPrintPos(30,50);
//        dis.print(soil44);
//    } while( dis.nextPage() );
//    
//    #ifdef DEBUG_U8GLIB_SERIAL
//    Serial.print("U press the button "); //DEBUG_U8GLIB_SERIAL if you know what you are doing ^_*
//    Serial.println(button);              //in config.h file
//    for(int i = 0; i < 8; i++){
//      if(result[i]!= ""){
//        Serial.println(result[i]);
//      }
//    }
//    #endif
//    delay(200);
//}
void displayAll() {
    dis.firstPage();  
    do {
        dis.setFont(u8g_font_helvR08);
//        dis.drawStr(0,10,"Soil mositure data");
        
        dis.drawStr(0,10,"No.1: ");
        dis.setPrintPos(30,10);
        dis.print(soil11);
        
        dis.drawStr(0,20,"No.2: ");
        dis.setPrintPos(30,20);
        dis.print(soil22);
        
        dis.drawStr(0,30,"No.3: ");
        dis.setPrintPos(30,30);
        dis.print(soil33);
        
//        dis.drawStr(0,50,"No.4: ");
//        dis.setPrintPos(30,50);
//        dis.print(soil44);
        //display tn901 data      
        dis.drawStr(60,10,"OT: ");
        dis.setPrintPos(90,10);
        dis.print(objectT);
        
        dis.drawStr(60,20,"ET:");
        dis.setPrintPos(90,20);
        dis.print(envirT);
        
        //display gps data;
        dis.drawStr(60,30,"Lat:");
        dis.setPrintPos(80,30);
        dis.print(gpslat);
        
        dis.drawStr(0,40,"Lon:");
        dis.setPrintPos(25,40);
        dis.print(gpslon);
        
//        dis.drawStr(60,40,"Date:");
//        dis.setPrintPos(90,40);
//        dis.print(gpsdate);
        
//        dis.drawStr(0,50,"Time:");
//        dis.setPrintPos(30,50);
//        dis.print(gpstime);
        
        dis.drawStr(0,60,"D:");
        dis.setPrintPos(20,60);
        dis.print(gpsdate);
        
        dis.drawStr(0,50,"DD ");
        dis.setPrintPos(20,50);
        dis.print(date);
        
        dis.drawStr(60,50,"TT ");
        dis.setPrintPos(75,50);
        dis.print(time);
        
        dis.setPrintPos(60,40);
        dis.print(dht_t);
        
        dis.setPrintPos(90,40);
        dis.print(dht_h);
                
    } while( dis.nextPage() );
    
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
