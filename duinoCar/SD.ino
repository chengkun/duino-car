// save the datalog to SD card.
void saveSD(String dataString){
  File dataFile = SD.open("datalog.txt",FILE_WRITE);
  if(dataFile){
    dataFile.println(dataString);
    dataFile.close();
    Serial2.println(dataString);
  }
}

void saveSD_test(){
  File dataFile = SD.open(file,FILE_WRITE);
  if(dataFile){
    dataFile.print(soil11);
    dataFile.print(",");
    dataFile.print(soil22);
    dataFile.print(",");
    dataFile.print(soil33);
    dataFile.print(",");
    dataFile.print(objectT);
    dataFile.print(",");
    dataFile.print(envirT);
    dataFile.print(",");
    dataFile.print(soil11);
    dataFile.print(",");
    dataFile.print(gpslat);
    dataFile.print(",");
    dataFile.print(gpslon);
    dataFile.print(",");
    dataFile.print(gpsdate);
    dataFile.print(",");
    dataFile.print(dht_t);
    dataFile.print(",");
    dataFile.print(dht_h);
    dataFile.println(",");
    dataFile.close();
  }
}
