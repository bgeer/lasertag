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
        fiveSecondClock(this, 5'000'000, "five Second Clock"),
        parameters(parameters),
        oledUpdateFlag(oledUpdateFlag),
        gameOverFlag(gameOverFlag)
    {}



    void main(){
        for(;;){
            wait(fiveSecondClock);
            if (startGame && parameters.getGameTime() > 0){
                oledUpdateFlag.set();
                parameters.setGameTime(parameters.getGameTime() - 5);
  
            }else if(startGame){
                hwlib::cout << "time out\n";
                gameOverFlag.set();
            }
            
        }
        hwlib::wait_ms(10);

    }

    void start(){
        startGame = true;
    }

    bool getStartGame_gameTimer(){
        return startGame;
    }

};


#endif