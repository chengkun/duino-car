void tn901Setup(){
  tn.Init(2,3,4);
}

void readTN(){
  tn.Read();
  objectT = (int)tn.OT/100.0;
  envirT = (int)tn.ET/100.0;
}

float readOT(){
  return tn.OT;
}

float readET(){
  return tn.ET;
}
