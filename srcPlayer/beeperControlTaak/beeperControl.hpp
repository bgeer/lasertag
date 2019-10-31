#ifndef BEEPERCONTROL_HPP
#define BEEPERCONTROL_HPP


#include "hwlib.hpp"

class beeperControl{
private:
    hwlib::pin_out & beeper;
public:
    beeperControl(hwlib::pin_out & beeper):
    beeper(beeper)
    {}

    void playSound1(){
        int freq = 500;
        int time = 600;
        for(int i = 0; i < time; i++){
            beeper.write(1);
            beeper.flush();
            hwlib::wait_us(freq);
            beeper.write(0);
            beeper.flush();
            hwlib::wait_us(freq);
            freq += 1;
        }
    }

    void playSound2(int wp){
        int freq = 1 + (wp*10);
        int time = 400;
        for(int i = 0; i < time; i++){
            beeper.write(1);
            beeper.flush();
            hwlib::wait_us(freq);
            beeper.write(0);
            beeper.flush();
            hwlib::wait_us(freq);
            freq += 1;
        }
    }
};

#endif