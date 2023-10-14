#include "eeprom.hpp"
#include <iostream>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "../lib/74HC245/C74HC245.cpp"
#include "../lib/74HC595/C74HC595.cpp"

eeprom::eeprom(){
    configure();
}

void eeprom::read(unsigned int address){}

void eeprom::readAll(){}

void eeprom::write(unsigned char address, unsigned char data){
    c74hc595 ci595;
    c74hc245 ci245(1);

    ci595.setAddress(address);
    ci245.wData(data);
}

void eeprom::writeAll(){}