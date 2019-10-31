#include "hwlib.hpp"
#include "rtos.hpp"

#include "../srcSender/irLedController.hpp"
#include "irReciever.hpp"

int main() {
    // Wait for the PC console to start
    hwlib::wait_ms(2000);


    auto input  = hwlib::target::pin_in ( hwlib::target::pins::d11 );
	auto gnd    = hwlib::target::pin_out( hwlib::target::pins::d12 );
    auto vdd    = hwlib::target::pin_out( hwlib::target::pins::d13 );

	gnd.write( 0 );
    vdd.write( 1 );
    gnd.flush();
    vdd.flush();
    auto tsop_gnd = hwlib::target::pin_out( hwlib::target::pins::d3 );
    tsop_gnd.write(0);
    tsop_gnd.flush();
    auto ir = irLed();
    auto sender = irLedSender(ir, 200);
    auto logger = msg_logger();
    auto decoder = msg_decoder(logger);
    auto detector = pause_detector(decoder, input);
    rtos::run();

}
