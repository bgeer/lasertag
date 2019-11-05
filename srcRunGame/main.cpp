#include "runGame.hpp"
#include "rtos.hpp"
#include "../srcTrigger/trigger.hpp"
#include "../srcSender/irLedController.hpp"
#include "../srcSender/irLed.hpp"
#include "../srcReciever/irReciever.hpp"
#include "oledController.hpp"


int main(){
    hwlib::wait_ms(1000);
    //initialise oled
    //====================================================================
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
    //====================================================================



    //receiver pins
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
    runGame player(senderTask, o);
    

    auto decoderTask = msg_decoder(player);
    auto detectorTask = pause_detector(decoderTask, receiverInput);
    auto triggerTask = trigger(player);

    (void) decoderTask;
    (void) detectorTask;
    (void) triggerTask;

    rtos::run();
}