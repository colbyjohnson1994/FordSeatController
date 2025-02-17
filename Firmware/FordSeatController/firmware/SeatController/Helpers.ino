#include "includes.h"

void initializeInputs() {
  pinMode(HEAT_SW_IN, INPUT);
  pinMode(COOL_SW_IN, INPUT);
  pinMode(CSH_SENS_IN, INPUT);
  pinMode(BK_SENS_IN, INPUT);
}

void initializeDigitalOutputs() {
  pinMode(RED_LED, OUTPUT);
  pinMode(HEAT1_LED, OUTPUT);
  pinMode(HEAT2_LED, OUTPUT);
  pinMode(HEAT3_LED, OUTPUT);
  pinMode(COOL1_LED, OUTPUT);
  pinMode(COOL2_LED, OUTPUT);
  pinMode(COOL3_LED, OUTPUT);

  pinMode(HEAT_COOL_RLY, OUTPUT);

  // everything off
  digitalWrite(RED_LED, LOW);
  digitalWrite(HEAT1_LED, LOW);
  digitalWrite(HEAT2_LED, LOW);
  digitalWrite(HEAT3_LED, LOW);
  digitalWrite(COOL1_LED, LOW);
  digitalWrite(COOL2_LED, LOW);
  digitalWrite(COOL3_LED, LOW);

  digitalWrite(HEAT_COOL_RLY, LOW);
}

