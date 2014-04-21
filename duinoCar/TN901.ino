void tn901Setup(){
  tn.Init(2,3,4);
}

void readTN(){
  tn.Read();
  tn.OT;
  tn.ET;
}

float readOT(){
  return tn.OT;
}

float readET(){
  return tn.ET;
}
