#include "gameLeaderController.hpp"
#include "bitHelper.hpp"

uint16_t gameLeaderController::makedata( uint8_t valueL, uint8_t valueR, int sizeL ) {
    uint16_t data = 0x00;

    for (int i = sizeL - 1; i >= 0; i--) {
        bool bit = (valueL & (1 << i));
        data |= bit << (15 - (sizeL - i));
    }
    for (int i = 10 - sizeL - 1; i >= 0; i--) {
        bool bit = (valueR & (1 << i));
        data |= bit << (15 - (10 - i));
    }
    
    return encode(data);
}

void gameLeaderController::playerconfig() {
    state = gameLeaderStates::SHOW_BEGIN;

    for(;;) {
        switch(state) {
        
        case gameLeaderStates::SHOW_BEGIN:

            screen1.write16x16("Waiting\0");
            screen2.write8x8("================\npress *\nto continue..\0");
            screen1.flush();
            state = gameLeaderStates::IDLE;
            break;
        
        case gameLeaderStates::IDLE:
            for(;;){
                if (matrix.pressed() == '*') {
                    state = gameLeaderStates::CONFIG_PLAYERS;
                    break;
                }
            }
            break;

        case gameLeaderStates::CONFIG_PLAYERS:
            screen1.clear();
            char text[12] = "Player:\n  \0";
            for(unsigned int i = 1; i <= MAXPLAYERS; i++) {
                if (i >= 30) {
                    text[8] = '3';
                    text[9] = char(i - 30) + '0';
                } else if (i >= 20) {
                    text[8] = '2';
                    text[9] = char(i - 20) + '0';
                } else if (i >= 10) {
                    text[8] = '1';
                    text[9] = char(i - 10) + '0';
                } else {
                    text[8] = char(i) + '0';
                }
                
                screen1.write16x16(text);
                char poweradd[20] = 
                for (;;) {
                    screen2.write8x8("================\nPower:\0");
                    screen1.flush();
                }
                
                hwlib::wait_ms(1000);
            }
            break;
            
        // case gameLeaderStates::SEND_CONFIG:
        //     for(;;){
        //         hwlib::cout << "jdhbawjdbh";
        //     }
        }
    }
}