
#include "gameParameters.hpp"


class gameTimer: public rtos::task {

    rtos::clock oneSecondClock;
    gameParameters & parameters;
    bool startGame = false;
    rtos::flag oledFlag;


    gameTimer(gameParameters & parameters, rtos::flag & oledFlag:
        oneSecondClock(this, 1'000, "One Second Clock");
        parameters(parameters),
        game(game)
    {}



    void main(){
        for(;;){
            if (startGame && parameters.getGameTime() > 0){
                wait(oneSecondClock);
                parameters.setGameTime(parameters.getGameTime()--);
                oledFlag.set();
            }
        }
        hwlib::wait_ms(10);

    }

    void start(){
        startGame = true;
    };



}