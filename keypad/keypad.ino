#include <Key.h>
#include <Keypad.h>

int ATACK_LED = 12; //red led
int DAMAGE_LED = 11; //green led
const int ROW_NUM = 4; //four rows
const int COLUMN_NUM = 4; //four columns

char keys[ROW_NUM][COLUMN_NUM] = {
  {'1','2','3', 'A'},
  {'4','5','6', 'B'},
  {'7','8','9', 'C'},
  {'*','0','#', 'D'}
};

byte pin_rows[ROW_NUM] = {9, 8, 7, 6}; //connect to the row pinouts of the keypad
byte pin_column[COLUMN_NUM] = {5, 4, 3, 2}; //connect to the column pinouts of the keypad

Keypad keypad = Keypad( makeKeymap(keys), pin_rows, pin_column, ROW_NUM, COLUMN_NUM );

void setup(){
  Serial.begin(9600);
  pinMode(ATACK_LED, OUTPUT);
  pinMode(DAMAGE_LED, OUTPUT);
  digitalWrite(ATACK_LED, HIGH);
  digitalWrite(DAMAGE_LED, HIGH);
}

void loop(){
  Serial.flush();
  char key = keypad.getKey();

  if (key){
    Serial.println(key);
  }

  char value = Serial.read();
  if (value == 'E'){
    digitalWrite(ATACK_LED, LOW);
  }
  if (value == 'F'){
    digitalWrite(DAMAGE_LED, LOW);
  }  
}
