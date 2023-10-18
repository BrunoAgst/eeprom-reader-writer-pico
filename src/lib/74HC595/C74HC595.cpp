#include "c74hc595.hpp"
#include <iostream>
#include "pico/stdio.h"
#include "hardware/gpio.h"

c74hc595::c74hc595(){
    configure();
}

void c74hc595::configure(){
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

void c74hc595::setAddress(unsigned int address){
    for(int i = 0; i < 8; i++){
        gpio_put(DATA, address & (1 << (7 - i)) ? 1 : 0);
        gpio_put(SH_CP, 1);
        sleep_ms(1);
        gpio_put(SH_CP, 0);
    }
    gpio_put(ST_CP, 1);
    sleep_ms(5);
    gpio_put(ST_CP, 0);
}