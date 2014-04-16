// save the datalog to SD card.
void saveSD(String dataString){
  File dataFile = SD.open("datalog.txt",FILE_WRITE);
  if(dataFile){
    dataFile.println(dataString);
    dataFile.close();
    Serial2.println(dataString);
  }
}
