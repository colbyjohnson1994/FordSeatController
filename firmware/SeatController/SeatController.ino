#include "includes.h"

void setup() {
  //initialize serial
  Serial.begin(115200);

  delay(1000);

  // initialize DotStar LED
  _DotStarLED.begin(); // Initialize pins for output
  _DotStarLED.setBrightness(80);
  _DotStarLED.show();  // Turn all LEDs off ASAP

  initializeInputs();
  initializeDigitalOutputs();
  initializeAnalogOutputs();

  // initialize counting variables
  _sensor_seconds = millis();
  _control_seconds = millis();
  _software_seconds = millis();
  _button_seconds = millis();
  _pwm_seconds = millis();

  Serial.println("Controller Initialized");
  Serial.println("Firmware Revision: 03.20.2023");
  Serial.println("CJ Design and Build\r\n");

  //turn the PID on
  cshPID.SetMode(AUTOMATIC);
  bkPID.SetMode(AUTOMATIC);
}

void loop() 
{
  CoolBtn.update();
  HeatBtn.update();

  if ((millis() - _pwm_seconds) > PWM_INTERVAL)
  {
    // pwm interval has elapsed
    _pwm_seconds = millis();

    UpdatePWMOutputs();
  }

  if ((millis() - _button_seconds) > BUTTON_FREQ)
  {
    // buttons frequency has elapsed, read from buttons
    _button_seconds = millis();

    CheckButtons();
  }

  if ((millis() - _sensor_seconds) > READ_FREQ)
  {
    // read frequency has elapsed, read from sensors
    _sensor_seconds = millis();

    ReadFromInputs();
  }

  if ((millis() - _control_seconds) > CONTROL_FREQ)
  {
    _control_seconds = millis();

    AdjustPWMValues();
  }

  if ((millis() - _software_seconds) > SOFTWARE_FREQ)
  {
    _software_seconds = millis();

    UpdateSoftware();
  }

  // code for demo-ing LED's
  // digitalWrite(RED_LED, HIGH);

  // for (int i = 0; i < 75; i++)
  // {
  //   _DotStarLED.setPixelColor(0, i, i, i);
  //   _DotStarLED.show();
  //   delay(5);
  // }

  // digitalWrite(RED_LED, LOW);
  
  // for (int i = 75; i >= 0; i--)
  // {
  //   _DotStarLED.setPixelColor(0, i, i, i);
  //   _DotStarLED.show();
  //   delay(5);
  // }
}
