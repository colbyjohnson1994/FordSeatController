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

// Maximum runtime before dropping to level 1 (in milliseconds)
// 60 minutes = 3,600,000 ms
#define MAX_MODE_RUNTIME_MS   3600000UL
// Time when current mode started
unsigned long modeStartTime = 0;

#define READ_FREQ 100 // in ms
#define COOLDOWN_TIMER  5000  // in milli seconds
#define CONTROL_FREQ 1000 // in milli seconds
#define SOFTWARE_FREQ 250 // in ms
#define BUTTON_FREQ 100 // in ms
#define SMOOTHING_FACTOR 10 // moving average size
#define PWM_FREQ 100.0 // in hertz
#define PWM_INTERVAL (uint8_t)(1000.0 / PWM_FREQ)
#define BTN_THRES 150 // in ADC ticks
#define PID_THRES 5  // in degrees C, this difference triggers change in PID sensitivy

// setpoints in deg C, 
#define HEAT_OFF        0.0
#define HEAT_LEVEL_1_SP 30.0
#define HEAT_LEVEL_2_SP 40.0
#define HEAT_LEVEL_3_SP 50.0

#define COOL_LEVEL_1_SP 22.0
#define COOL_LEVEL_2_SP 18.0
#define COOL_LEVEL_3_SP 12.0

#define FAN_OFF           0.0

// Fan speed limits per heating level (in %)
#define HEAT_L1_FAN_MIN   10.0
#define HEAT_L1_FAN_MAX   30.0   // low max for level 1 to avoid over-cooling

#define HEAT_L2_FAN_MIN   30.0
#define HEAT_L2_FAN_MAX   50.0

#define HEAT_L3_FAN_MIN   50.0
#define HEAT_L3_FAN_MAX  100.0   // full range at max heat

// Fan speed limits per cooling level (in %)
#define COOL_L1_FAN_MIN   10.0
#define COOL_L1_FAN_MAX   30.0   // moderate max for gentle cooling

#define COOL_L2_FAN_MIN   30.0
#define COOL_L2_FAN_MAX   50.0

#define COOL_L3_FAN_MIN   50.0
#define COOL_L3_FAN_MAX  100.0   // max fan for aggressive cooling

#define SHUTDOWN_HT_OFF   70.0
#define SHUTDOWN_HT_ON    65.0
#define SHUTDOWN_LT_OFF   10.0
#define SHUTDOWN_LT_ON    15.0
#define SHUTDOWN_FAN_PERC 50.0

// Fan control constants
#define FAN_MIN_HEAT      10.0    // Minimum fan % in heating mode
#define FAN_MIN_COOL      10.0    // Minimum fan % in cooling mode

#define FAN_BIAS_OFFSET 5.0   //default

#define HEAT_BIAS_L1   10.0   // Stronger bias at low heat → fan starts ramping earlier
#define HEAT_BIAS_L2    7.0
#define HEAT_BIAS_L3    4.0   // Less bias at max heat

#define COOL_BIAS_L1    4.0
#define COOL_BIAS_L2    7.0
#define COOL_BIAS_L3   12.0

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
unsigned long _cooldown_seconds = 0;

unsigned long _pwm_seconds = 0;
unsigned long _pwm_count = 0;

// PID variables
double CSH_NTC_AVG;
double BK_NTC_AVG;

double CSH_TED_PWM_OUT = 0.0;
double BK_TED_PWM_OUT = 0.0;

// Fan PID outputs - MUST be declared BEFORE the PID constructors
double CSH_FAN_PWM_OUT = 0.0;
double BK_FAN_PWM_OUT = 0.0;

uint8_t CSH_TED_PWM = 0;
uint8_t BK_TED_PWM = 0;
uint8_t CSH_FAN_PWM = 0;
uint8_t BK_FAN_PWM = 0;

// In heating: we want fan to increase as actual temp approaches setpoint
// → Invert the process variable for fan PID
double CSH_Inverted_Temp = 0.0;
double BK_Inverted_Temp  = 0.0;

double DESIRED_HEAT = HEAT_OFF;
double DESIRED_COOL = FAN_OFF;

double SetPoint = 0.0;      // Shared setpoint for TED PIDs
double FanSetPoint = 0.0;   // Dedicated setpoint for fan PIDs (allows independent biasing)

bool SHUTDOWN_HT_CUSH_ACTIVE = false;
bool SHUTDOWN_HT_BACK_ACTIVE = false;
bool SHUTDOWN_LT_CUSH_ACTIVE = false;
bool SHUTDOWN_LT_BACK_ACTIVE = false;
bool COOLDOWN_ACTIVE = false;

double _aggKp = 15.0, _aggKi = 10.0, _aggKd = 0.0;
PID cshPID(&CSH_NTC_AVG, &CSH_TED_PWM_OUT, &SetPoint, _aggKp, _aggKi, _aggKd, DIRECT);
PID bkPID(&BK_NTC_AVG, &BK_TED_PWM_OUT, &SetPoint, _aggKp, _aggKi, _aggKd, DIRECT);

double _fanKp = 30.0, _fanKi = 10.0, _fanKd = 0.0;

// Temporary variables for fan PID inputs (allows us to feed inverted/normal values)
double CSH_Fan_PID_Input = 0.0;
double BK_Fan_PID_Input  = 0.0;

// Fan PIDs now use temporary input variables (we'll assign inverted or normal temp before Compute)
PID cshFanPID(&CSH_Fan_PID_Input, &CSH_FAN_PWM_OUT, &FanSetPoint, _fanKp, _fanKi, _fanKd, DIRECT);
PID bkFanPID(&BK_Fan_PID_Input, &BK_FAN_PWM_OUT, &FanSetPoint, _fanKp, _fanKi, _fanKd, DIRECT);


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