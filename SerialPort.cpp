// C library headers
#include "SerialPort.h"
#include <stdio.h>
#include <string.h>

// Linux headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <termios.h> // Contains POSIX terminal control definitions
#include <unistd.h> // write(), read(), close()

int SerialPort::connectArduino() {
    serial_port = open("/dev/ttyACM0", O_RDWR);

// Check for errors
    if (serial_port < 0) {
        printf("Error %i from open: %s\n", errno, strerror(errno));
    }
}

char SerialPort::readData(){
    char buffer;
    read(serial_port, &buffer, sizeof(char));
    //cout << "Key: " << buffer << endl;
    return buffer;
}

int SerialPort::getKey() {
    cout << "Key Presionada: " << readData() << endl;
    for (int i = 0; i < 2; ++i) {
        readData();
    }
    return 0;
}

int SerialPort::writeData(char data){
    unsigned char msg = data;
    write(serial_port, &msg, sizeof(msg));
    return 0;
}

int SerialPort::closeSerial() {
    close(serial_port);
}