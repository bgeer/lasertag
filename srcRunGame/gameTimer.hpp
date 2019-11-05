#ifndef GAME_TIMER_HPP
#define GAME_TIMER_HPP

#include "rtos.hpp"
#include "gameParameters.hpp"


class gameTimer : public rtos::task<> {

    rtos::clock oneSecondClock;
    gameParameters & parameters;
    bool startGame = false;
    rtos::flag & oledUpdateFlag;

public:
    gameTimer(gameParameters & parameters, rtos::flag & oledUpdateFlag):
        oneSecondClock(this, 1'000'000, "One Second Clock"),
        parameters(parameters),
        oledUpdateFlag(oledUpdateFlag)
    {}



    void main(){
        for(;;){
            wait(oneSecondClock);
            oledUpdateFlag.set();
            if (startGame && parameters.getGameTime() > 0){
                parameters.setGameTime(parameters.getGameTime() - 1);
  
            }
            
        }
        hwlib::wait_ms(10);

    }

    void start(){
        startGame = true;
    }



};


#endif