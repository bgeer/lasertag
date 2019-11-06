#ifndef IR_LED
#define IR_LED

#include "hwlib.hpp"
/// @file

/// \brief
/// port used for IR led
/// \details
/// This class reserves a Port for an IR led.
class irLed {

private:

    hwlib::target::d2_36kHz ir = hwlib::target::d2_36kHz();

public: 

    irLed(){
    }
    /// \brief
    /// writes bool to port
    /// \details
    /// This function writes a bool to the port that the IR led uses.
    void write(bool n){
        ir.write(n);
        ir.flush();
    }

};

#endif
