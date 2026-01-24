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

void CheckTemperatureLimits() {
  // check if we are above limits
  if (CSH_NTC_AVG > SHUTDOWN_HT_OFF) {
    SHUTDOWN_HT_CUSH_ACTIVE = true;
  } else {
    if (SHUTDOWN_HT_CUSH_ACTIVE && CSH_NTC_AVG < SHUTDOWN_HT_ON) {
      SHUTDOWN_HT_CUSH_ACTIVE = false;
    }
  }

  if (BK_NTC_AVG > SHUTDOWN_HT_OFF) {
    SHUTDOWN_HT_BACK_ACTIVE = true;
  } else {
    if (SHUTDOWN_HT_BACK_ACTIVE && BK_NTC_AVG < SHUTDOWN_HT_ON) {
      SHUTDOWN_HT_BACK_ACTIVE = false;
    }
  }

  if (CSH_NTC_AVG < SHUTDOWN_LT_OFF) {
    SHUTDOWN_LT_CUSH_ACTIVE = true;
  } else {
    if (SHUTDOWN_LT_CUSH_ACTIVE && CSH_NTC_AVG > SHUTDOWN_LT_ON) {
      SHUTDOWN_LT_CUSH_ACTIVE = false;
    }
  }

  if (BK_NTC_AVG < SHUTDOWN_LT_OFF) {
    SHUTDOWN_LT_BACK_ACTIVE = true;
  } else {
    if (SHUTDOWN_LT_BACK_ACTIVE && BK_NTC_AVG > SHUTDOWN_LT_ON) {
      SHUTDOWN_LT_BACK_ACTIVE = false;
    }
  }
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
        // advance to heat stage 1
        DESIRED_HEAT = HEAT_LEVEL_1_SP;
      else if (DESIRED_HEAT == HEAT_LEVEL_1_SP)
        // advance to heat stage 2
        DESIRED_HEAT = HEAT_LEVEL_2_SP;
      else if (DESIRED_HEAT == HEAT_LEVEL_2_SP)
        // advance to heat stage 3
        DESIRED_HEAT = HEAT_LEVEL_3_SP;
      else if (DESIRED_HEAT == HEAT_LEVEL_3_SP)
        // turn off heating
        DESIRED_HEAT = HEAT_OFF;
    }
  } else {
    // reset debounce
    heatState = false;
  }
}

void SetLEDOutputs() {
  // LEDs indicate requested level (fan now dynamic)
  if (DESIRED_COOL == FAN_OFF) {
    digitalWrite(COOL1_LED, LOW);
    digitalWrite(COOL2_LED, LOW);
    digitalWrite(COOL3_LED, LOW);
  } else if (DESIRED_COOL == COOL_LEVEL_1_SP) {
    digitalWrite(COOL1_LED, HIGH);
  } else if (DESIRED_COOL == COOL_LEVEL_2_SP) {
    digitalWrite(COOL1_LED, HIGH);
    digitalWrite(COOL2_LED, HIGH);
  } else if (DESIRED_COOL == COOL_LEVEL_3_SP) {
    digitalWrite(COOL1_LED, HIGH);
    digitalWrite(COOL2_LED, HIGH);
    digitalWrite(COOL3_LED, HIGH);
  }

  if (DESIRED_HEAT == HEAT_OFF) {
    digitalWrite(HEAT1_LED, LOW);
    digitalWrite(HEAT2_LED, LOW);
    digitalWrite(HEAT3_LED, LOW);
  } else if (DESIRED_HEAT == HEAT_LEVEL_1_SP) {
    digitalWrite(HEAT1_LED, HIGH);
  } else if (DESIRED_HEAT == HEAT_LEVEL_2_SP) {
    digitalWrite(HEAT1_LED, HIGH);
    digitalWrite(HEAT2_LED, HIGH);
  } else if (DESIRED_HEAT == HEAT_LEVEL_3_SP) {
    digitalWrite(HEAT1_LED, HIGH);
    digitalWrite(HEAT2_LED, HIGH);
    digitalWrite(HEAT3_LED, HIGH);
  }
}

