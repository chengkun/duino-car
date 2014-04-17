void readSoilData(){
  int v1 = analogRead(soil1);
  int v2 = analogRead(soil2);
  int v3 = analogRead(soil3);
  int v4 = analogRead(soil4);
  
  float v1v = ((float)v1)*(5.0 / 1023);
  float v2v = ((float)v2)*(5.0 / 1023);
  float v3v = ((float)v3)*(5.0 / 1023);
  float v4v = ((float)v4)*(5.0 / 1023);
  
  soil11 = v1v;
  soil22 = v2v;
  soil33 = v3v;
  soil44 = v4v;
}
