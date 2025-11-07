#include <Arduino.h>
#include <FastLED.h>
#include "fl/leds.h"
#include "fl/xymap.h"


/*******************************\
|            Globals            |
\*******************************/

//LEDs
constexpr uint16_t WIDTH  = 8;
constexpr uint16_t HEIGHT = 8;
constexpr uint16_t NUM_LEDS = HEIGHT * WIDTH;
CRGB leds[NUM_LEDS];

//Controls
int bunPin[5] = {2, 3, 4, 5, 6}; // Right left down up
bool bunPrev[5] = {0, 0, 0, 0, 0}; // Right left down up
bool bunPressed[5] = {0, 0, 0, 0, 0}; // Right left down up

unsigned long int lastUpdate = 0;
unsigned int index = 0;
unsigned const int maxIndex = 5;
unsigned int interations = 0;
unsigned int framerate = 250;



/*******************************\
|     Function Declarations      |
\*******************************/

int solidCol(int R, int G, int B, bool print = true);


/*******************************\
|          Setup Code           |
\*******************************/

void setup() {
    //Initialize board
    FastLED.addLeds<WS2812B, 12, GRB>(leds, NUM_LEDS);

    //Turn on board
    solidCol(0, 1, 0);

    //Initialize buttons
    pinMode(bunPin[0], INPUT_PULLUP);
    pinMode(bunPin[1], INPUT_PULLUP);
    pinMode(bunPin[2], INPUT_PULLUP);
    pinMode(bunPin[3], INPUT_PULLUP);
    pinMode(bunPin[4], INPUT_PULLUP);

    //Start Serial
    Serial.begin(9600);

    //Turn off board
    delay(250);
    solidCol(0,0,0);
}



//Main Code
void loop() {
    bool curState[5] = {!digitalRead(bunPin[0]), !digitalRead(bunPin[1]), !digitalRead(bunPin[2]), !digitalRead(bunPin[3]), !digitalRead(bunPin[3])};

    for (unsigned int i = 0; i < sizeof(curState) / sizeof(curState[0]); i++){
        if (curState[i] == true && bunPrev[i] == false){
            bunPressed[i] = true;
        }
    }

    if ((millis() - lastUpdate) > framerate){
        FastLED.clear();
        auto map   = fl::XYMap::constructRectangularGrid(HEIGHT, WIDTH);
        fl::Leds s = fl::Leds(leds, map);

        if (bunPressed[0]){
            index++;
        } else if (index > maxIndex){
            index = 0;
        }

        if (index == 1){
            framerate = 250;
            solidCol(0, 0, 1);
        } else if (index == 2){
            framerate = 50;
                
            unsigned int pos = interations % 32;
            if (pos <= 7){
                s(0, pos) = CRGB(0, 0, 2);
            } else if (pos > 7 && pos <= 15){
                s(pos - 7, 7) = CRGB(0, 0, 2);
            } else if (pos > 15 && pos <= 23){
                s(7, 7-(pos-15)) = CRGB(0, 0, 2);
            } else if (pos > 23){
                s(7 - (pos-23), 0) = CRGB(0, 0, 2);
            }
        } else if (index == 3){
            framerate = 500;
            solidCol(1, 1, 1, false);

            unsigned int startPos = 0;
            for (uint16_t y = 0; y < HEIGHT; ++y) {
                for (uint16_t x = 0; x < WIDTH; ++x) {
                    if (((x + y) >= (0 + startPos) && (x + y) <= (2 + startPos)) || ((x + y) >= (12 + startPos) && (x + y) < (16 + startPos))){
                        s(x, y) = CRGB(0, 0, 1);
                    }
                    if (((x + y) > (2 + startPos) && (x + y) < (6 + startPos)) || ((x + y) > (8 + startPos) && (x + y) < (12 + startPos))){
                        s(x, y) = CRGB(1, 0, 0);
                    }
                }
            }
        }
        
        FastLED.show(); 
        lastUpdate = millis();
        interations++;
        for(unsigned int i = 0; i < sizeof(bunPressed) / sizeof(bunPressed[0]); i ++){
            bunPressed[i] = 0;
        }
    }
    
    for(unsigned int i = 0; i < sizeof(bunPrev) / sizeof(bunPrev[0]); i ++){
      bunPrev[i] = curState[i];
      curState[i] = 0;
    }
}


/*******************************\
|           Functions           |
\*******************************/

void introCode(){
    
}



int solidCol(int R, int G, int B, bool print = true){
    auto map   = fl::XYMap::constructRectangularGrid(HEIGHT, WIDTH);
    fl::Leds s = fl::Leds(leds, map);

    for (uint16_t y = 0; y < HEIGHT; ++y) {
        for (uint16_t x = 0; x < WIDTH; ++x) {
            s(x, y) = CRGB(R, G, B);
        }
    }
    if (print){
        FastLED.show(); 
    }
}