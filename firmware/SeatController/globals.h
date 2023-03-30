#ifndef GLOBALS
#define GLOBALS

//Use these pin definitions for the ItsyBitsy M0
#define DATAPIN    41
#define CLOCKPIN   40

// There is only one pixel on the board
#define NUMPIXELS 1 

// NTC definitions
#define REFERENCE_RESISTANCE   10000
#define NOMINAL_RESISTANCE     10000
#define NOMINAL_TEMPERATURE    25
#define B_VALUE                3950

// pwm definitions
#define MAX_PWM 200
#define MIN_PWM 10

// Seat control definitions
#define READ_FREQ 100 // in ms
#define CONTROL_FREQ 1000 // in milli seconds
#define SMOOTHING_FACTOR 10 // moving average size
#define PWM_FREQ 200 // in hertz
#define BTN_THRES 150 // in ADC ticks

// setpoints in deg C, 
#define HEAT_OFF        0.0
#define HEAT_LEVEL_1_SP 47.0
#define HEAT_LEVEL_2_SP 55.0
#define HEAT_LEVEL_3_SP 62.0

// setpoints in percent fan duty cycle
#define FAN_OFF         0
#define COOL_LEVEL_1_SP 25
#define COOL_LEVEL_2_SP 65
#define COOL_LEVEL_3_SP 100

// Controller pin definitions
// Analog Inputs
#define HEAT_SW_IN  A0
#define COOL_SW_IN  A1
#define CSH_SENS_IN A2
#define BK_SENS_IN  A3

// Digital Outputs
#define RED_LED     13
#define HEAT1_LED   A4
#define HEAT2_LED   A5
#define HEAT3_LED   7
#define COOL1_LED   4
#define COOL2_LED   2
#define COOL3_LED   3

// Analog Outputs
#define CSHBLWR_CTRL  5
#define CSHTED_CTRL   10
#define BKBLWR_CTRL   9
#define BKTED_CTRL    11


// dotstar led
Adafruit_DotStar _DotStarLED(NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);

// controller variables
unsigned long _sensor_seconds = 0;
unsigned long _control_seconds = 0;

// PID variables
float _KP = 1.0;
uint8_t CSH_TED_PWM = 0;
uint8_t CSH_BLOWR_PWM = 0;
uint8_t BK_TED_PWM = 0;
uint8_t BK_BLOWR_PWM = 0;

float DESIRED_HEAT = HEAT_OFF;
float DESIRED_COOL = FAN_OFF;

// NTC Thermistor Variables
Thermistor* CSH_Thermistor = new NTC_Thermistor(
  CSH_SENS_IN,
  REFERENCE_RESISTANCE,
  NOMINAL_RESISTANCE,
  NOMINAL_TEMPERATURE,
  B_VALUE
);

Thermistor* CSH_Smooth_Thermistor = new SmoothThermistor(CSH_Thermistor, SMOOTHING_FACTOR);

Thermistor* BK_Thermistor = new NTC_Thermistor(
  BK_SENS_IN,
  REFERENCE_RESISTANCE,
  NOMINAL_RESISTANCE,
  NOMINAL_TEMPERATURE,
  B_VALUE
);

Thermistor* BK_Smooth_Thermistor = new SmoothThermistor(BK_Thermistor, SMOOTHING_FACTOR);

// Button Variables
ResponsiveAnalogRead HeatBtn(HEAT_SW_IN, false);
ResponsiveAnalogRead CoolBtn(COOL_SW_IN, false);

float CSH_NTC_AVG;
float BK_NTC_AVG;

#endif