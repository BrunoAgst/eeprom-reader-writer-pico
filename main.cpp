#include "eeprom.cpp"

int main(){
    eeprom e;
    e.execute74HC595(0x05);
    e.execute74HC245(1, 0x05);
}