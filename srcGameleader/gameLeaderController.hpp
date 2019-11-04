#ifndef GAMELEADERCONTROLLER_HPP
#define GAMELEADERCONTROLLER_HPP

#define MAXPLAYERS 31

#include "rtos.hpp"
#include "hwlib.hpp"
#include "terminal.hpp"
#include "/home/daanzvw/LazerGameProject/lasertag/srcSender/irLedController.hpp"

#define ever ;;


class gameLeaderController : public rtos::task<> {
private:

    rtos::clock oneSecondClock;

    enum class gameLeaderStates {SHOW_BEGIN, IDLE, CONFIG_PLAYERS, SEND_CONFIG};
    gameLeaderStates state;

    char playerPower[31];
    unsigned int playerIndex = 0;

    irLedSender &sender;
    terminal &screen1;
    terminal &screen2;
    hwlib::keypad<16> &matrix;

    uint16_t makedata( uint8_t valueL, uint8_t valueR, int sizeL );

public:

    gameLeaderController(
        irLedSender &sender,
        terminal &screen1,
        terminal &screen2,
        hwlib::keypad<16> &matrix
    ):
        task("gameLeaderController"),
        oneSecondClock( this, 1'000, "oneSecondClock" ),
        sender( sender ),
        screen1( screen1 ),
        screen2( screen2 ),
        matrix( matrix )
    {}

    void playerconfig();

    void main () {
        for (ever){
            hwlib::wait_us(0);
        }
    } 

};





#endif /* GAMELEADERCONTROLLER_HPP */