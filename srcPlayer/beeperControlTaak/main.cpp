#include "hwlib.hpp"
#include "beeperControl.hpp"

int main(){
    hwlib::wait_ms(1000);
    namespace target = hwlib::target;
    auto beeper = target::pin_out( target::pins::d8 );

    beeperControl pieper(beeper);
    pieper.playSound2(9);
    
}