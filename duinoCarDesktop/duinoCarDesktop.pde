import controlP5.*;
import processing.opengl.*;
import processing.serial.*;

Serial g_serial;
ControlP5 cp5;

PImage img;

public static final int COM_SPEED = 115200;
public static final int FRAMERATE = 20;

/* Axis constants */
public static int NUM_AXIS = 2;
public static final int ROLL = 0, PITCH = 1, YAW = 2;
public static final String AXIS_NAME[] = { "ROLL", "PITCH", "YAW" };
public static final int TOGGLE_SIZE = 12;
public static final int DEBUG_VARS_NUM = 5;

Textlabel txtlblWhichcom;
Textlabel txtlblLogo;
Textlabel txtlblState,txtlblLongtitude,txtlblLatitude,txtlblWater,txtlblPoint;
ListBox commListbox,baudListbox;

int commListMax;
int serialState = 0;

int windowsX    = 1020;        int windowsY    = 540;
int disWaterX   = 180;         int disWaterY   = 250;

Button buttonIMPORT, buttonSAVE, buttonREAD, buttonRESET, buttonWRITE, buttonCALIBRATE_ACC, buttonCALIBRATE_MAG, buttonSTART, buttonSTOP, buttonSETTING, 
       buttonAcc, buttonBaro, buttonMag, buttonGPS, buttonSonar, buttonOptic, buttonRXbind, btnQConnect,buttonExport,
       btMagDecl,btMWiiHome,btDownloads;
Button buttonSubmit;


color yellow_ = color(200, 200, 20), green_ = color(30, 120, 30), red_ = color(120, 30, 30), blue_ = color(50, 50, 100),
       grey_ = color(30, 30, 30),black_ = color(0, 0, 0),orange_ =color(200,128,0),white_ = color(145);
boolean graphEnable = false;boolean readEnable = false;boolean writeEnable = false;boolean calibrateEnable = false;

int version,subversion;
int init_com; //,graph_on;

PFont font8,font12,font15;

String shortifyPortName(String portName, int maxlen)  {
  String shortName = portName;
  if(shortName.startsWith("/dev/")) shortName = shortName.substring(5);  
  if(shortName.startsWith("tty.")) shortName = shortName.substring(4); // get rid off leading tty. part of device name
  if(portName.length()>maxlen) shortName = shortName.substring(0,(maxlen-1)/2) + "~" +shortName.substring(shortName.length()-(maxlen-(maxlen-1)/2));
  if(shortName.startsWith("cu.")) shortName = "";// only collect the corresponding tty. devices
  return shortName;
}

void setup(){
  size(windowsX,windowsY);
  frameRate(FRAMERATE); 
  noStroke();
  
  textFont(createFont("Helvetica", 25));
  
  img = loadImage("open-streets-dc.png");
  img.resize(600,280);
  
  font8 = createFont("Arial bold",8,false);font12 = createFont("Arial bold",12,false);font15 = createFont("Arial bold",15,false);
  
  cp5 = new ControlP5(this);
  cp5.setControlFont(font12);
  
  cp5.addTextfield("Longitudinal").setPosition(180,20).setSize(70,20).setFont(font12).setFocus(true).setColor(color(255,0,0));
  cp5.addTextfield("Transverse").setPosition(280,20).setSize(70,20).setFont(font12).setColor(color(255,0,0));
  //buttonSubmit = cp5.addButton("bSUBMIT",
  
  // Baud list items
  baudListbox = cp5.addListBox("baudList",20,150,110,240).setBarHeight(18); // make a listbox with available Baudrates
  baudListbox.captionLabel().set("BAUD_RATE").setColorBackground(red_);
  baudListbox.addItem("9600"  ,9600); // addItem(name,value)
  baudListbox.addItem("14400" ,14400);
  baudListbox.addItem("19200" ,19200);
  baudListbox.addItem("28800" ,28800);
  baudListbox.addItem("38400" ,38400);
  baudListbox.addItem("57600" ,57600);
  baudListbox.addItem("115200",115200);
  
  commListbox = cp5.addListBox("portComList",20,75,110,240).setBarHeight(18); // make a listbox and populate it with the available comm ports
  commListbox.captionLabel().set("PORT COM").setColorBackground(red_);
  commListbox.setColorBackground(grey_);
  for(int i=0;i<Serial.list().length;i++) {
    String pn = shortifyPortName(Serial.list()[i], 13);
    if (pn.length() >0 ) commListbox.addItem(pn,i); // addItem(name,value)
    commListMax = i;
  }
  commListbox.addItem("Close Comm",++commListMax); // addItem(name,value)
  // text label for which comm port selected
  txtlblWhichcom = cp5.addTextlabel("txtlblWhichcom","No Port Selected",20,40); // textlabel(name,text,x,y)
  txtlblLogo = cp5.addTextlabel("txtlblLogo","NWSUAF",40,12);
  
  btnQConnect = cp5.addButton("bQCONN",1,25,270,100,19).setLabel("  ReConnect").setColorBackground(red_);
  buttonSTART = cp5.addButton("bSTART",1,25,300,45,19); buttonSTART.setLabel("START"); buttonSTART.setColorBackground(grey_);
  buttonSTOP = cp5.addButton("bSTOP",1,80,300,40,19); buttonSTOP.setLabel("STOP"); buttonSTOP.setColorBackground(grey_);

  txtlblState = cp5.addTextlabel("txtlblState","State",190,305);
  txtlblLongtitude = cp5.addTextlabel("txtlblLongtitude","Longtitude",270,305);
  txtlblLatitude = cp5.addTextlabel("txtlblLatitude","Latitude",390,305);
  txtlblWater = cp5.addTextlabel("txtlblWater","Moisture",490,305);
  txtlblPoint = cp5.addTextlabel("txtlblPoint","Point",590,305);
  
}