void AdjustPWMValues() {
  double fanSetpoint = SetPoint;

  if (DESIRED_HEAT != HEAT_OFF) {
    // Heat mode
    digitalWrite(HEAT_COOL_RLY, LOW);

    SetPoint = DESIRED_HEAT;
    fanSetpoint = DESIRED_HEAT + FAN_BIAS_OFFSET;  // Bias higher → encourages more fan when close

    // TED PID - DIRECT
    cshPID.SetControllerDirection(DIRECT);
    bkPID.SetControllerDirection(DIRECT);
    cshPID.Compute();
    bkPID.Compute();

    CSH_TED_PWM = (uint8_t)((CSH_TED_PWM_OUT / 255.0) * 100.0);
    BK_TED_PWM  = (uint8_t)((BK_TED_PWM_OUT  / 255.0) * 100.0);
    if (CSH_TED_PWM > MAX_PWM) CSH_TED_PWM = MAX_PWM;
    if (BK_TED_PWM  > MAX_PWM) BK_TED_PWM  = MAX_PWM;

    // Fan PID - REVERSE (lower fan when far from setpoint → max TEC heating effect)
    cshFanPID.SetControllerDirection(REVERSE);
    bkFanPID.SetControllerDirection(REVERSE);
    cshFanPID.Setpoint = fanSetpoint;
    bkFanPID.Setpoint = fanSetpoint;
    cshFanPID.Compute();
    bkFanPID.Compute();

    CSH_FAN_PWM = (uint8_t)((CSH_FAN_PWM_OUT / 255.0) * 100.0);
    BK_FAN_PWM  = (uint8_t)((BK_FAN_PWM_OUT  / 255.0) * 100.0);

    // Enforce minimum fan PWM and cap at 100%
    if (CSH_FAN_PWM < FAN_MIN_HEAT) CSH_FAN_PWM = FAN_MIN_HEAT;
    if (BK_FAN_PWM  < FAN_MIN_HEAT) BK_FAN_PWM  = FAN_MIN_HEAT;
    if (CSH_FAN_PWM > 100) CSH_FAN_PWM = 100;
    if (BK_FAN_PWM  > 100) BK_FAN_PWM  = 100;

    // Shutdowns
    if (SHUTDOWN_HT_CUSH_ACTIVE || SHUTDOWN_LT_CUSH_ACTIVE) CSH_TED_PWM = 0;
    if (SHUTDOWN_HT_BACK_ACTIVE || SHUTDOWN_LT_BACK_ACTIVE) BK_TED_PWM  = 0;

  } else if (DESIRED_COOL != FAN_OFF) {
    // Cool mode
    digitalWrite(HEAT_COOL_RLY, HIGH);

    SetPoint = DESIRED_COOL;
    fanSetpoint = DESIRED_COOL - FAN_BIAS_OFFSET;  // Bias lower → encourages more fan when close

    // TED PID - REVERSE
    cshPID.SetControllerDirection(REVERSE);
    bkPID.SetControllerDirection(REVERSE);
    cshPID.Compute();
    bkPID.Compute();

    CSH_TED_PWM = (uint8_t)((CSH_TED_PWM_OUT / 255.0) * 100.0);
    BK_TED_PWM  = (uint8_t)((BK_TED_PWM_OUT  / 255.0) * 100.0);
    if (CSH_TED_PWM > MAX_PWM) CSH_TED_PWM = MAX_PWM;
    if (BK_TED_PWM  > MAX_PWM) BK_TED_PWM  = MAX_PWM;

    // Fan PID - REVERSE (lower fan when far from setpoint → max TEC cooling effect)
    cshFanPID.SetControllerDirection(REVERSE);
    bkFanPID.SetControllerDirection(REVERSE);
    cshFanPID.Setpoint = fanSetpoint;
    bkFanPID.Setpoint = fanSetpoint;
    cshFanPID.Compute();
    bkFanPID.Compute();

    CSH_FAN_PWM = (uint8_t)((CSH_FAN_PWM_OUT / 255.0) * 100.0);
    BK_FAN_PWM  = (uint8_t)((BK_FAN_PWM_OUT  / 255.0) * 100.0);

    // Enforce minimum fan PWM and cap at 100%
    if (CSH_FAN_PWM < FAN_MIN_COOL) CSH_FAN_PWM = FAN_MIN_COOL;
    if (BK_FAN_PWM  < FAN_MIN_COOL) BK_FAN_PWM  = FAN_MIN_COOL;
    if (CSH_FAN_PWM > 100) CSH_FAN_PWM = 100;
    if (BK_FAN_PWM  > 100) BK_FAN_PWM  = 100;

    // Shutdowns
    if (SHUTDOWN_HT_CUSH_ACTIVE || SHUTDOWN_LT_CUSH_ACTIVE) CSH_TED_PWM = 0;
    if (SHUTDOWN_HT_BACK_ACTIVE || SHUTDOWN_LT_BACK_ACTIVE) BK_TED_PWM  = 0;

  } else {
    // Off
    digitalWrite(HEAT_COOL_RLY, LOW);
    CSH_TED_PWM = 0;
    BK_TED_PWM  = 0;
    CSH_FAN_PWM = 0;
    BK_FAN_PWM  = 0;
  }
}

void UpdatePWMOutputs() {
  // cushion ted pwm
  if (_pwm_count < (CSH_TED_PWM / 20.0))
    digitalWrite(CSHTED_CTRL, HIGH);
  else
    digitalWrite(CSHTED_CTRL, LOW);

  // cushion blower pwm
  if (_pwm_count < (CSH_FAN_PWM / 20.0))
    digitalWrite(CSHBLWR_CTRL, HIGH);
  else
    digitalWrite(CSHBLWR_CTRL, LOW);

  // back ted pwm
  if (_pwm_count < (BK_TED_PWM / 20.0))
    digitalWrite(BKTED_CTRL, HIGH);
  else
    digitalWrite(BKTED_CTRL, LOW);

  // back blower pwm
  if (_pwm_count < (BK_FAN_PWM / 20.0))
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
  Serial.println("CSH_BLOWR_PWM=" + String(CSH_FAN_PWM));
  Serial.println("CSH_TED_PWM=" + String(CSH_TED_PWM));
  Serial.println("BK_BLOWR_PWM=" + String(BK_FAN_PWM));
  Serial.println("BK_TED_PWM=" + String(BK_TED_PWM));
  Serial.println("SHUTDOWN_HT_CUSH=" + String(SHUTDOWN_HT_CUSH_ACTIVE));
  Serial.println("SHUTDOWN_HT_BACK=" + String(SHUTDOWN_HT_BACK_ACTIVE));
  Serial.println("SHUTDOWN_LT_CUSH=" + String(SHUTDOWN_LT_CUSH_ACTIVE));
  Serial.println("SHUTDOWN_LT_BACK=" + String(SHUTDOWN_LT_BACK_ACTIVE));
}