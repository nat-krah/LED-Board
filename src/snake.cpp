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
int bunPin{4} = [2, 3, 4, 5]; // Right left down up
bool bunPrev{4} = [0, 0, 0, 0]; // Right left down up


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
    FastLED.addLeds<WS2812B, 6, GRB>(leds, NUM_LEDS);

    //Turn on board
    solidCol(0x000100);

    //Initialize buttons
    pinMode(bunPin[0], INPUT);
    pinMode(bunPin[1], INPUT);
    pinMode(bunPin[2], INPUT);
    pinMode(bunPin[3], INPUT);

    //Start Serial
    Serial.begin(9600);

    //Turn off board
    delay(50);
    solidCol(0x000000);
}


//Main Code
void loop() {
    bool curState{4} = [digitalRead(bunPin[0]), digitalRead(bunPin[1]), digitalRead(bunPin[2]), digitalRead(bunPin[3])];

    //Grab current state
    //If state was down and now up then the button was pressed 
    //Generate an array of buttons that were pressed in this cycle
    //if time has ellaptsed enough to update screen, i.e. if current time is greater than then cycle time, call update screen
    //if (millis() - lastUpdate > framerate){
    //    Update screen
    //}
    



    rightPrev = right;
    leftPrev = left;
    downPrev = down;
    upPrev = up
 


}


/*******************************\
|           Functions           |
\*******************************/


int solidCol(int color){
    auto map   = fl::XYMap::constructRectangularGrid(HEIGHT, WIDTH);
    fl::Leds s = fl::Leds(leds, map);

    for (uint16_t y = 0; y < HEIGHT; ++y) {
        for (uint16_t x = 0; x < WIDTH; ++x) {
            s(x, y) = CRGB(color);
        }
    }
}