void initializeAnalogOutputs() {
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

void ReadFromInputs() {
  // read our two ntc thermistors
  CSH_NTC_AVG = CSH_Smooth_Thermistor->readCelsius();
  BK_NTC_AVG = BK_Smooth_Thermistor->readCelsius();
}

void CheckButtons() {
  static bool coolState = false;
  static bool heatState = false;
  // check cool button
  if (CoolBtn.getValue() > BTN_THRES) {
    if (!coolState) {
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
    }
  } else {
    // reset debounce
    coolState = false;
  }

  // check heat button
  if (HeatBtn.getValue() > BTN_THRES) {
    if (!heatState) {
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
    }
  } else {
    // reset debounce
    heatState = false;
  }
}

void SetLEDOutputs() {
  if (DESIRED_COOL == FAN_OFF) {
    // turn off cool leds
    digitalWrite(COOL1_LED, LOW);
    digitalWrite(COOL2_LED, LOW);
    digitalWrite(COOL3_LED, LOW);
    CSH_BLOWR_PWM = FAN_OFF;
    BK_BLOWR_PWM = FAN_OFF;
  } else if (DESIRED_COOL == COOL_LEVEL_1_SP) {
    // set cool 1 to be on
    digitalWrite(COOL1_LED, HIGH);
    CSH_BLOWR_PWM = COOL_LEVEL_1_FAN;
    BK_BLOWR_PWM = COOL_LEVEL_1_FAN;
  } else if (DESIRED_COOL == COOL_LEVEL_2_SP) {
    // set cool 1 and 2 to be on
    digitalWrite(COOL1_LED, HIGH);
    digitalWrite(COOL2_LED, HIGH);
    CSH_BLOWR_PWM = COOL_LEVEL_2_FAN;
    BK_BLOWR_PWM = COOL_LEVEL_2_FAN;
  } else if (DESIRED_COOL == COOL_LEVEL_3_SP) {
    // set cool 1, 2 and 3 to be on
    digitalWrite(COOL1_LED, HIGH);
    digitalWrite(COOL2_LED, HIGH);
    digitalWrite(COOL3_LED, HIGH);
    CSH_BLOWR_PWM = COOL_LEVEL_3_FAN;
    BK_BLOWR_PWM = COOL_LEVEL_3_FAN;
  }

  if (DESIRED_HEAT == HEAT_OFF) {
    // turn off HEAT leds
    digitalWrite(HEAT1_LED, LOW);
    digitalWrite(HEAT2_LED, LOW);
    digitalWrite(HEAT3_LED, LOW);
    CSH_BLOWR_PWM = FAN_OFF;
    BK_BLOWR_PWM = FAN_OFF;
  } else if (DESIRED_HEAT == HEAT_LEVEL_1_SP) {
    // set HEAT 1 to be on
    digitalWrite(HEAT1_LED, HIGH);
    CSH_BLOWR_PWM = HEAT_LEVEL_1_FAN;
    BK_BLOWR_PWM = HEAT_LEVEL_1_FAN;
  } else if (DESIRED_HEAT == HEAT_LEVEL_2_SP) {
    // set HEAT 1 and 2 to be on
    digitalWrite(HEAT1_LED, HIGH);
    digitalWrite(HEAT2_LED, HIGH);
    CSH_BLOWR_PWM = HEAT_LEVEL_2_FAN;
    BK_BLOWR_PWM = HEAT_LEVEL_2_FAN;
  } else if (DESIRED_HEAT == HEAT_LEVEL_3_SP) {
    // set HEAT 1, 2 and 3 to be on
    digitalWrite(HEAT1_LED, HIGH);
    digitalWrite(HEAT2_LED, HIGH);
    digitalWrite(HEAT3_LED, HIGH);
    CSH_BLOWR_PWM = HEAT_LEVEL_3_FAN;
    BK_BLOWR_PWM = HEAT_LEVEL_3_FAN;
  }
}

void AdjustPWMValues() {
  // based on what state our controller is in, adjust the pwm values
  // relative to our measured temperatures for heat or state for cooling
  if (DESIRED_HEAT != HEAT_OFF) {
    // we are in a heat state
    digitalWrite(HEAT_COOL_RLY, LOW);

    cshPID.Compute();
    bkPID.Compute();

    // values are referenced into floating point variables
    CSH_TED_PWM = (uint8_t)((CSH_TED_PWM_OUT / 255.0) * 100.0);
    BK_TED_PWM = (uint8_t)((BK_TED_PWM_OUT / 255.0) * 100.0);

    if (CSH_TED_PWM > MAX_PWM)
      CSH_TED_PWM = MAX_PWM;
    if (BK_TED_PWM > MAX_PWM)
      BK_TED_PWM = MAX_PWM;
  } else if (DESIRED_COOL != FAN_OFF) {
    digitalWrite(HEAT_COOL_RLY, HIGH);
    // needs to be separate from heat so we can control the fan pwm separately
    CSH_BLOWR_PWM = DESIRED_COOL;
    BK_BLOWR_PWM = DESIRED_COOL;
  } else {
    // set everything to off
    digitalWrite(HEAT_COOL_RLY, LOW);
    CSH_TED_PWM = 0;
    CSH_BLOWR_PWM = 0;
    BK_TED_PWM = 0;
    BK_BLOWR_PWM = 0;
  }
}

void UpdatePWMOutputs() {
  // // temp disable TED
  // CSH_TED_PWM = 0;
  // BK_TED_PWM = 0;

  // cushion ted pwm
  if (_pwm_count < (CSH_TED_PWM / 20.0))
    digitalWrite(CSHTED_CTRL, HIGH);
  else
    digitalWrite(CSHTED_CTRL, LOW);

  // cushion blower pwm
  if (_pwm_count < (CSH_BLOWR_PWM / 20.0))
    digitalWrite(CSHBLWR_CTRL, HIGH);
  else
    digitalWrite(CSHBLWR_CTRL, LOW);

  // cushion ted pwm
  if (_pwm_count < (BK_TED_PWM / 20.0))
    digitalWrite(BKTED_CTRL, HIGH);
  else
    digitalWrite(BKTED_CTRL, LOW);

  // cushion ted pwm
  if (_pwm_count < (BK_BLOWR_PWM / 20.0))
    digitalWrite(BKBLWR_CTRL, HIGH);
  else
    digitalWrite(BKBLWR_CTRL, LOW);

  // increment pwm counter and check for overflow
  _pwm_count++;
  if (_pwm_count >= MAX_CYCLE)
    _pwm_count = 0;
}

void UpdateSoftware() {
  // switch inputs
  Serial.println("DESIRED_HEAT=" + String(DESIRED_HEAT));
  Serial.println("DESIRED_COOL=" + String(DESIRED_COOL));

  // adc inputs
  Serial.println("CSH_NTC_AVG=" + String(CSH_NTC_AVG));
  Serial.println("BK_NTC_AVG=" + String(BK_NTC_AVG));

  // system variables
  Serial.println("CSH_BLOWR_PWM=" + String(CSH_BLOWR_PWM));
  Serial.println("CSH_TED_PWM=" + String(CSH_TED_PWM));
  Serial.println("BK_BLOWR_PWM=" + String(BK_BLOWR_PWM));
  Serial.println("BK_TED_PWM=" + String(BK_TED_PWM));
}