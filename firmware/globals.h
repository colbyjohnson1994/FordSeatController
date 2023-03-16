//Use these pin definitions for the ItsyBitsy M0
#define DATAPIN    41
#define CLOCKPIN   40

// There is only one pixel on the board
#define NUMPIXELS 1 

// Seat control definitions
#define READ_FREQ 500 // in ms
#define AVERAGE_SIZE 10 // moving average size

// setpoints in deg C, 
#define HEAT_LEVEL_1_SP 47.0
#define HEAT_LEVEL_2_SP 55.0
#define HEAT_LEVEL_3_SP 62.0

// in deg C
#define HEAT_HYST 2.0

#define HEAT_FAN COOL_LEVEL_1_SP

// setpoints in percent fan duty cycle
#define FAN_OFF         0
#define COOL_LEVEL_1_SP 25
#define COOL_LEVEL_2_SP 65
#define COOL_LEVEL_3_SP 100

// Controller pin definitions
#define RED_LED 13

// dotstar led
Adafruit_DotStar _DotStarLED(NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);

// controller variables
float CSH_RTC_HIST[AVERAGE_SIZE];
float BK_RTC_HIST[AVERAGE_SIZE];

float CSH_RTC_AVG;
float BK_RTC_AVG;