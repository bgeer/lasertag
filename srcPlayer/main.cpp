#include "hwlib.hpp"
#include "oledController.hpp"

void main(){
    // wait for the PC console to start
    hwlib::wait_ms(1000);   
   
    namespace target = hwlib::target;
   
    auto scl = target::pin_oc(target::pins::scl);
    auto sda = target::pin_oc(target::pins::sda);
   
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);
   
    // use the buffered version
    auto oled = hwlib::glcd_oled(i2c_bus, 0x3c);  

    oledController o(oled);

    return 0;
}