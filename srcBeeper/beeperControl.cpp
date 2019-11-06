#include "beeperControl.hpp"

void beeperControl::playFreq(int freq, int times){
    int time = 1 / freq * 500;
    for(int i = 0; i < times; i++){
        beeper.write(1);
        beeper.flush();
        hwlib::wait_ms(time);
        beeper.write(0);
        beeper.flush();
        hwlib::wait_ms(time);

    }
}

void beeperControl::portamento(int start, int end, int speed){

    for(int freq = start; freq < end; freq += speed){
        playFreq(freq, 1);
    }

}

// void beeperControl::playSound1(){
//     int freq = 1500;
//     int time = 600;
//     portamento(freq, time, 1);
// }

void beeperControl::playSound1(){
       int freq = 10;
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

void beeperControl::playSound2(){
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

// void beeperControl::playSound2(){
//     int freq = 1000;
//     int time = 400;
//     portamento(freq, time, 1);
// }