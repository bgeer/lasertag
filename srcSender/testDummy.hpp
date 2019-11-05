#include "irLedController.hpp"
#include "rtos.hpp"
#include "../srcGameleader/bitHelper.hpp"

class testDummy : public rtos::task<> { 

private:

    uint16_t testMessage1 = 0b1000100010000000;
    uint16_t testMessage2 = 0b1010000010000000;
    uint16_t testMessage3 = 0b1000011111110000;
    irLedSender & sender;

public: 

    testDummy(irLedSender & sender):
        task("DUMMY TEST"),
        sender(sender)
        {}

        
    void main(){

            for(;;){
                hwlib::cout << (encode(testMessage3)) << "\n";
                sender.writeChannel(encode(testMessage3));
                hwlib::wait_ms(200);
            }
        
    



    }

};