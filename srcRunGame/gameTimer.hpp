#ifndef GAME_TIMER_HPP
#define GAME_TIMER_HPP

#include "rtos.hpp"
#include "gameParameters.hpp"

/// @file a rtos task to time the clock
class gameTimer : public rtos::task<> {

    rtos::clock fiveSecondClock;
    gameParameters & parameters;
    bool startGame = false;
    rtos::flag & oledUpdateFlag;
    rtos::flag & gameOverFlag;

public:
    /// @brief constructor
    /// @param parameters entity class to store game parameters
    /// @param oledUpdateFlag rtos flag to update the oled
    /// @param gameOverFlag rtos flag to signal that the game is over
    gameTimer(gameParameters & parameters, rtos::flag & oledUpdateFlag, rtos::flag & gameOverFlag):
        fiveSecondClock(this, 5'000'000, "five Second Clock"),
        parameters(parameters),
        oledUpdateFlag(oledUpdateFlag),
        gameOverFlag(gameOverFlag)
    {}


    /// @brief void main, endless loop
    /// @details this function updates the oled every 5 seconds, if the time gets below 0 the game over flag will be set
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

    /// @brief used to start the game after the countdown
    void start(){
        startGame = true;
    }

    /// @brief used to check if the game has started
    bool getStartGame_gameTimer(){
        return startGame;
    }

};


#endif