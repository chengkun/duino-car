const int PUL = 6;
const int DIR = 7;
int value = 0;
int testState = true;

#define trigPin 48                                    // Pin 12 trigger output
#define echoPin 21                                     // Pin 2 Echo input
#define onBoardLED 13                                 // Pin 13 onboard LED
#define echo_int 2                                    // Interrupt id for echo pulse

#define TIMER_US 50                                   // 50 uS timer duration 
#define TICK_COUNTS 4000                              // 200 mS worth of timer ticks

volatile long echo_start = 0;                         // Records start of echo pulse 
volatile long echo_end = 0;                           // Records end of echo pulse
volatile long echo_duration = 0;                      // Duration - difference between end and start
volatile int trigger_time_count = 0;                  // Count down counter to trigger pulse time
volatile long range_flasher_counter = 0;              // Count down counter for flashing distance LED

const int led = 13;
const int throttle = 8;
const int switchPin = 9;

String inputString = "";
boolean stringComplete = false;

const int sdCS = 53;
TinyGPS gps;
const char *file = "datalog1.txt";

static void gpsdump(TinyGPS &gps);
static bool feedgps();
static void print_float(float val, float invalid, int len, int prec);
static void print_date(TinyGPS &gps);

TN901 tn;

int soil1 = A0;
int soil2 = A1;
int soil3 = A2;
int soil4 = A8;

float soil11, soil22, soil33, soil44;

U8GLIB_ST7920_128X64_1X dis(49,46,47);
