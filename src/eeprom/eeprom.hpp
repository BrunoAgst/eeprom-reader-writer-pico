#ifndef EEPROM
#define EEPROM

#define DATA 21
#define SH_CP 18
#define ST_CP 19
#define DATA_LENGTH 8

#define DIR 7
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
        void write(unsigned char address, unsigned char data);
        void read(unsigned int address);
        void readAll();
        void writeAll();
    private:
        void configure();
};

#endif