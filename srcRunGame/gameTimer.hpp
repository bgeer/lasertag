#ifndef GAME_TIMER_HPP
#define GAME_TIMER_HPP

#include "rtos.hpp"
#include "gameParameters.hpp"


class gameTimer : public rtos::task<> {

    rtos::clock oneSecondClock;
    gameParameters & parameters;
    bool startGame = false;
    rtos::flag & oledUpdateFlag;
    rtos::flag & gameOverFlag;

public:
    gameTimer(gameParameters & parameters, rtos::flag & oledUpdateFlag, rtos::flag & gameOverFlag):
        oneSecondClock(this, 1'000'000, "One Second Clock"),
        parameters(parameters),
        oledUpdateFlag(oledUpdateFlag),
        gameOverFlag(gameOverFlag)
    {}



    void main(){
        for(;;){
            wait(oneSecondClock);
            oledUpdateFlag.set();
            if (startGame && parameters.getGameTime() > 0){
                parameters.setGameTime(parameters.getGameTime() - 1);
  
            }else if(startGame){
                hwlib::cout<<"time\n";
                gameOverFlag.set();
            }
            
        }
        hwlib::wait_ms(10);

    }

    void start(){
        startGame = true;
    }



};


#endif