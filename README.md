# Tesseract
Glowing Cube thing

![Cube](https://github.com/jastill/Tesseract/blob/main/media/Glowing.png?raw=true)

## Build

This was built with some parts that were removed from an old project, an old USB charger, a new tilt sensor and a new photo cube.

A very simple idea, if the tilt sensor detects movement it trigger the code to glow.

## Materials

| Item | Purchase Link |
|------|---------------|
| Photo Cube | https://www.amazon.com/gp/product/B01FSBDZW0/ref=ppx_od_dt_b_asin_title_s00?ie=UTF8&psc=1 |
| WeMos D1 | |
| 8 Pixel 2812 LED Strip CJMCU-2812-8 | | 
| Tilt Sensor | https://www.amazon.com/gp/product/B00RGN0KY0/ref=ppx_yo_dt_b_asin_title_o00_s01?ie=UTF8&psc=1 |
| Privacy pain |  |

## Circuit

The LED and Tilt sensor are connected directly to the Wemos to remove the need for a custom PCB.

Connections:

| WeMos | LED |
|-------|-----|
| 5v | VDC |
| GND | GND |
| D4 | DIN |
