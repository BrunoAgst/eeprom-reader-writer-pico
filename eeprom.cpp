#include "eeprom.hpp"
#include <iostream>
#include "pico/stdlib.h"
#include "hardware/gpio.h"

eeprom::eeprom(){};

void eeprom::config74HC245(int RW){
    stdio_init_all();

    gpio_init(DIR);
    gpio_set_dir(DIR, RW);

    gpio_init(B0);
    gpio_set_dir(B0, RW);

    gpio_init(B1);
    gpio_set_dir(B1, RW);

    gpio_init(B2);
    gpio_set_dir(B2, RW);

    gpio_init(B3);
    gpio_set_dir(B3, RW);

    gpio_init(B4);
    gpio_set_dir(B4, RW);

    gpio_init(B5);
    gpio_set_dir(B5, RW);

    gpio_init(B6);
    gpio_set_dir(B6, RW);

    gpio_init(B7);
    gpio_set_dir(B7, RW);
}

void eeprom::config74HC595(){
    stdio_init_all();

    gpio_init(DATA);
    gpio_set_dir(DATA, GPIO_OUT);

    gpio_init(SH_CP);
    gpio_set_dir(SH_CP, GPIO_OUT);

    gpio_init(ST_CP);
    gpio_set_dir(ST_CP, GPIO_OUT);

    gpio_put(ST_CP, 0);
    gpio_put(SH_CP, 0);
}

void eeprom::execute74HC595(unsigned int data){
    config74HC595();
    std::cout << "74HC595:" << std::endl;
    for(int i = 0; i < 8; i++){
        gpio_put(DATA, data & (1 << (7 - i)) ? 1 : 0);
        gpio_put(SH_CP, 1);
        sleep_ms(5);
        gpio_put(SH_CP, 0);
    }
    gpio_put(ST_CP, 1);
    sleep_ms(5);
    gpio_put(ST_CP, 0);
}

void eeprom::execute74HC245(int DIRECTION, unsigned char data){
    config74HC245(DIRECTION);
    std::cout << "74HC245:" << std::endl;
    for(int i = 8; i <= 16; i++){
        gpio_put(i, data & (1 << (15 - i)) ? 1 : 0);
    }
}