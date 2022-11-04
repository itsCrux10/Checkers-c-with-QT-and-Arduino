//
// Created by itsrichard on 26/10/22.
//

#include "ArduinoHandler.h"
#define DELETE '9'
#define ATACK '0'
#define EXIT 9

// Attributes of the class
SerialPort* serialPort; // class with the serial functionality
int keys[10] = {'1','2','3','4','5','6','7','8',DELETE, ATACK}; // keys that are allowed for the user to press
int checkerCoord [2]; // Content the row and column coord of selected checker
int moveCoord [4]; // Content the row and column coord of selected checker and also the place to move
int counter = 0; // Variable for erased cases
int atack = 0; // Atack state verification

// Constructor method of class, define the attributes and initialize the connection with the arduino
ArduinoHandler::ArduinoHandler() {
    serialPort = new SerialPort; // instance a seria port class
    int n = serialPort->connectSerial(); // initialize the serial connection
    if (n < 0) cout << "El control no está conectado, conectelo y reinicie la aplicación" << endl; // verify errors
}

// Function that gets the coords of the selected checker by the user
int* ArduinoHandler::getCheckerCoord() {
    char key;
    for (int i = 0; i < 2; ++i) { // get two keys events
        key = serialPort->getKey(); // get the pressed key
        if (key == DELETE) { // Deleted Button Case
            cout << "Se borró correctamente la pieza elegida" << endl;
            return getCheckerCoord();
        }
        int n = verifyKey(key); // Verify if the user press an allowed key
        if (!n){ // if press a wrong button
            cout << "Ingrese solo las entradas válidas del control" << endl;
            return getCheckerCoord();
        }
        checkerCoord[i] = (int) key - 49; // define the respective coord
        moveCoord[i] = (int) key - 49;// define the respective coord
    }
    return checkerCoord; // return an array with row and colum coord
}

// Function that checked if the pressed key is one of the allowed one
int ArduinoHandler::verifyKey(char key) {
    for (int j = 0; j < 10; ++j) {
        if (key == keys[j]) return 1;
    }
    return 0;
}

// Function that get the coords of the place where the player want to move the selected checker
int* ArduinoHandler::getMoveCoord() {
    char key;
    for (int i = 2; i < 4; ++i) {
        key = serialPort->getKey();
        if (key == DELETE && counter < 1) { // first tap of deleted key case
            cout << "Se borró correctamente el lugar de ataque" << endl;
            counter++;
            return getMoveCoord();
        }
        if (key == DELETE && counter == 1){ // Double tap deleted key case
            cout << "Se borró correctamente las entradas anteriores. Iniciando otra vez con la pieza elegida" << endl;
            counter = 0;
            int n = EXIT;
            int* goBack = &n;
            return goBack;
        }
        if (key == ATACK) { // Deleted Button Case
            atack = 1;
            cout << "Seleccione la coordenada de la ficha que quiere atacar" << endl;
            return getMoveCoord();
        }
        int n = verifyKey(key); // Verify if the user press an allowed key
        if (!n){ // if press a wrong button
            cout << "Ingrese solo las entradas válidas del control" << endl;
            return getMoveCoord();
        }
        moveCoord[i] = (int) key - 49;
    }
    return moveCoord;
}

// Function that turn on and turn off the diode in a time-lapse when the player is under attack
int ArduinoHandler::atackLed() {
    turnOnLight();
    sleep(2);
    turnOffLight();
    return 0;
}

// Function that send a char to the arduino to turn on the diode
int ArduinoHandler::turnOnLight() {
    char message = 'E';
    serialPort->writeData(message);
    return 0;
}

// Function that send a char to the arduino to turn off the diode
int ArduinoHandler::turnOffLight() {
    char message = 'F';
    serialPort->writeData(message);
    return 0;
}

// Function that close the arduino connection
int ArduinoHandler::closeSerial(){
    serialPort->closeSerial();
    delete serialPort;
    return 0;
}