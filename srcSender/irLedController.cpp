#include "irLedController.hpp"

void irLedSender::sendZero(){
    output.write(HIGH);
    hwlib::wait_us(800);
    output.write(LOW);
    hwlib::wait_us(1600);
}

void irLedSender::sendOne(){
    output.write(HIGH);
    hwlib::wait_us(1600);
    output.write(LOW);
    hwlib::wait_us(800);
}

void irLedSender::write(const uint16_t & message){

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