#include "C74HC245.hpp"
#include <iostream>
#include "pico/stdio.h"
#include "hardware/gpio.h"

c74hc245::c74hc245(int RW){
    configure(RW);
}

void c74hc245::configure(int RW){
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

void c74hc245::rData(){}

void c74hc245::wData(unsigned char data){
    std::cout << "74HC245:" << std::endl;
    for(int i = 8; i <= 16; i++){
        gpio_put(i, data & (1 << (15 - i)) ? 1 : 0);
    }
}