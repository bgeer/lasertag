#include "hwlib.hpp"
#include "oledController.hpp"

int main(){
    // wait for the PC console to start
    hwlib::wait_ms(1000);   
   
    namespace target = hwlib::target;
   
    auto scl = target::pin_oc(target::pins::scl);
    auto sda = target::pin_oc(target::pins::sda);
   
    auto i2c_bus = hwlib::i2c_bus_bit_banged_scl_sda(scl, sda);
   
    // use the buffered version
    auto oled = hwlib::glcd_oled(i2c_bus, 0x3c);  

    auto w1 = hwlib::part(
    oled, 
    hwlib::xy(0,0), 
    hwlib::xy(128, 32));
    auto w2 = hwlib::part(
    oled,
    hwlib::xy(0,24),
    hwlib::xy(128,72));
    auto w3 = hwlib::part(
    oled,
    hwlib::xy(0,0),
    hwlib::xy(128,64));

    auto f = hwlib::font_default_8x8();
    auto f2 = hwlib::font_default_16x16();
    auto d1 = hwlib::terminal_from(w1, f);
    auto d2 = hwlib::terminal_from(w2, f);
    auto d3 = hwlib::terminal_from(w3, f2);

    oledController o(oled, d1, d2, d3);

    o.drawPlayerNumber(5);
    o.drawHpTime(100, 1530);
    o.flush();
    hwlib::wait_ms(5000);
    o.clear();
    o.drawGameOver();
    o.flush();
    hwlib::wait_ms(5000);
    o.clear();
    o.drawGameCountdown(30);
    o.flush();

    return 0;
}