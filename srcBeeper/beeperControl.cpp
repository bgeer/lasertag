#include "beeperControl.hpp"

void beeperControl::playFreq(int freq, int times){
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

void beeperControl::portamento(int start, int end, int speed){

    for(unsigned int freq = start, freq < end, freq += speed){
        playFreq(freq, 1);
    }

}

void beeperControl::playSound1(){
    int freq = 500;
    int time = 600;
    portamento(freq, time)
}

void beeperControl::playSound2(int wp){
    int freq = 1 + (wp*10);
    int time = 400;
    portamento(freq, time)
}