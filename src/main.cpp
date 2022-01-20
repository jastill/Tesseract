#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define PIN D4
#define NUMPIXELS 8

Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAY 50

#define START_BRIGHTNESS (uint8_t)128
#define MAX_BRIGHTNESS (uint8_t)255
#define STEPS (uint8_t)10

#define BLUE  pixels.Color(0,0,255)
#define RED  pixels.Color(255,0,0)
#define COLOR BLUE

uint8_t brightness = START_BRIGHTNESS;

void setup()
{
  pixels.begin();
  pixels.clear();
}

void loop()
{
  static uint8_t up = false;

  if (up == true)
  {
    brightness = brightness + STEPS;
  }
  else
  {
    brightness = brightness - STEPS;
  }

  if (brightness > MAX_BRIGHTNESS-STEPS && up == true)
  {
    up = false;
  }
  else if (brightness < STEPS && up == false)
  {
    up = true;
  }

  pixels.setBrightness(brightness);
  for (int i=0; i<NUMPIXELS; i++) {
    pixels.setPixelColor(i, COLOR);
  }
  pixels.show();

  delay(DELAY);
}