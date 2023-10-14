#include "./eeprom/eeprom.cpp"

int main(){
    eeprom e;
    unsigned int address = 0x01;
    unsigned char data = 0x0F;
    e.write(address, data);
}