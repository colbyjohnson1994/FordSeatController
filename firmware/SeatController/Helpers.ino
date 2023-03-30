#include "includes.h"

void initializeInputs()
{
  pinMode(HEAT_SW_IN, INPUT);
  pinMode(COOL_SW_IN, INPUT);
  pinMode(CSH_SENS_IN, INPUT);
  pinMode(BK_SENS_IN, INPUT);
}

void initializeDigitalOutputs()
{
  pinMode(RED_LED, OUTPUT);
  pinMode(HEAT1_LED, OUTPUT);
  pinMode(HEAT2_LED, OUTPUT);
  pinMode(HEAT3_LED, OUTPUT);
  pinMode(COOL1_LED, OUTPUT);
  pinMode(COOL2_LED, OUTPUT);
  pinMode(COOL3_LED, OUTPUT);

  // everything off
  digitalWrite(RED_LED, LOW);
  digitalWrite(HEAT1_LED, LOW);
  digitalWrite(HEAT2_LED, LOW);
  digitalWrite(HEAT3_LED, LOW);
  digitalWrite(COOL1_LED, LOW);
  digitalWrite(COOL2_LED, LOW);
  digitalWrite(COOL3_LED, LOW);
}

void initializeAnalogOutputs()
{
  pinMode(CSHBLWR_CTRL, OUTPUT);
  pinMode(CSHTED_CTRL, OUTPUT);
  pinMode(BKBLWR_CTRL, OUTPUT);
  pinMode(BKTED_CTRL, OUTPUT);

  // everything off
  digitalWrite(CSHBLWR_CTRL, LOW);
  digitalWrite(CSHTED_CTRL, LOW);
  digitalWrite(BKBLWR_CTRL, LOW);
  digitalWrite(BKTED_CTRL, LOW);
}

void ReadFromInputs()
{
  // read our two ntc thermistors
  CSH_NTC_AVG = CSH_Smooth_Thermistor->readCelsius();
  BK_NTC_AVG = BK_Smooth_Thermistor->readCelsius();
}

void CheckButtons()
{
  static bool coolState = false;
  static bool heatState = false;
  // check cool button
  if (CoolBtn.getValue() > BTN_THRES)
  {
    if (!coolState)
    {
      coolState = true;
      DESIRED_HEAT = HEAT_OFF;
      
      if (DESIRED_COOL == FAN_OFF)
        // advance to cool stage 1
        DESIRED_COOL = COOL_LEVEL_1_SP;
      else if (DESIRED_COOL == COOL_LEVEL_1_SP)
        // advanced to cool stage 2
        DESIRED_COOL = COOL_LEVEL_2_SP;
      else if (DESIRED_COOL == COOL_LEVEL_2_SP)
        // advance to cool stage 3
        DESIRED_COOL = COOL_LEVEL_3_SP;
      else if (DESIRED_COOL == COOL_LEVEL_3_SP)
        // turn off cooling
        DESIRED_COOL = FAN_OFF;

      SetLEDOutputs();
    }
  }
  else
  {
    // reset debounce
    coolState = false;
  }

  // check heat button
  if (HeatBtn.getValue() > BTN_THRES)
  {
    if (!heatState)
    {
      heatState = true;
      DESIRED_COOL = FAN_OFF;
      
      if (DESIRED_HEAT == HEAT_OFF)
        // advance to cool stage 1
        DESIRED_HEAT = HEAT_LEVEL_1_SP;
      else if (DESIRED_HEAT == HEAT_LEVEL_1_SP)
        // advanced to cool stage 2
        DESIRED_HEAT = HEAT_LEVEL_2_SP;
      else if (DESIRED_HEAT == HEAT_LEVEL_2_SP)
        // advance to cool stage 3
        DESIRED_HEAT = HEAT_LEVEL_3_SP;
      else if (DESIRED_HEAT == HEAT_LEVEL_3_SP)
        // turn off cooling
        DESIRED_HEAT = HEAT_OFF;

      SetLEDOutputs();
    }
  }
  else
  {
    // reset debounce
    heatState = false;
  }
}

