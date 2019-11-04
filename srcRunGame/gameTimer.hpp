#ifndef GAME_TIMER_HPP
#define GAME_TIMER_HPP

#include "rtos.hpp"
#include "gameParameters.hpp"


class gameTimer : public rtos::task<> {

    rtos::clock oneSecondClock;
    gameParameters & parameters;
    bool startGame = false;
    bool &oledUpdate;

public:
    gameTimer(gameParameters & parameters, bool & oledUpdate):
        oneSecondClock(this, 1'000, "One Second Clock"),
        parameters(parameters),
        oledUpdate(oledUpdate)
    {}



    void main(){
        for(;;){
            if (startGame && parameters.getGameTime() > 0){
                wait(oneSecondClock);
                parameters.setGameTime(parameters.getGameTime() - 1);
                oledUpdate = true;
            }
        }
        hwlib::wait_ms(10);

    }

    void start(){
        startGame = true;
    }



};


#endif