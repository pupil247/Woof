#include "ScreenHandler.h"

ScreenHandler::ScreenHandler(){
    pObjet = this;
    screenState = WAITING;
    tapCounter = 0;
    swipeCounter = 0;
}

ScreenHandler::~ScreenHandler(){
    delete faceSprite;
    delete topHalf;
    delete bottomHalf;
    delete swipeUp;
    delete swipeDown;
    delete screenTouch;
} 

void ScreenHandler::start(){
    faceSprite = new TFT_eSprite(&M5.Lcd);
    topHalf = new Zone(0,0,SCREEN_HEIGHT/2,SCREEN_WIDTH);
    bottomHalf = new Zone(0,SCREEN_HEIGHT/2, SCREEN_WIDTH,SCREEN_HEIGHT/2);
    swipeDown = new Gesture(*topHalf, *bottomHalf, "Swipe Down");
    swipeUp = new Gesture(*bottomHalf, *topHalf, "Swipe Up");

    screenTouch = new Button(0, 0, 320, 240, "touch screen");

    
    
    swipeDown->addHandler(swipeDetected);
    swipeUp->addHandler(swipeDetected);
    screenTouch->addHandler(tapDetected, E_RELEASE);
    faceSprite->createSprite(SCREEN_WIDTH, SCREEN_HEIGHT);
    xTaskCreatePinnedToCore( (TaskFunction_t)task,    "Task screen",    5000,      NULL,    4,    NULL,    1);
}

void ScreenHandler::task(){
    //local variables
    TFT_eSprite * faceSprite = pObjet->faceSprite;

    //init the eye sprite
    faceSprite->fillSprite(TFT_BLACK);
    faceSprite->fillRoundRect(EYE_X0, EYE_Y0, EYE_WIDTH, EYE_LENGTH, EYE_RADIUS, TFT_CYAN);
    faceSprite->fillRoundRect(EYE_X0 + 100, EYE_Y0, EYE_WIDTH, EYE_LENGTH, EYE_RADIUS, TFT_CYAN);
    faceSprite->pushSprite(0,0);
    M5.Axp.SetVibration(true);  // Open the vibration.   开启震动马达
    vTaskDelay(pdMS_TO_TICKS(100));
    M5.Axp.SetVibration(false); 
    
    uint16_t cnt = 0;
    while(1){
        
        switch(pObjet->screenState){
            case screenState_t::WAITING:
                cnt++;
                if(!(cnt%4000) || !(cnt%4500)){
                    blink(0);
                }
                break;
            case screenState_t::SLEEPING:
                break;
            case screenState_t::ANGRY:
                M5.Axp.SetVibration(true);
                angryEyes(2000);
                M5.Axp.SetVibration(false);
                pObjet->screenState = WAITING;
                break;
            case screenState_t::HAPPY:
                break;
            case screenState_t::LOOKING:
                break;

        }

        //detect if gesture is detected
        M5.Touch.update();
        //detect if tap is detected

        vTaskDelay(pdMS_TO_TICKS(1)); 
    }
    
}

