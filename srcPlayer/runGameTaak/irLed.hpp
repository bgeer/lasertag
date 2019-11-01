#ifndef IR_LED
#define IR_LED

#include "hwlib.hpp"

class irLed {

private:

    hwlib::target::d2_36kHz ir = hwlib::target::d2_36kHz();

public: 

    irLed(){
    }
    void write(bool n){
        ir.write(n);
        ir.flush();
    }

};

#endif