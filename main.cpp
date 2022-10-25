#include "SerialPort.h"

int main(){
    char num1 = 'E';
    char num2 = 'F';
    SerialPort serialPort;
    serialPort.connectArduino();
    for (int i = 0; i < 20; ++i) {
        //serialPort.readData();
        serialPort.getKey();
    }
    serialPort.writeData(num1);
    serialPort.writeData(num2);
    serialPort.closeSerial();
    return 0;
}