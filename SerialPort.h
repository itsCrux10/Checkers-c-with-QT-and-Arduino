#ifndef PROYECTO_2_SERIALPORT_H
#define PROYECTO_2_SERIALPORT_H

#include <stdio.h>
#include <string.h>
#include <iostream>

using namespace std;

class SerialPort
{
private:
    int serial_port;
public:
    int connectSerial();
    int writeData(char data);
    int closeSerial();
    char getKey();

private:
    char readData();
};

#endif //PROYECTO_2_SERIALPORT_H