void SetLEDOutputs()
{
  if (DESIRED_COOL == FAN_OFF)
  {
    // turn off cool leds
    digitalWrite(COOL1_LED, LOW);
    digitalWrite(COOL2_LED, LOW);
    digitalWrite(COOL3_LED, LOW);
  }
  else if (DESIRED_COOL == COOL_LEVEL_1_SP)
  {
    // set cool 1 to be on
    digitalWrite(COOL1_LED, LOW);
  }
  else if (DESIRED_COOL == COOL_LEVEL_2_SP)
  {
    // set cool 1 and 2 to be on
    digitalWrite(COOL2_LED, LOW);
  }
  else if (DESIRED_COOL == COOL_LEVEL_3_SP)
  {  
    // set cool 1, 2 and 3 to be on
    digitalWrite(COOL3_LED, LOW);
  }

  if (DESIRED_HEAT == HEAT_OFF)
  {
    // turn off HEAT leds
    digitalWrite(HEAT1_LED, LOW);
    digitalWrite(HEAT2_LED, LOW);
    digitalWrite(HEAT3_LED, LOW);
  }
  else if (DESIRED_HEAT == HEAT_LEVEL_1_SP)
  {
    // set HEAT 1 to be on
    digitalWrite(HEAT1_LED, LOW);
  }
  else if (DESIRED_HEAT == HEAT_LEVEL_2_SP)
  {
    // set HEAT 1 and 2 to be on
    digitalWrite(HEAT2_LED, LOW);
  }
  else if (DESIRED_HEAT == HEAT_LEVEL_3_SP)
  {  
    // set HEAT 1, 2 and 3 to be on
    digitalWrite(HEAT3_LED, LOW);
  }
}

void AdjustPWMValues()
{
  // based on what state our controller is in, adjust the pwm values
  // relative to our measured temperatures for heat or state for cooling
  if (DESIRED_HEAT != HEAT_OFF)
  {
    // we are in a heat state

    // set the fan to a constant
    CSH_BLOWR_PWM = COOL_LEVEL_2_SP;
    BK_BLOWR_PWM = COOL_LEVEL_2_SP;

    // calculate the differential between our desired temperature and our current
    float csh_diff, bk_diff;
    csh_diff = DESIRED_HEAT - CSH_NTC_AVG;
    bk_diff = DESIRED_HEAT - BK_NTC_AVG;

    // calculate the desired PWM using a proportional formula
    CSH_TED_PWM = CSH_TED_PWM + (int)(_KP * (csh_diff/DESIRED_HEAT));
    if (CSH_TED_PWM > MAX_PWM)
      CSH_TED_PWM = MAX_PWM;
    else if (CSH_TED_PWM < MIN_PWM)
      CSH_TED_PWM = MIN_PWM;

    BK_TED_PWM = BK_TED_PWM + (int)(_KP * (bk_diff/DESIRED_HEAT));
    if (BK_TED_PWM > MAX_PWM)
      BK_TED_PWM = MAX_PWM;
    else if (BK_TED_PWM < MIN_PWM)
      BK_TED_PWM = MIN_PWM;
  }
  else if (DESIRED_COOL != FAN_OFF)
  {
    // needs to be separate from heat so we can control the fan pwm separately
    CSH_BLOWR_PWM = DESIRED_COOL;
    BK_BLOWR_PWM = DESIRED_COOL;
  }
  else
  {
    // set everything to off
    CSH_TED_PWM = 0;
    CSH_BLOWR_PWM = 0;
    BK_TED_PWM = 0;
    BK_BLOWR_PWM = 0;
  }

  // set the outputs
  analogWrite(CSHBLWR_CTRL, CSH_BLOWR_PWM);
  analogWrite(CSHTED_CTRL, CSH_TED_PWM);
  analogWrite(BKBLWR_CTRL, BK_BLOWR_PWM);
  analogWrite(BKTED_CTRL, BK_TED_PWM);
}