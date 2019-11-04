#ifndef IR_LED_CONTROLLER
#define IR_LED_CONTROLLER

#define HIGH 1
#define LOW 0

#include "irLed.hpp"
#include <rtos.hpp>


class irLedSender : public rtos::task<>{

private:

    irLed &output;
    rtos::channel<uint16_t, 10> uintChannel;
    

public:

    irLedSender(irLed &output):
        task("irLedSender"),
        output(output),
        uintChannel(this, "uintChannel")
    {}

private:

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

public:

    void writeChannel(const uint16_t & message){
        uintChannel.write(message);
    }


    void main() override {


        for(;;){
            auto message = uintChannel.read();
            write(message); 
        }
    }

};


#endif










