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
int bunPin[4] = {2, 6, 4, 5}; // Right left down up
bool bunPrev[4] = {0, 0, 0, 0}; // Right left down up
bool bunPressed[4] = {0, 0, 0, 0}; // Right left down up

unsigned int lastUpdate = 0;


//Snake structure
struct snakeNode{
    int x;
    int y;

    snakeNode* next;
    snakeNode* previous;
};

//Game state
int startWidth = 1; //Starting x position of game
int startHeight = 1; //Starting y position of game
int width = 0; //Width of playable game
int height = 0; //Height of playable game
int score = 0;
int speed = 50;

int snakeCol = 0x000100;
int fruitCol = 0x000100;

int fruitX = 0;
int fruitY = 0;


/*******************************\
|      Function Declaratio       |
\*******************************/

int randi(int x, int y);
int solidCol(int color);


/*******************************\
|          Setup Code           |
\*******************************/

void setup() {
    //Initialize board
    FastLED.addLeds<WS2812B, 12, GRB>(leds, NUM_LEDS);

    //Turn on board
    solidCol(0x000100);

    //Initialize buttons
    pinMode(bunPin[0], INPUT_PULLUP);
    pinMode(bunPin[1], INPUT_PULLUP);
    pinMode(bunPin[2], INPUT_PULLUP);
    pinMode(bunPin[3], INPUT_PULLUP);

    //Start Serial
    Serial.begin(9600);

    //Turn off board
    delay(250);
    solidCol(0x000000);
    
}


//Main Code
void loop() {
    unsigned int framerate = 250;
    bool curState[4] = {!digitalRead(bunPin[0]), !digitalRead(bunPin[1]), !digitalRead(bunPin[2]), !digitalRead(bunPin[3])};

    for (int i = 0; i < 4; i++){
        if (curState[i] == true && bunPrev[i] == false){
            bunPressed[i] = true;
        }
    }

    if (millis() - lastUpdate > framerate){
      FastLED.clear();
      auto map   = fl::XYMap::constructRectangularGrid(HEIGHT, WIDTH);
      fl::Leds s = fl::Leds(leds, map);

      for (int i = 0; i < 4; i++){
        if (bunPressed[i]){
          s(i, 0) = CRGB(0, 0, 1);
        }
      }

      for (int i = 0; i < 4; i++){
        if (curState[i]){
          s(i, 1) = CRGB(1, 0, 1);
        }
      }

      for (int i = 0; i < 4; i++){
        if (bunPrev[i]){
          s(i, 2) = CRGB(1, 0, 0);
        }
      }

      s(5, 5) = CRGB(1, 0, 0);
      FastLED.show(); 
      lastUpdate = millis();
      for(int i = 0; i < 4; i ++){
        bunPressed[i] = 0;
      }
    }

    //Grab current state
    //If state was down and now up then the button was pressed 
    //Generate an array of buttons that were pressed in this cycle
    //if time has ellaptsed enough to update screen, i.e. if current time is greater than then cycle time, call update screen
    //if (millis() - lastUpdate > framerate){
    //    Update screen
    //}

    Serial.print(curState[0]);
    Serial.print(", ");
    Serial.print(curState[1]);
    Serial.print(", ");
    Serial.print(curState[2]);
    Serial.print(", ");
    Serial.print(curState[3]);
    Serial.print("\n");
    
    delay(10);
    for(int i = 0; i < 4; i ++){
      bunPrev[i] = curState[i];
      curState[i] = 0;
    }
  
}


/*******************************\
|           Functions           |
\*******************************/


int solidCol(int color){
    auto map   = fl::XYMap::constructRectangularGrid(HEIGHT, WIDTH);
    fl::Leds s = fl::Leds(leds, map);

    for (uint16_t y = 0; y < HEIGHT; ++y) {
        for (uint16_t x = 0; x < WIDTH; ++x) {
            s(x, y) = CRGB(0,1,0);
        }
    }
    FastLED.show(); 
}