#include "ArduinoHandler.h"

using namespace std;

ArduinoHandler arduinoHandler;

int getMove(){
    int* checker = arduinoHandler.getCheckerCoord();
    // Aquí iría la función para iluminar los posibles movimientos
    cout << "[" << checker[0] << ", " << checker[1] << "]" << endl;
    int* move = arduinoHandler.getMoveCoord();
    if (*move == 9) return getMove();
    else{
        cout << "[" << move[0] << ", " << move[1] << ", " << move[2] << ", " << move[3] << "]"<< endl;
        return 0;
    }
}

int main(){
    getMove();
    arduinoHandler.atackLed();
    arduinoHandler.closeSerial();
    return 0;
}
