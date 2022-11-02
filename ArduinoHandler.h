//
// Created by itsrichard on 26/10/22.
//

#ifndef PROYECTO_2_ARDUINOHANDLER_H
#define PROYECTO_2_ARDUINOHANDLER_H

#include "SerialPort.h"
#include <unistd.h>
#include <thread>
#include <iostream>

using namespace std;

class ArduinoHandler {
public:
    ArduinoHandler();
    int* getCheckerCoord();
    int* getMoveCoord();
    int atackLed();
    int closeSerial();
private:
    int verifyKey(char key);
    int turnOnLight();
    int turnOffLight();
};

#endif //PROYECTO_2_ARDUINOHANDLER_H
