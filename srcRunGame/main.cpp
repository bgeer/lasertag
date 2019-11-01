#include "runGame.hpp"
#include "rtos.hpp"

#include "../srcSender/irLedController.hpp"
#include "../srcSender/irLed.hpp"
#include "../srcReciever/irReciever.hpp"


int main(){
    hwlib::wait_ms(1000);
    auto receiverInput  = hwlib::target::pin_in ( hwlib::target::pins::d11 );
	auto receiverGnd    = hwlib::target::pin_out( hwlib::target::pins::d12 );
    auto receiverVdd    = hwlib::target::pin_out( hwlib::target::pins::d13 );

	receiverGnd.write( 0 );
    receiverVdd.write( 1 );
    receiverGnd.flush();
    receiverVdd.flush();




    auto irLedGnd    = hwlib::target::pin_out( hwlib::target::pins::d3 );
    irLedGnd.write(0);
    irLedGnd.flush();
    auto ir = irLed();
    auto senderTask = irLedSender(ir);
    runGame player(senderTask);
    
    
    auto decoderTask = msg_decoder(player);
    auto detectorTask = pause_detector(decoderTask, receiverInput);

    rtos::run();

    //hwlib::cout<<player101.checkMessage()<<hwlib::endl;
}