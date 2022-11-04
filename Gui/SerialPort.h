#ifndef PROYECTO_2_SERIALPORT_H
#define PROYECTO_2_SERIALPORT_H

#include <stdio.h>
#include <string.h>
#include <iostream>

// Libraries for open, configurate and use the serial
#include <fcntl.h> // Contains file controls
#include <errno.h> // Error integer and strerror() function
#include <unistd.h> // write(), read(), close()

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
