#ifndef IR_LED_CONTROLLER
#define IR_LED_CONTROLLER

#define HIGH 1
#define LOW 0

#include "irLed.hpp"
#include <rtos.hpp>

#include "/home/pieper/TI-PROJECT-IR/IR_RECIEVER/bitHelper.hpp"

class irLedSender : public rtos::task<>{

private:

    irLed &output;
    rtos::channel<uint16_t, 10> uintChannel;
    int ID;

public:

    irLedSender(irLed &output, int p_ID):
        task("irLedSender"),
        output(output),
        uintChannel(this, "uintChannel"),
        ID(p_ID)
    {}

    void sendZero(){
        output.write(HIGH);
        hwlib::wait_us(800);
        output.write(LOW);
        hwlib::wait_us(1600);
    }

    void sendOne(){
        output.write(HIGH);
        hwlib::wait_us(1600);
        output.write(LOW);
        hwlib::wait_us(800);
    }

    void write(const uint16_t & message){
        auto p_message = message;
        encode(p_message);
        sendOne();
        hwlib::wait_us(3500);
        
        for(int j = 0; j < 2; j++){

            for(int i = 15; i > -1; i--){
                if (1 & (message >> i)) {
                    sendOne();
                } else {
                    sendZero();
                }
            }  

        }
    }




    void main() override {

        for(;;){
            hwlib::wait_ms(1000);
            write(ID); 
        }
    }

};


#endif










