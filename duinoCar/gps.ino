
void gpsData(){
  bool newdata = false;
  if(feedgps())newdata = true;
  gpsdump(gps);
}

static void gpsdump(TinyGPS &gps)
{
  float flat, flon;
  unsigned long age, date, time, chars = 0;
  unsigned short sentences = 0, failed = 0;
  static const float LONDON_LAT = 51.508131, LONDON_LON = -0.128002;
  
  gps.f_get_position(&flat, &flon, &age);
  print_float(flat, TinyGPS::GPS_INVALID_F_ANGLE, 9, 5);
  print_float(flon, TinyGPS::GPS_INVALID_F_ANGLE, 10, 5);
  print_date(gps);
  
  Serial.println();
}


static void print_float(float val, float invalid, int len, int prec)
{
  char sz[32];
  if (val == invalid)
  {
    strcpy(sz, "*******");
    sz[len] = 0;
        if (len > 0) 
          sz[len-1] = ' ';
    for (int i=7; i<len; ++i)
        sz[i] = ' ';
    Serial.print(sz);
  }
  else
  {
    File dataFile = SD.open("datalog.txt",FILE_WRITE);
    if(val){
      dataFile.print(val, prec);
      dataFile.close();
    }
    Serial.print(val, prec);
    
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1);
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i=flen; i<len; ++i){
      Serial.print(" ");
      File dataFile = SD.open(file,FILE_WRITE);
      dataFile.print(",");
      dataFile.close();
    }
  }
  feedgps();
}

static void print_date(TinyGPS &gps)
{
  int year;
  byte month, day, hour, minute, second, hundredths;
  unsigned long age;
  gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);
  if (age == TinyGPS::GPS_INVALID_AGE)
    Serial.print("*******    *******    ");
  else
  {
    char sz[32];
    sprintf(sz, "%02d/%02d/%02d,%02d:%02d:%02d   ",
        month, day, year, hour, minute, second);
    Serial.print(sz);
    saveCharSD(sz);
  }
  feedgps();
}

static bool feedgps()
{
  while (Serial3.available())
  {
    if (gps.encode(Serial3.read()))
      return true;
  }
  return false;
}

void saveFloatSD(float data, int prec){
  File dataFile = SD.open("datalog1.txt",FILE_WRITE);
  if(data){
    dataFile.println(data,prec);
  }
}

void saveCharSD(char data[32]){
  File dataFile = SD.open(file,FILE_WRITE);
  if(data){
    dataFile.println(data);
    dataFile.close();
    //Serial2.println(dataString);
  }
}
