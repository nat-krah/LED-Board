#include <Arduino.h>

#include <FastLED.h>
#include "fl/leds.h"
#include "fl/xymap.h"
 
constexpr uint16_t WIDTH  = 8;
constexpr uint16_t HEIGHT = 8;
constexpr uint16_t NUM_LEDS = HEIGHT * WIDTH;
CRGB leds[NUM_LEDS];

//Setup code
void setup() {
  FastLED.addLeds<WS2812B, 5, GRB>(leds, NUM_LEDS);

  Serial.begin(9600);
}


//Main Code
void loop() {
  auto map   = fl::XYMap::constructRectangularGrid(HEIGHT, WIDTH);
  fl::Leds s = fl::Leds(leds, map);


  int i = 0;
  for (uint16_t y = 0; y < HEIGHT; ++y) {
      for (uint16_t x = 0; x < WIDTH; ++x) {
          s(x, y) = CRGB(1, 1 + i, 1 + i);
          i++;

          Serial.print(x);

        delay(50);
      }
  }


  for (uint16_t y = 0; y < HEIGHT; ++y) {
    for (uint16_t x = 0; x < WIDTH; ++x) {
      s(x, y) = CRGB(0,0,0);
    }
  }

}
