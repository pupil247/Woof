#pragma once
#include "Arduino.h"
#include <Wifi.h>
#include "ioMapping.h"
using namespace ioMapping;

class WifiHandler{

private:
    static WifiHandler * pObjet;
    static void task();
    std::string ssid;
    std::string password;
public:
    
    WifiHandler();
    ~WifiHandler();
    void start();
};
