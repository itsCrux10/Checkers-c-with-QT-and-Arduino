// C library headers
#include "SerialPort.h"
#include <stdio.h>
#include <string.h>

// Linux headers
#include <fcntl.h> // Contains file controls like O_RDWR
#include <errno.h> // Error integer and strerror() function
#include <unistd.h> // write(), read(), close()

int SerialPort::connectSerial() {
    serial_port = open("/dev/ttyACM0", O_RDWR);

// Check for errors
    if (serial_port < 0) {
        printf("Error %i from open: %s\n", errno, strerror(errno));
        return -1;
    }
    cout << "<<< Connection with Arduino was successfully correct >>>" << endl;
    return 0;
}

char SerialPort::readData(){
    char buffer;
    int n = read(serial_port, &buffer, sizeof(char));
    return buffer;
}

char SerialPort::getKey() {
    char key = readData();
    cout << "Key Presionada: " << key << endl;

    for (int i = 0; i < 2; ++i) {
        readData();
    }
    return key;
}

int SerialPort::writeData(char data){
    unsigned char msg = data;
    write(serial_port, &msg, sizeof(msg));
    return 0;
}

int SerialPort::closeSerial() {
    close(serial_port);
    cout << "<<< Connection with Arduino was successfully closed >>>" << endl;
}