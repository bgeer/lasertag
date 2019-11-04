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

    void playFreq(int freq, int times){
        int time = 1 / freq * 500;
        for(unsigned int i = 0; i < times; i++){
            beeper.write(1);
            beeper.flush();
            hwlib::wait_ms(time);
            beeper.write(0);
            beeper.flush();
            hwlib::wait_ms(time);

        }
    }

    void portamento(int start, int end, int speed){

        for(unsigned int freq = start, freq < end, freq += speed){
            playFreq(freq, 1);
        }

    }

    void playSound1(){
        int freq = 500;
        int time = 600;
        portamento(freq, time)
    }

    void playSound2(int wp){
        int freq = 1 + (wp*10);
        int time = 400;
        portamento(freq, time)
    }
};

#endif