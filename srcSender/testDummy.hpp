#include "irLedController.hpp"
#include "rtos.hpp"
#include "../srcGameleader/bitHelper.hpp"

class testDummy : public rtos::task<> { 

private:

    uint16_t testMessage1 = 0b0000100010000000;
    uint16_t testMessage2 = 0b0010000010000000;
    uint16_t testMessage3 = 0b1100001111100000;
    irLedSender & sender;

public: 

    testDummy(irLedSender & sender):
        task("DUMMY TEST"),
        sender(sender)
        {}

        
    void main(){

        for(;;){
            hwlib::wait_ms(100);
            sender.writeChannel(encode(testMessage1));
            hwlib::wait_ms(500);
            sender.writeChannel(encode(testMessage2));
            for(;;){
                sender.writeChannel(encode(testMessage3));
                hwlib::wait_ms(1000);
            }
        
        }



    }

};