void ScreenHandler::blink(bool eye){
    int currentWidth = EYE_WIDTH;
    int currentHeight = EYE_LENGTH;
    int currentPositionX = EYE_X0;
    int currentPositionY = EYE_Y0;
    int currentRadius = EYE_RADIUS;
    bool closing = 1;
    bool blinkDone = 0;
    while(!blinkDone){
        if(closing){
            currentWidth += 2 * BLINK_SPEED;
            currentHeight -= 4 * BLINK_SPEED;
            currentPositionX -= 2 * BLINK_SPEED;
            currentPositionY += BLINK_SPEED;
            currentRadius = (currentRadius > 5 && (currentWidth % 3)) ? currentRadius - 2 * BLINK_SPEED : currentRadius;
        }else{
            currentWidth -= 2 * BLINK_SPEED;
            currentHeight += 4 * BLINK_SPEED;;
            currentPositionX += 2 * BLINK_SPEED;
            currentPositionY -= BLINK_SPEED;
            currentRadius = (currentRadius < EYE_RADIUS && (currentWidth % 3)) ? currentRadius + 2 * BLINK_SPEED : currentRadius;    
        }

        if(currentHeight < EYE_HEIGHT_CLOSED)
            currentHeight = EYE_HEIGHT_CLOSED;

        pObjet->faceSprite->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, TFT_BLACK);
        pObjet->faceSprite->fillRoundRect(currentPositionX, currentPositionY, currentWidth, currentHeight, currentRadius, TFT_CYAN);
        if(eye)
            pObjet->faceSprite->fillRoundRect(EYE_X0 + 100, EYE_Y0, EYE_WIDTH, EYE_LENGTH, EYE_RADIUS, TFT_CYAN);
        else
            pObjet->faceSprite->fillRoundRect(currentPositionX + 100, currentPositionY, currentWidth, currentHeight, currentRadius, TFT_CYAN);

        pObjet->faceSprite->pushSprite(0,0);
        if(currentWidth >= EYE_LENGTH )
            closing = 0;
        else if(currentHeight >= EYE_LENGTH){

            closing = 1;
            blinkDone = true;
        }
    }
    
}

void ScreenHandler::angryEyes(uint16_t timeMs){
    int currentWidth = EYE_WIDTH;
    int currentHeight = EYE_LENGTH;
    int currentPositionX = EYE_X0;
    int currentPositionY = EYE_Y0;
    int currentRadius = EYE_RADIUS;
    bool closing = 1;
    bool blinkDone = 0;
    while(!blinkDone){
        if(closing){
            currentWidth += 2 * BLINK_SPEED;
            currentHeight -= 4 * BLINK_SPEED;
            currentPositionX -= 2 * BLINK_SPEED;
            currentPositionY += BLINK_SPEED;
            currentRadius = (currentRadius > 5 && (currentWidth % 3)) ? currentRadius - 2 * BLINK_SPEED : currentRadius;
        }else{
            currentWidth -= 2 * BLINK_SPEED;
            currentHeight += 4 * BLINK_SPEED;;
            currentPositionX += 2 * BLINK_SPEED;
            currentPositionY -= BLINK_SPEED;
            currentRadius = (currentRadius < EYE_RADIUS && (currentWidth % 3)) ? currentRadius + 2 * BLINK_SPEED : currentRadius;    
        }

        if(currentHeight < EYE_HEIGHT_CLOSED)
            currentHeight = EYE_HEIGHT_CLOSED;

        pObjet->faceSprite->fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, TFT_BLACK);
        pObjet->faceSprite->fillRoundRect(currentPositionX, currentPositionY, currentWidth, currentHeight, currentRadius, currentHeight >= EYE_LENGTH ? TFT_CYAN : TFT_RED);
   
        pObjet->faceSprite->fillRoundRect(currentPositionX + 100, currentPositionY, currentWidth, currentHeight, currentRadius, currentHeight >= EYE_LENGTH ? TFT_CYAN : TFT_RED);

        pObjet->faceSprite->pushSprite(0,0);
        if(currentWidth >= EYE_LENGTH - 20){
            closing = 0;
            vTaskDelay(pdMS_TO_TICKS(1000));
        }
        else if(currentHeight >= EYE_LENGTH){
            closing = 1;
            blinkDone = true;
        }
    }    
}

void ScreenHandler::swipeDetected(Event& e){
    Serial.println("swipedetected");
    if(pObjet->swipeCounter++ > 5){
        pObjet->screenState = screenState_t::HAPPY;
    }
}

void ScreenHandler::tapDetected(Event& e){
    Serial.println("tapDetected");
    if(pObjet->tapCounter++ > 5){
        pObjet->tapCounter = 0;
        pObjet->screenState = screenState_t::ANGRY;
        Serial.println("Charlie is angry");
    }
}


ScreenHandler* ScreenHandler::pObjet = nullptr;