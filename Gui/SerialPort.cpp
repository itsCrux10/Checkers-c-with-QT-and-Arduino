#include "SerialPort.h"

// Function that create a structure for connect to the USB serial with the Arduino UNO
int SerialPort::connectSerial() {
    serial_port = open("/dev/ttyACM0", O_RDWR); // Initialize the connection

// Check for errors
    if (serial_port < 0) {
        printf("Error %i from open: %s\n", errno, strerror(errno));
        return -1;
    }
    cout << "<<< Connection with Arduino was successfully correct >>>" << endl;
    return 0;
}

// Function that gets and read a byte and interpreted as char
char SerialPort::readData(){
    char buffer;
    int n = read(serial_port, &buffer, sizeof(char)); // read a byte from serial
    return buffer;
}

// Function that gets the key pressed by the user
char SerialPort::getKey() {
    char key = readData();
    cout << "Key Presionada: " << key << endl; // get key

    for (int i = 0; i < 2; ++i) { //
        readData(); // Discard the next two chars (that is because when a key its press generate 3 chars for no reason, the first one is the key, and the next two are trash)
    }
    return key;
}

// Function that send a char to the serial
int SerialPort::writeData(char data){
    unsigned char msg = data; // the message given
    write(serial_port, &msg, sizeof(msg)); // send it to serial
    return 0;
}

// Function that close the connection with the serial
int SerialPort::closeSerial() {
    close(serial_port);
    cout << "<<< Connection with Arduino was successfully closed >>>" << endl;
}