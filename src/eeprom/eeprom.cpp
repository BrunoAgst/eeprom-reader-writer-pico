#include "eeprom.hpp"
#include <iostream>
#include <iomanip>
#include <vector>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#include "../lib/74HC595/C74HC595.cpp"

eeprom::eeprom(){
    configureAT28C16();
}

void eeprom::menu(unsigned int option, unsigned int address, unsigned int data, std::vector<unsigned int> dataList){
    switch(option){
        case 1:
            write(address, data);
            break;
        case 2:
            writeAll(dataList);
            break;
        case 3:
            { 
                unsigned int dataValue = read(address);
                std::cout << "Data: " "0x" << std::setfill('0') << std::setw(2) << std::hex << dataValue << std::endl; 
                break;
            }
        case 4:
            readAll();
            break;
        default:
            std::cout << "Invalid Option" << std::endl;
            break;
    }
}

unsigned int eeprom::read(unsigned int address){
    c74hc595 ci595;

    ci595.setAddress(address);
    configureReadEEPROM();
    gpio_put(OE, 0);
    return rData();
}

void eeprom::readAll(){
    c74hc595 ci595;

    configureReadEEPROM();
    gpio_put(OE, 0);
    unsigned int data = 0;
    int line = 0;

    std::cout << "---------------------------------------------------------------------------------------------------" << std::endl;
    for(int i = 0; i < 256; i++){
        ci595.setAddress(i);
        data = rData();
        if(line == 20){
            std::cout << "\n";
            line = 0;
        }
        std::cout << "0x" << std::setfill('0') << std::setw(2) << std::hex << data << " ";
        line++;
        sleep_ms(5);
    }
    std::cout << "\n---------------------------------------------------------------------------------------------------" << std::endl;

}

void eeprom::write(unsigned int address, unsigned int data){
    c74hc595 ci595;

    ci595.setAddress(address);
    configureWriteEEPROM();
    gpio_put(OE, 1);
    wData(data);
    gpio_put(WE, 0);
    sleep_ms(1);
    gpio_put(WE, 1);
    sleep_ms(1);
    std::cout << "Record " << "0x" << std::setfill('0') << std::setw(2) << std::hex << data << " in  address" << "0x" << std::setfill('0') << std::setw(2) << std::hex << address << std::endl; 

}

void eeprom::writeAll(std::vector<unsigned int> data){

    c74hc595 ci595;

    configureWriteEEPROM();
    std::cout << "Recording..." << std::endl;
    for(int i = 0; i < data.size(); i++){
        ci595.setAddress(i);
        gpio_put(OE, 1);
        wData(data[i]);
        gpio_put(WE, 0);
        sleep_ms(1);
        gpio_put(WE, 1);
        sleep_ms(5);
    }
    
    std::cout << "Finish" << std::endl;

}

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

void eeprom::wData(unsigned int data){
    for(int i = B0; i <= B7; i++){
        gpio_put(i, data & (1 << (15 - i)) ? 1 : 0);
        sleep_ms(1);
    }
}

unsigned int eeprom::rData(){
    unsigned int data = 0;
    for(int i = B0; i <= B7; i++){
        int dataValue = gpio_get(i);
        data = (data << 1) + dataValue;
        sleep_ms(1);
    }

    return data;
}