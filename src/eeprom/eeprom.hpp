#ifndef EEPROM
#define EEPROM

#include <vector>

#define OE 3
#define WE 2

#define B0 8
#define B1 9
#define B2 10
#define B3 11
#define B4 12
#define B5 13
#define B6 14
#define B7 15

class eeprom {
    public:
        eeprom();
        void menu(unsigned int option, unsigned int address = 0, unsigned int data = 0, std::vector<unsigned int> dataList = {});
    private:
        void write(unsigned int address, unsigned int data);
        unsigned int read(unsigned int address);
        void readAll();
        void writeAll(std::vector<unsigned int> data);
        void configureAT28C16();
        void configureWriteEEPROM();
        void configureReadEEPROM();
        void wData(unsigned int data);
        unsigned int rData();
};

#endif