void draw(){
  background(80);
  //rect(30, 20, 55, 55, 7);
  
  fill(white_);
  rect(10,10,140,320);
  rect(160,10,610,320);
  rect(780,10,230,320);
  rect(10,340,1000,190);
  fill(grey_);
  rect(165,300,600,25);
  //image(img,165,15);
  fill(black_);
  text("西北农林科技大学",760, 480); //name of the university
  text("机电学院",810,510);
  fill(green_);
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 5; j++){ 
      float x = disWaterX+i*40;
      float y = disWaterY-j*40;  // column 2
      rect(x, y, 35, 35);
    }
  }
  fill(yellow_);
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < 5; j++){ 
      float x = disWaterX+i*40;
      float y = disWaterY-j*40;  // column 2
      rect(x, y, 35, 35);
    }
  }
}


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//==================================================================
class cDataArray {
  float[] m_data;
  int m_maxSize, m_startIndex = 0, m_endIndex = 0, m_curSize;
  
  cDataArray(int maxSize){
    m_maxSize = maxSize;
    m_data = new float[maxSize];
  }
  void addVal(float val) {
    m_data[m_endIndex] = val;
    m_endIndex = (m_endIndex+1)%m_maxSize;
    if (m_curSize == m_maxSize) {
      m_startIndex = (m_startIndex+1)%m_maxSize;
    } else {
      m_curSize++;
    }
  }
  float getVal(int index) {return m_data[(m_startIndex+index)%m_maxSize];}
  int getCurSize(){return m_curSize;}
  int getMaxSize() {return m_maxSize;}
  float getMaxVal() {
    float res = 0.0;
    for(int i=0; i<m_curSize-1; i++) if ((m_data[i] > res) || (i==0)) res = m_data[i];
    return res;
  }
  float getMinVal() {
    float res = 0.0;
    for(int i=0; i<m_curSize-1; i++) if ((m_data[i] < res) || (i==0)) res = m_data[i];
    return res;
  }
  float getRange() {return getMaxVal() - getMinVal();}
}

class cGraph {
  float m_gWidth, m_gHeight, m_gLeft, m_gBottom, m_gRight, m_gTop;
  
  cGraph(float x, float y, float w, float h) {
    m_gWidth     = w; m_gHeight    = h;
    m_gLeft      = x; m_gBottom    = y;
    m_gRight     = x + w;
    m_gTop       = y + h;
  }
  
  void drawGraphBox() {
    stroke(0, 0, 0);
    rectMode(CORNERS);
    rect(m_gLeft, m_gBottom, m_gRight, m_gTop);
  }
  
  void drawLine(cDataArray data, float minRange, float maxRange) {
    float graphMultX = m_gWidth/data.getMaxSize();
    float graphMultY = m_gHeight/(maxRange-minRange);
    /*
    for(int i=0; i<data.getCurSize()-1; ++i) {
      float x0 = i*graphMultX+m_gLeft;
      float y0 = m_gTop-(((data.getVal(i)-(maxRange+minRange)/2)*scaleSlider.value()+(maxRange-minRange)/2)*graphMultY);
      float x1 = (i+1)*graphMultX+m_gLeft;
      float y1 = m_gTop-(((data.getVal(i+1)-(maxRange+minRange)/2 )*scaleSlider.value()+(maxRange-minRange)/2)*graphMultY);
      line(x0, y0, x1, y1);
    }
    */
  }
}


/****************** Error definition ****************/
class ErrorInfo {
  int code;
  public final String text;
  public final String hint;
  
  ErrorInfo(int code, String text, String hint) {
    this.code = code;
    this.text = text;
    this.hint = hint;
  }
}

// Frmware errors
public static final int ERR_NO_SENSOR = 1;
public static final int ERR_CALIB_ACC = 2;
public static final int ERR_SET_POWER = 4;
public static final int ERR_CALIB_POLES = 8;
// GUI errors
public static final int ERR_GUI_VERSION = 128;


private ErrorInfo errors[] = {
  new ErrorInfo(ERR_NO_SENSOR, "Sensor is not connected", "Turn off power and check I2C sensor connection. DON'T CONNECT SENSOR WHEN BOARD IS POWERED!"),
  new ErrorInfo(ERR_CALIB_ACC, "Accelerometer is not calibrated", "Simple calibration: Level sensor horisontally as precise as possible, and than press \"CALIB_ACC\". For more precise six-points calibration see instruction manual"),
  new ErrorInfo(ERR_SET_POWER, "POWER is not set",  "Increse POWER from low values (50 for example) until motor will give enough torque, but does not make too hot"),
  new ErrorInfo(ERR_CALIB_POLES, "POLES is not set",  "Use AUTO calibration to get number of poles and direction. Set precise number of poles manually if detected wrong (it equals to number of magnets in the motor)"),
  new ErrorInfo(ERR_GUI_VERSION, "GUI vs board version mismatch",  "Try to update GUI to latest version")
  
};

public ErrorInfo getErrorInfo(int code) {
  if(code > 0) {
    for(int i=0; i<errors.length; i++) {
      if((errors[i].code & code) > 0) {
        return errors[i];
      }
    }
    return new ErrorInfo(0, "UNKNOWN ERROR #" + code, "SEE MANUALS TO CHECK CODE");
  } else {
    return null;
  }
}

ErrorInfo error = null;

/**************************************************/

