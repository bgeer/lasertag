#include "irLedController.hpp"
#include "testDummy.hpp"

int main(){

    hwlib::wait_ms(1000);
    auto input 		 = hwlib::target::pin_in ( hwlib::target::pins::d11 );
	auto gnd    = hwlib::target::pin_out( hwlib::target::pins::d12 );
    auto vdd = hwlib::target::pin_out( hwlib::target::pins::d13 );

	gnd.write( 0 );
    vdd.write( 1 );
    gnd.flush();
    vdd.flush();
    auto tsop_gnd    = hwlib::target::pin_out( hwlib::target::pins::d3 );
    tsop_gnd.write(0);
    tsop_gnd.flush();
    auto ir = irLed();
    auto sender = irLedSender(ir);
    auto dummy = testDummy(sender);


    (void) sender;
    (void) dummy;
    rtos::run();



}  