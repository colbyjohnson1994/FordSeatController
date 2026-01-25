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
      else if (DESIRED_COOL == COOL_LEVEL_3_SP) {
        // turn off cooling
        DESIRED_COOL = FAN_OFF;

        // enable cooldown
        _cooldown_seconds = millis();
        COOLDOWN_ACTIVE = true;
      }
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
      else if (DESIRED_HEAT == HEAT_LEVEL_3_SP) {
        // turn off heating
        DESIRED_HEAT = HEAT_OFF;

        // enable cooldown
        _cooldown_seconds = millis();
        COOLDOWN_ACTIVE = true;
      }
    }
  } else {
    // reset debounce
    heatState = false;
  }
}

void SetLEDOutputs() {
  // LEDs indicate requested level (fan is now dynamic)
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
  // Track mode runtime and drop to level 1 if timeout reached
  bool isActiveMode = (DESIRED_HEAT != HEAT_OFF) || (DESIRED_COOL != FAN_OFF);

  if (isActiveMode) {
    if (modeStartTime == 0) {
      modeStartTime = millis();  // Start counting when mode becomes active
    }

    if (millis() - modeStartTime > MAX_MODE_RUNTIME_MS) {
      // Timeout reached → drop to level 1
      if (DESIRED_HEAT != HEAT_OFF) {
        DESIRED_HEAT = HEAT_LEVEL_1_SP;
      } else if (DESIRED_COOL != FAN_OFF) {
        DESIRED_COOL = COOL_LEVEL_1_SP;
      }

      modeStartTime = millis();  // Reset timer so it doesn't immediately trigger again
      // Optional: flash RED_LED or send message via Serial
      Serial.println("Mode timeout reached - dropped to level 1");
    }
  } else {
    // Mode is OFF → reset timer
    modeStartTime = 0;
  }

  if (DESIRED_HEAT != HEAT_OFF) {
    digitalWrite(HEAT_COOL_RLY, LOW);

    SetPoint = DESIRED_HEAT;  // TED setpoint

    // Calculate inverted temperature for fan PID
    // (higher actual temp → higher inverted value → PID sees "closer to target")
    double CSH_Inverted_Temp = 100.0 - CSH_NTC_AVG;  // 100 is arbitrary (higher than any possible temp)
    double BK_Inverted_Temp = 100.0 - BK_NTC_AVG;

    // Adjustable bias per level
    float heatBias = FAN_BIAS_OFFSET;
    if (DESIRED_HEAT == HEAT_LEVEL_1_SP) heatBias = HEAT_BIAS_L1;
    else if (DESIRED_HEAT == HEAT_LEVEL_2_SP) heatBias = HEAT_BIAS_L2;
    else if (DESIRED_HEAT == HEAT_LEVEL_3_SP) heatBias = HEAT_BIAS_L3;

    // FanSetPoint should be higher than inverted temps when close to setpoint
    FanSetPoint = 100.0 - (DESIRED_HEAT - heatBias);

    // TED PID - DIRECT
    cshPID.SetControllerDirection(DIRECT);
    bkPID.SetControllerDirection(DIRECT);
    cshPID.Compute();
    bkPID.Compute();

    CSH_TED_PWM = (uint8_t)((CSH_TED_PWM_OUT / 255.0) * 100.0);
    BK_TED_PWM = (uint8_t)((BK_TED_PWM_OUT / 255.0) * 100.0);
    if (CSH_TED_PWM > MAX_PWM) CSH_TED_PWM = MAX_PWM;
    if (BK_TED_PWM > MAX_PWM) BK_TED_PWM = MAX_PWM;

    // Fan PID - DIRECT, using inverted temp
    cshFanPID.SetControllerDirection(DIRECT);
    bkFanPID.SetControllerDirection(DIRECT);

    // Feed inverted temperature to fan PID inputs
    CSH_Fan_PID_Input = CSH_Inverted_Temp;
    BK_Fan_PID_Input = BK_Inverted_Temp;

    cshFanPID.Compute();
    bkFanPID.Compute();

    CSH_FAN_PWM = (uint8_t)((CSH_FAN_PWM_OUT / 255.0) * 100.0);
    BK_FAN_PWM = (uint8_t)((BK_FAN_PWM_OUT / 255.0) * 100.0);

    // Enforce per-level fan speed limits
    float fanMinHeat = FAN_MIN_HEAT;  // fallback
    float fanMaxHeat = 100.0;

    if (DESIRED_HEAT == HEAT_LEVEL_1_SP) {
      fanMinHeat = HEAT_L1_FAN_MIN;
      fanMaxHeat = HEAT_L1_FAN_MAX;
    } else if (DESIRED_HEAT == HEAT_LEVEL_2_SP) {
      fanMinHeat = HEAT_L2_FAN_MIN;
      fanMaxHeat = HEAT_L2_FAN_MAX;
    } else if (DESIRED_HEAT == HEAT_LEVEL_3_SP) {
      fanMinHeat = HEAT_L3_FAN_MIN;
      fanMaxHeat = HEAT_L3_FAN_MAX;
    }

    if (CSH_FAN_PWM < fanMinHeat) CSH_FAN_PWM = (uint8_t)fanMinHeat;
    if (BK_FAN_PWM < fanMinHeat) BK_FAN_PWM = (uint8_t)fanMinHeat;
    if (CSH_FAN_PWM > fanMaxHeat) CSH_FAN_PWM = (uint8_t)fanMaxHeat;
    if (BK_FAN_PWM > fanMaxHeat) BK_FAN_PWM = (uint8_t)fanMaxHeat;

    // Shutdowns
    if (SHUTDOWN_HT_CUSH_ACTIVE || SHUTDOWN_LT_CUSH_ACTIVE) {
      CSH_TED_PWM = 0;
      CSH_FAN_PWM = SHUTDOWN_FAN_PERC;
    }
    if (SHUTDOWN_HT_BACK_ACTIVE || SHUTDOWN_LT_BACK_ACTIVE) {
      BK_TED_PWM = 0;
      BK_FAN_PWM = SHUTDOWN_FAN_PERC;
    }
  } else if (DESIRED_COOL != FAN_OFF) {
    // Cool mode
    digitalWrite(HEAT_COOL_RLY, HIGH);

    SetPoint = DESIRED_COOL;  // TED setpoint

    // Adjustable bias per cooling level
    float coolBias = FAN_BIAS_OFFSET;
    if (DESIRED_COOL == COOL_LEVEL_1_SP) coolBias = COOL_BIAS_L1;
    else if (DESIRED_COOL == COOL_LEVEL_2_SP) coolBias = COOL_BIAS_L2;
    else if (DESIRED_COOL == COOL_LEVEL_3_SP) coolBias = COOL_BIAS_L3;

    // Fan setpoint: bias LOWER than desired cool temp → more fan when far above setpoint
    FanSetPoint = DESIRED_COOL - coolBias;

    // TED PID - REVERSE (decrease power when too hot)
    cshPID.SetControllerDirection(REVERSE);
    bkPID.SetControllerDirection(REVERSE);
    cshPID.Compute();
    bkPID.Compute();

    CSH_TED_PWM = (uint8_t)((CSH_TED_PWM_OUT / 255.0) * 100.0);
    BK_TED_PWM = (uint8_t)((BK_TED_PWM_OUT / 255.0) * 100.0);
    if (CSH_TED_PWM > MAX_PWM) CSH_TED_PWM = MAX_PWM;
    if (BK_TED_PWM > MAX_PWM) BK_TED_PWM = MAX_PWM;

    // Fan PID - REVERSE (increase fan when actual temp > FanSetPoint, i.e., hotter)
    cshFanPID.SetControllerDirection(REVERSE);
    bkFanPID.SetControllerDirection(REVERSE);

    // Feed actual temperature to fan PID inputs
    CSH_Fan_PID_Input = CSH_NTC_AVG;
    BK_Fan_PID_Input = BK_NTC_AVG;

    cshFanPID.Compute();
    bkFanPID.Compute();

    CSH_FAN_PWM = (uint8_t)((CSH_FAN_PWM_OUT / 255.0) * 100.0);
    BK_FAN_PWM = (uint8_t)((BK_FAN_PWM_OUT / 255.0) * 100.0);

    // Enforce per-level fan speed limits for cooling
    float fanMinCool = FAN_MIN_COOL;
    float fanMaxCool = 100.0;

    if (DESIRED_COOL == COOL_LEVEL_1_SP) {
      fanMinCool = COOL_L1_FAN_MIN;
      fanMaxCool = COOL_L1_FAN_MAX;
    } else if (DESIRED_COOL == COOL_LEVEL_2_SP) {
      fanMinCool = COOL_L2_FAN_MIN;
      fanMaxCool = COOL_L2_FAN_MAX;
    } else if (DESIRED_COOL == COOL_LEVEL_3_SP) {
      fanMinCool = COOL_L3_FAN_MIN;
      fanMaxCool = COOL_L3_FAN_MAX;
    }

    if (CSH_FAN_PWM < fanMinCool) CSH_FAN_PWM = (uint8_t)fanMinCool;
    if (BK_FAN_PWM < fanMinCool) BK_FAN_PWM = (uint8_t)fanMinCool;
    if (CSH_FAN_PWM > fanMaxCool) CSH_FAN_PWM = (uint8_t)fanMaxCool;
    if (BK_FAN_PWM > fanMaxCool) BK_FAN_PWM = (uint8_t)fanMaxCool;

    // Shutdowns
    if (SHUTDOWN_HT_CUSH_ACTIVE || SHUTDOWN_LT_CUSH_ACTIVE) {
      CSH_TED_PWM = 0;
      CSH_FAN_PWM = SHUTDOWN_FAN_PERC;
    }
    if (SHUTDOWN_HT_BACK_ACTIVE || SHUTDOWN_LT_BACK_ACTIVE) {
      BK_TED_PWM = 0;
      BK_FAN_PWM = SHUTDOWN_FAN_PERC;
    }
  } else {
    // Off
    digitalWrite(HEAT_COOL_RLY, LOW);
    CSH_TED_PWM = 0;
    BK_TED_PWM = 0;
    CSH_FAN_PWM = 0;
    BK_FAN_PWM = 0;

    if (COOLDOWN_ACTIVE) {
      CSH_FAN_PWM = SHUTDOWN_FAN_PERC;
      BK_FAN_PWM = SHUTDOWN_FAN_PERC;
    }
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
#define PRINT_KEY_VALUE(key, value) Serial.println(String(key) + "=" + String(value))

  // Determine current mode
  String mode = "OFF";
  if (DESIRED_HEAT != HEAT_OFF) {
    if (DESIRED_HEAT == HEAT_LEVEL_1_SP) mode = "HEAT_1";
    else if (DESIRED_HEAT == HEAT_LEVEL_2_SP) mode = "HEAT_2";
    else if (DESIRED_HEAT == HEAT_LEVEL_3_SP) mode = "HEAT_3";
  } else if (DESIRED_COOL != FAN_OFF) {
    if (DESIRED_COOL == COOL_LEVEL_1_SP) mode = "COOL_1";
    else if (DESIRED_COOL == COOL_LEVEL_2_SP) mode = "COOL_2";
    else if (DESIRED_COOL == COOL_LEVEL_3_SP) mode = "COOL_3";
  }

  PRINT_KEY_VALUE("DESIRED_MODE", mode);

  // Also send the actual temperature setpoints (for charting)
  PRINT_KEY_VALUE("DESIRED_HEAT", DESIRED_HEAT);
  PRINT_KEY_VALUE("DESIRED_COOL", DESIRED_COOL);

  // Rest unchanged
  PRINT_KEY_VALUE("CSH_NTC_AVG", CSH_NTC_AVG);
  PRINT_KEY_VALUE("BK_NTC_AVG", BK_NTC_AVG);

  PRINT_KEY_VALUE("CSH_BLOWR_PWM", CSH_FAN_PWM);
  PRINT_KEY_VALUE("CSH_TED_PWM", CSH_TED_PWM);
  PRINT_KEY_VALUE("BK_BLOWR_PWM", BK_FAN_PWM);
  PRINT_KEY_VALUE("BK_TED_PWM", BK_TED_PWM);

  PRINT_KEY_VALUE("SHUTDOWN_HT_CUSH", SHUTDOWN_HT_CUSH_ACTIVE ? 1 : 0);
  PRINT_KEY_VALUE("SHUTDOWN_HT_BACK", SHUTDOWN_HT_BACK_ACTIVE ? 1 : 0);
  PRINT_KEY_VALUE("SHUTDOWN_LT_CUSH", SHUTDOWN_LT_CUSH_ACTIVE ? 1 : 0);
  PRINT_KEY_VALUE("SHUTDOWN_LT_BACK", SHUTDOWN_LT_BACK_ACTIVE ? 1 : 0);

#undef PRINT_KEY_VALUE
}

void CheckSerialCommands() {
  if (Serial.available() > 0) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();

    if (cmd.startsWith("HEAT:")) {
      int level = cmd.substring(5).toInt();
      if (level >= 0 && level <= 3) {
        if (level == 0){
          DESIRED_HEAT = FAN_OFF;

          // enable cooldown
          _cooldown_seconds = millis();
          COOLDOWN_ACTIVE = true;
        }
        else if (level == 1) DESIRED_HEAT = HEAT_LEVEL_1_SP;
        else if (level == 2) DESIRED_HEAT = HEAT_LEVEL_2_SP;
        else if (level == 3) DESIRED_HEAT = HEAT_LEVEL_3_SP;
        DESIRED_COOL = FAN_OFF;  // Disable opposite mode
      }
    } else if (cmd.startsWith("COOL:")) {
      int level = cmd.substring(5).toInt();
      if (level >= 0 && level <= 3) {
        if (level == 0) {
          DESIRED_COOL = FAN_OFF;

          // enable cooldown
          _cooldown_seconds = millis();
          COOLDOWN_ACTIVE = true;
        } else if (level == 1) DESIRED_COOL = COOL_LEVEL_1_SP;
        else if (level == 2) DESIRED_COOL = COOL_LEVEL_2_SP;
        else if (level == 3) DESIRED_COOL = COOL_LEVEL_3_SP;
        DESIRED_HEAT = HEAT_OFF;
      }
    }
  }
}