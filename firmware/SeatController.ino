#include "includes.h"

void setup() {
  // initialize DotStar LED
  _DotStarLED.begin(); // Initialize pins for output
  _DotStarLED.setBrightness(80);
  _DotStarLED.show();  // Turn all LEDs off ASAP

  // initialize red led
  pinMode(RED_LED, OUTPUT);
}

void loop() 
{
  digitalWrite(RED_LED, HIGH);

  for (int i = 0; i < 75; i++)
  {
    _DotStarLED.setPixelColor(0, i, i, i);
    _DotStarLED.show();
    delay(5);
  }

  digitalWrite(RED_LED, LOW);
  
  for (int i = 75; i >= 0; i--)
  {
    _DotStarLED.setPixelColor(0, i, i, i);
    _DotStarLED.show();
    delay(5);
  }
}
