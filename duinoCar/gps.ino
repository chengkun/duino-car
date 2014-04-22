// return the gps data
float* readGPS(TinyGPS &gps, float invalid){
  float gpsData[4];
  //float flat, flon;
  unsigned long age = 0;
  gps.f_get_position(&gpsData[0],&gpsData[1],&age);
  return gpsData;
}


void gpsData(){
//  bool newdata = false;
//  if(feedgps())newdata = true;
//  gpsdump(gps);
  bool newdata = false;
  unsigned long start = millis();
  
  // Every second we print an update
  while (millis() - start < 1000)
  {
    if (feedgps())
      newdata = true;
  }
  
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
  
  char s[8];
  sprintf(s, "%f", flat);
  
  gpslat = (float)((long int)(((long)flat)*10000.0)/10000.0);
  gpslon = (float)((long int)(((long)flon)*10000.0)/10000.0);
  
  get_date(gps, gpsdate);
  gps.get_datetime(&date, &time, 0);
  
  Serial.print(flat, 5);
  Serial.print(",");
  Serial.println(flon, 5);
  
  //Serial.println();
}
// get gps value
float get_float(float val, float invalid, int len, int prec)
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
    //Serial.print(sz);
  }
  else
  {   
    //Serial.print(val, prec);
    val = (int)(val * 10000.0)/10000.0;
    return val;
//    int vi = abs((int)val);
//    int flen = prec + (val < 0.0 ? 2 : 1);
//    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
//    for (int i=flen; i<len; ++i){
//      Serial.print(" ");
//    }
  }
  feedgps();
}

// print gps on serial
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
    Serial.print(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1);
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i=flen; i<len; ++i)
      Serial.print(" ");
  }
  feedgps();
}

void get_date(TinyGPS &gps, String &gpsdate){
  gpsdate = "";
  int year;
  byte month, day, hour, minute, second, hundredths;
  unsigned long age;
  gps.crack_datetime(&year, &month, &day, &hour, &minute, &second, &hundredths, &age);
  gps.get_datetime(&date, &time, 0);
  if (age == TinyGPS::GPS_INVALID_AGE)
    Serial.print("*******    *******    ");
  else
  {
    char sz[32];
    sprintf(sz, "%02d/%02d/%02d %02d:%02d:%02d   ",
        month, day, year, hour, minute, second);
    for(int i = 0;i < 20;++i){
        gpsdate = gpsdate + sz[i];
    }
    Serial.print(sz);
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
    sprintf(sz, "%02d/%02d/%02d %02d:%02d:%02d   ",
        month, day, year, hour, minute, second);
    Serial.print(sz);
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

//void saveFloatSD(float data, int prec){
//  File dataFile = SD.open("datalog1.txt",FILE_WRITE);
//  if(data){
//    dataFile.println(data,prec);
//  }
//}
//
//void saveCharSD(char data[32]){
//  File dataFile = SD.open(file,FILE_WRITE);
//  if(data){
//    dataFile.println(data);
//    dataFile.close();
//    //Serial2.println(dataString);
//  }
//}
