#ifndef GLOBALS
#define GLOBALS

//Use these pin definitions for the ItsyBitsy M0
#define DATAPIN    41
#define CLOCKPIN   40

// There is only one pixel on the board
#define NUMPIXELS 1 

// NTC definitions
#define REFERENCE_RESISTANCE   43000
#define NOMINAL_RESISTANCE     1000
#define NOMINAL_TEMPERATURE    25
#define B_VALUE                3950

// pwm definitions
#define MAX_PWM 100
#define MIN_PWM 0
#define MAX_CYCLE 5

// Seat control definitions
#define READ_FREQ 100 // in ms
#define CONTROL_FREQ 1000 // in milli seconds
#define SOFTWARE_FREQ 500 // in ms
#define BUTTON_FREQ 100 // in ms
#define SMOOTHING_FACTOR 10 // moving average size
#define PWM_FREQ 100.0 // in hertz
#define PWM_INTERVAL (uint8_t)(1000.0 / PWM_FREQ)
#define BTN_THRES 150 // in ADC ticks
#define PID_THRES 5  // in degrees C, this difference triggers change in PID sensitivy

// setpoints in deg C, 
#define HEAT_OFF        0.0
#define HEAT_LEVEL_1_SP 47.0
#define HEAT_LEVEL_2_SP 55.0
#define HEAT_LEVEL_3_SP 62.0

#define COOL_LEVEL_1_SP 25.0
#define COOL_LEVEL_2_SP 20.0
#define COOL_LEVEL_3_SP 15.0

#define FAN_OFF           0.0
#define HEAT_LEVEL_1_FAN  40.0
#define HEAT_LEVEL_2_FAN  75.0
#define HEAT_LEVEL_3_FAN  100.0

#define COOL_LEVEL_1_FAN  40.0
#define COOL_LEVEL_2_FAN  75.0
#define COOL_LEVEL_3_FAN  100.0

#define SHUTDOWN_HT_OFF   70.0
#define SHUTDOWN_HT_ON    65.0
#define SHUTDOWN_LT_OFF   -30.0
#define SHUTDOWN_LT_ON    -25.0

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

// Relay Outputs
#define HEAT_COOL_RLY 12


// dotstar led
Adafruit_DotStar _DotStarLED(NUMPIXELS, DATAPIN, CLOCKPIN, DOTSTAR_BRG);

// controller variables
unsigned long _sensor_seconds = 0;
unsigned long _control_seconds = 0;
unsigned long _software_seconds = 0;
unsigned long _button_seconds = 0;

unsigned long _pwm_seconds = 0;
unsigned long _pwm_count = 0;

// PID variables
double CSH_NTC_AVG;
double BK_NTC_AVG;

double CSH_TED_PWM_OUT = 0.0;
double BK_TED_PWM_OUT = 0.0;

uint8_t CSH_TED_PWM = 0;
uint8_t BK_TED_PWM = 0;
uint8_t CSH_BLOWR_PWM = 0;
uint8_t BK_BLOWR_PWM = 0;

double DESIRED_HEAT = HEAT_OFF;
double DESIRED_COOL = FAN_OFF;

double SetPoint = 0.0;  // Shared setpoint for PID

bool SHUTDOWN_HT_CUSH_ACTIVE = false;
bool SHUTDOWN_HT_BACK_ACTIVE = false;
bool SHUTDOWN_LT_CUSH_ACTIVE = false;
bool SHUTDOWN_LT_BACK_ACTIVE = false;

double _aggKp = 15.0, _aggKi = 10.0, _aggKd = 0.0;
PID cshPID(&CSH_NTC_AVG, &CSH_TED_PWM_OUT, &SetPoint, _aggKp, _aggKi, _aggKd, DIRECT);
PID bkPID(&BK_NTC_AVG, &BK_TED_PWM_OUT, &SetPoint, _aggKp, _aggKi, _aggKd, DIRECT);


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

#endif