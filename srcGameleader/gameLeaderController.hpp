#ifndef GAMELEADERCONTROLLER_HPP
#define GAMELEADERCONTROLLER_HPP

#define MAXPLAYERS 31

#include "rtos.hpp"
#include "hwlib.hpp"
#include "terminal.hpp"
#include "duration.hpp"
#include "/home/daanzvw/LazerGameProject/lasertag/srcSender/irLedController.hpp"
/// @file



/// \brief
/// Task that initialises the players.
/// \details
/// This taks is used to initialise all the players 
/// by player id, weapon power, remaining time until game starts and game time.
class gameLeaderController : public rtos::task<> {
private:
    enum class gameLeaderStates {SHOW_BEGIN, IDLE, CONFIG_PLAYERS, SEND_CONFIG};
    gameLeaderStates state;

    char playerPower[31];
    unsigned int playerIndex = 0;

    irLedSender &sender;
    terminal &screen1;
    terminal &screen2;
    hwlib::keypad<16> &matrix;

    duration &clock;
    gameTimeEntity &time;

    uint16_t makedata( uint8_t valueL, uint8_t valueR, int sizeL );

public:

    gameLeaderController(
        irLedSender &sender,
        terminal &screen1,
        terminal &screen2,
        hwlib::keypad<16> &matrix,
        duration &clock,
        gameTimeEntity &time
    ):
        task("gameLeaderController"),
        sender( sender ),
        screen1( screen1 ),
        screen2( screen2 ),
        matrix( matrix ),
        clock( clock ),
        time( time )
    {}

    void main(); 

};





#endif /* GAMELEADERCONTROLLER_HPP */
