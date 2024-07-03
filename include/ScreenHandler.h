#pragma once
#include "Arduino.h"
#include "ioMapping.h"
#include <M5Core2.h>

#define SCREEN_HEIGHT 240
#define SCREEN_WIDTH 320

#define EYE_WIDTH 50
#define EYE_LENGTH 100
#define EYE_X0 110
#define EYE_Y0 40
#define EYE_RADIUS 30
#define EYE_HEIGHT_CLOSED 20
#define BLINK_SPEED 8

enum screenState_t{
    WAITING,
    SLEEPING,
    ANGRY,
    LOOKING,
    HAPPY
};

using namespace ioMapping;

class ScreenHandler{

private:
    //gesture detection
    Zone * topHalf;
    Zone * bottomHalf;
    Gesture * swipeDown;
    Gesture * swipeUp;
    Button * screenTouch;

    screenState_t screenState;
    static ScreenHandler * pObjet;
    TFT_eSprite * faceSprite;

    volatile uint8_t swipeCounter;
    volatile uint8_t tapCounter;
    static void task();

    //sprite actions
    static void blink(bool eye);
    static void angryEyes(uint16_t timeMs);
    static void swipeDetected(Event&);
    static void tapDetected(Event& e);
    
public:
    
    ScreenHandler();
    ~ScreenHandler();
    void start();
};
