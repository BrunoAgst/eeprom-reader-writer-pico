#include "./eeprom/eeprom.cpp"
#include <vector>

int main(){
    std::vector<unsigned int> myVector = {15, 240, 239, 3, 4, 5};
    eeprom e;
    e.menu(4, 0x00, 0x00, myVector);
}