#ifndef C74HC245
#define C74HC245

#define DIR 7
#define B0 8
#define B1 9
#define B2 10
#define B3 11
#define B4 12
#define B5 13
#define B6 14
#define B7 15

class c74hc245 {
    public:
        c74hc245(int RW);
        void rData();
        void wData(unsigned char data);
    private:
        void configure(int RW);
};

#endif