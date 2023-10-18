#ifndef EEPROM
#define EEPROM

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
        void menu(unsigned int option);
        void write(unsigned int address, unsigned char data);
        unsigned int read(unsigned int address);
        void readAll();
        void writeAll();
    private:
        void configureAT28C16();
        void configureWriteEEPROM();
        void configureReadEEPROM();
        void wData(unsigned char data);
        unsigned int rData();
};

#endif