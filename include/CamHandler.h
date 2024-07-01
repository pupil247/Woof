#pragma once
#include "Arduino.h"
#include "ioMapping.h"
#include <M5Core2.h>
using namespace ioMapping;

class CamHandler{

private:
    static CamHandler * pObjet;
    static void task();
    
public:
    
    CamHandler(){};
    ~CamHandler(){};
    void start();
};
