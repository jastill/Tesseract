/**
 * @file main.cpp
 * @author John Astill
 * @brief Glow a cube with an 8 led strip. 
 *        On startup the cube throbs for a set time then turns off.
 *        Any movement on the cube detected by an interrupt will start the throbbing again.
 * @version 0.1
 * @date 2022-01-21
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

#define LED_PIN D1
#define NUMPIXELS 8
#define MOVEMENT_IN D4

Adafruit_NeoPixel pixels(NUMPIXELS, LED_PIN, NEO_GRB + NEO_KHZ800);

#define DELAY 50

#define START_BRIGHTNESS (uint8_t)128
#define MAX_BRIGHTNESS (uint8_t)255
#define STEPS (uint8_t)10

#define BLUE  pixels.Color(0,0,255)
#define RED  pixels.Color(255,0,0)
#define COLOR BLUE

uint8_t brightness = START_BRIGHTNESS;

// The run duration will run for this long after the last detected motion
#define RUN_DURATION (long)60000
volatile long runTimerStart = 0;
volatile uint8_t movement = false;

/**
 * @brief Interrupt handler to detect the tilt sensor has moved.
 *        If you don't want to get rst cause:2, boot mode:(3,6), then make sure you have IRAM_ATTR before
 *        the function: https://arduino-esp8266.readthedocs.io/en/latest/reference.html?highlight=attachinterrupt#digital-io
 */
IRAM_ATTR void movementDetected() {
  movement = true;
}

/**
 * @brief Setup the pins for interrupts and configure the NEO pixels
 * 
 */
void setup()
{
  pinMode(MOVEMENT_IN,INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(MOVEMENT_IN), movementDetected, CHANGE);

  pixels.begin();
  pixels.clear();
}

/**
 * @brief Main loop looking for a tilt sensor. If running, throb the leds.
 * 
 */
void loop()
{
  static uint8_t brightnessUp = false;
  long duration = 0;

  // Interrupt triggered by tilt sensor
  if (movement == true) {
    runTimerStart = millis();
    movement = false;
  }

  // Millis is milliseconds since the program started running. So this will
  // cause the cube to glow once on startup.
  duration = millis() - runTimerStart;

  if (duration < RUN_DURATION) {
    if (brightnessUp == true)
    {
      brightness = brightness + STEPS;
    }
    else
    {
      brightness = brightness - STEPS;
    }

    // Flip the direction if the max or min is crossed.
    if (brightness > MAX_BRIGHTNESS-STEPS && brightnessUp == true)
    {
      brightnessUp = false;
    }
    else if (brightness < STEPS && brightnessUp == false)
    {
      brightnessUp = true;
    }

    pixels.setBrightness(brightness);
    for (int i=0; i<NUMPIXELS; i++) {
      pixels.setPixelColor(i, COLOR);
    }
    pixels.show();

    delay(DELAY);
  } else {
    pixels.clear();
    pixels.show();
  }
}