void displaySoil() {
    dis.firstPage();  
    do {
        dis.setFont(u8g_font_helvR08);
        dis.drawStr(0,10,"Soil mositure data");
        
        dis.drawStr(0,20,"No.1: ");
        dis.setPrintPos(20,20);
        dis.print(soil11);
        
        dis.drawStr(0,30,"No.2: ");
        dis.setPrintPos(20,30);
        dis.print(soil22);
        
        dis.drawStr(0,40,"No.3: ");
        dis.setPrintPos(20,30);
        dis.print(soil22);
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
