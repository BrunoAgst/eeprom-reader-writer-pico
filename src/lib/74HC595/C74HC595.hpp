#ifndef C74HC595
#define C74HC595

#define DATA 21
#define SH_CP 18
#define ST_CP 19
#define DATA_LENGTH 8

class c74hc595 {
    public:
        c74hc595();
        void setAddress(unsigned int address);
    private:
        void configure();
};

#endif