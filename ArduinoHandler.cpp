//
// Created by itsrichard on 26/10/22.
//

#include "ArduinoHandler.h"

SerialPort* serialPort;
int keys[9] = {'1','2','3','4','5','6','7','8','9'};
int checkerCoord [2];
int moveCoord [4];
int counter = 0;

ArduinoHandler::ArduinoHandler() {
    serialPort = new SerialPort;
    int n = serialPort->connectSerial();
    if (n < 0) cout << "El control no está conectado, conectelo y reinicie la aplicación" << endl;
}

int* ArduinoHandler::getCheckerCoord() {
    char key;
    for (int i = 0; i < 2; ++i) {
        key = serialPort->getKey();
        if (key == '9') {
            cout << "Se borró correctamente la pieza elegida" << endl;
            return getCheckerCoord();
        }
        int n = verifyKey(key);
        if (!n){
            cout << "Ingrese solo las entradas válidas del control" << endl;
            return getCheckerCoord();
        }
        checkerCoord[i] = (int) key - 48;
        moveCoord[i] = (int) key - 48;
    }
    return checkerCoord;
}

int ArduinoHandler::verifyKey(char key) {
    for (int j = 0; j < 9; ++j) {
        if (key == keys[j]) return 1;
    }
    return 0;
}

int* ArduinoHandler::getMoveCoord() {
    char key;
    for (int i = 2; i < 4; ++i) {
        key = serialPort->getKey();
        if (key == '9' && counter < 1) {
            cout << "Se borró correctamente el lugar de ataque" << endl;
            counter++;
            return getMoveCoord();
        }
        if (key == '9' && counter == 1){
            cout << "Se borró correctamente las entradas anteriores. Iniciando otra vez con la pieza elegida" << endl;
            counter = 0;
            int n = 9;
            int* goBack = &n;
            return goBack;
        }
        int n = verifyKey(key);
        if (!n){
            cout << "Ingrese solo las entradas válidas del control" << endl;
            return getMoveCoord();
        }
        moveCoord[i] = (int) key - 48;
    }
    return moveCoord;
}

int ArduinoHandler::atackLed() {
    turnOnLight();
    sleep(2);
    turnOffLight();
    return 0;
}

int ArduinoHandler::turnOnLight() {
    char message = 'E';
    serialPort->writeData(message);
    return 0;
}

int ArduinoHandler::turnOffLight() {
    char message = 'F';
    serialPort->writeData(message);
    return 0;
}

int ArduinoHandler::closeSerial(){
    serialPort->closeSerial();
    delete serialPort;
    return 0;
}