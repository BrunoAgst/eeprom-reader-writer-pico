#include "eeprom.hpp"
#include <iostream>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "../lib/74HC595/C74HC595.cpp"

eeprom::eeprom(){
    configureAT28C16();
}

void eeprom::menu(unsigned int option){
    unsigned int data = read(0x01);
    std::cout << "Data: " << data << std::endl;
}

unsigned int eeprom::read(unsigned int address){
    c74hc595 ci595;

    ci595.setAddress(address);
    configureReadEEPROM();
    gpio_put(OE, 0);
    return rData();
}

void eeprom::readAll(){}

void eeprom::write(unsigned int address, unsigned char data){
    c74hc595 ci595;

    ci595.setAddress(address);
    configureWriteEEPROM();
    gpio_put(OE, 1);
    wData(data);
    gpio_put(WE, 0);
    sleep_ms(1);
    gpio_put(WE, 1);
    sleep_ms(1);
}


void eeprom::writeAll(){}

void eeprom::configureAT28C16(){
    stdio_init_all();

    gpio_init(OE);
    gpio_set_dir(OE, GPIO_OUT);
    
    gpio_init(WE);
    gpio_set_dir(WE, GPIO_OUT);
}

void eeprom::configureWriteEEPROM(){
    stdio_init_all();

    gpio_init(B0);
    gpio_set_dir(B0, GPIO_OUT);

    gpio_init(B1);
    gpio_set_dir(B1, GPIO_OUT);

    gpio_init(B2);
    gpio_set_dir(B2, GPIO_OUT);
  
    gpio_init(B3);
    gpio_set_dir(B3, GPIO_OUT);

    gpio_init(B4);
    gpio_set_dir(B4, GPIO_OUT);

    gpio_init(B5);
    gpio_set_dir(B5, GPIO_OUT);

    gpio_init(B6);
    gpio_set_dir(B6, GPIO_OUT);

    gpio_init(B7);
    gpio_set_dir(B7, GPIO_OUT);
}

void eeprom::configureReadEEPROM(){
    stdio_init_all();

    gpio_init(B0);
    gpio_set_dir(B0, GPIO_IN);

    gpio_init(B1);
    gpio_set_dir(B1, GPIO_IN);

    gpio_init(B2);
    gpio_set_dir(B2, GPIO_IN);

    gpio_init(B3);
    gpio_set_dir(B3, GPIO_IN);

    gpio_init(B4);
    gpio_set_dir(B4, GPIO_IN);

    gpio_init(B5);
    gpio_set_dir(B5, GPIO_IN);

    gpio_init(B6);
    gpio_set_dir(B6, GPIO_IN);

    gpio_init(B7);
    gpio_set_dir(B7, GPIO_IN);
}

void eeprom::wData(unsigned char data){
    std::cout << "WRITE EEPROM" << std::endl;
    for(int i = B0; i <= B7; i++){
        gpio_put(i, data & (1 << (15 - i)) ? 1 : 0);
        sleep_ms(1);
    }
}

unsigned int eeprom::rData(){
    unsigned int data = 0;
    std::cout << "READ EEPROM" << std::endl;
    for(int i = B0; i <= B7; i++){
        int dataValue = gpio_get(i);
        data = (data << 1) + dataValue;
        sleep_ms(1);
    }

    return data;
}