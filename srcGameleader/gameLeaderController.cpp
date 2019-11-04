#include "gameLeaderController.hpp"
#include "bitHelper.hpp"

uint16_t gameLeaderController::makedata( uint8_t valueL, uint8_t valueR, int sizeL ) {
    uint16_t data = 0x8000;

    for (int i = sizeL - 1; i >= 0; i--) {
        bool bit = (valueL & (1 << i));
        data |= bit << (15 - (sizeL - i));
    }
    for (int i = 10 - sizeL - 1; i >= 0; i--) {
        bool bit = (valueR & (1 << i));
        data |= bit << (15 - (10 - i));
    }
    
    return data;
}

void gameLeaderController::main() {
    state = gameLeaderStates::SHOW_BEGIN;

    for(;;) {
    
    switch(state) {
    
    case gameLeaderStates::SHOW_BEGIN:
    {
        screen1.write16x16("Start\nGame\0");
        screen2.write8x8("================\npress *\nto continue..\0");
        screen1.flush();
        state = gameLeaderStates::IDLE;
    }
    break; 
    
    case gameLeaderStates::IDLE:
    {
        for(;;){
            if (matrix.pressed() == '*') {
                state = gameLeaderStates::CONFIG_PLAYERS;
                break;
            }
        }
    }   
    break;

    case gameLeaderStates::CONFIG_PLAYERS:
    {   
        screen1.clear();
        char text[] = "Player:\n  \0";
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
            char text2[] = "================\nPower(1/8):  \nContinue: *\nDone: #\0";
            char numbers[] = "12345678";
            screen2.write8x8(text2);
            screen1.flush();
            
            char tmpPowerValue = '\0';

            for (;;) {
                char matrixInfo = matrix.pressed();
                if (matrixInfo != '\0'){
                    if (matrixInfo == '*' && tmpPowerValue != '\0') {
                        playerPower[i-1] = tmpPowerValue;
                        playerIndex++;
                        break;
                    } else if (matrixInfo == '#' && tmpPowerValue != '\0') {
                        playerPower[i-1] = tmpPowerValue;
                        playerIndex++;
                        state = gameLeaderStates::SEND_CONFIG;
                        break;
                    }
                    for (unsigned int i = 0; i < 8; i++) {
                        if (matrixInfo == numbers[i]) {
                            text2[29] = matrixInfo;
                            tmpPowerValue = matrixInfo;
                            screen2.write8x8(text2);
                            screen1.flush();
                            break;
                        }
                    }
                }  
            }
            if (state == gameLeaderStates::SEND_CONFIG) {
                break;
            }
            
        }
        state = gameLeaderStates::SEND_CONFIG;
    }
    break;
        
    case gameLeaderStates::SEND_CONFIG:
    {   
        time.set(127);
        clock.start();

        screen1.clear();
        char text[] = "Player:\n  \0";
        char text2[] = "================\nPower:  \nNext Player: *\nFlash: #\0";
        for(unsigned int i = 1; i <= playerIndex; i++) {
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
            text2[24] = playerPower[i-1];
            screen1.write16x16(text);
            screen2.write8x8(text2);
            screen1.flush();
            
            bool isFlashed = false;
            bool pressed = false;
            for (;;) {
                hwlib::wait_ms(10);

                char matrixInfo = matrix.pressed();
                if (matrixInfo != '\0') {
                    if (matrixInfo == '*' && isFlashed) {
                        break;
                    } else if (matrixInfo == '#' && !pressed) {
                        pressed = true;
                        isFlashed = true;
                        uint16_t firstMessage = makedata(i, 10, 5);
                        uint16_t secondMessage = makedata(playerPower[i - 1], time.get(), 3);

                        bool tmp;
                        hwlib::cout << "i: " << i << " gametime: 10 lvalue: 5\n";
                        for (int i = 0; i < 16; i++) {
                            tmp = firstMessage & (1 << i);
                            hwlib::cout << tmp;
                        }
                        hwlib::cout << "\n\nPower: " << playerPower[i-1] << " time.get(): " << time.get() << " lvalue: 3\n";
                        for (int i = 0; i < 16; i++) {
                            tmp = secondMessage & (1 << i);
                            hwlib::cout << tmp;
                        }
                        hwlib::cout << hwlib::endl;
                    } 
                } else {
                    pressed = false;
                }
            }
        }
        state = gameLeaderStates::SHOW_BEGIN;
        playerIndex = 0;
    }
    clock.stop();
    break;
    }
    }
}








// void gameLeaderController::playerconfig() {
//     state = gameLeaderStates::SHOW_BEGIN;

//     for(;;) {
    
//     switch(state) {
    
//     case gameLeaderStates::SHOW_BEGIN:
//     {
//         screen1.write16x16("Start\nGame\0");
//         screen2.write8x8("================\npress *\nto continue..\0");
//         screen1.flush();
//         state = gameLeaderStates::IDLE;
//     }
//     break; 
    
//     case gameLeaderStates::IDLE:
//     {
//         for(;;){
//             if (matrix.pressed() == '*') {
//                 state = gameLeaderStates::CONFIG_PLAYERS;
//                 break;
//             }
//         }
//     }   
//     break;

//     case gameLeaderStates::CONFIG_PLAYERS:
//     {
//         screen1.clear();
//         char text[] = "Player:\n  \0";
//         for(unsigned int i = 1; i <= MAXPLAYERS; i++) {
//             if (i >= 30) {
//                 text[8] = '3';
//                 text[9] = char(i - 30) + '0';
//             } else if (i >= 20) {
//                 text[8] = '2';
//                 text[9] = char(i - 20) + '0';
//             } else if (i >= 10) {
//                 text[8] = '1';
//                 text[9] = char(i - 10) + '0';
//             } else {
//                 text[8] = char(i) + '0';
//             }
            
//             screen1.write16x16(text);
//             char text2[] = "================\nPower(1/8):  \nContinue: *\nDone: #\0";
//             char numbers[] = "12345678";
//             screen2.write8x8(text2);
//             screen1.flush();
            
//             char tmpPowerValue = '\0';

//             for (;;) {
//                 char matrixInfo = matrix.pressed();
//                 if (matrixInfo != '\0'){
//                     if (matrixInfo == '*' && tmpPowerValue != '\0') {
//                         playerPower[i-1] = tmpPowerValue;
//                         playerIndex++;
//                         break;
//                     } else if (matrixInfo == '#' && tmpPowerValue != '\0') {
//                         playerPower[i-1] = tmpPowerValue;
//                         playerIndex++;
//                         state = gameLeaderStates::SEND_CONFIG;
//                         break;
//                     }
//                     for (unsigned int i = 0; i < 8; i++) {
//                         if (matrixInfo == numbers[i]) {
//                             text2[29] = matrixInfo;
//                             tmpPowerValue = matrixInfo;
//                             screen2.write8x8(text2);
//                             screen1.flush();
//                             break;
//                         }
//                     }
//                 }  
//             }
//             if (state == gameLeaderStates::SEND_CONFIG) {
//                 break;
//             }
            
//         }
//         state = gameLeaderStates::SEND_CONFIG;
//     }
//     break;
        
//     case gameLeaderStates::SEND_CONFIG:
//     {   
//         screen1.clear();
//         char text[] = "Player:\n  \0";
//         char text2[] = "================\nPower:  \nNext Player: *\nFlash: #\0";
//         for(unsigned int i = 1; i <= playerIndex; i++) {
//             if (i >= 30) {
//                 text[8] = '3';
//                 text[9] = char(i - 30) + '0';
//             } else if (i >= 20) {
//                 text[8] = '2';
//                 text[9] = char(i - 20) + '0';
//             } else if (i >= 10) {
//                 text[8] = '1';
//                 text[9] = char(i - 10) + '0';
//             } else {
//                 text[8] = char(i) + '0';
//             }
//             text2[24] = playerPower[i-1];
//             screen1.write16x16(text);
//             screen2.write8x8(text2);
//             screen1.flush();
            
//             bool flashed = false;
//             for (;;) {
//                 char matrixInfo = matrix.pressed();
//                 if (matrixInfo != '\0') {
//                     if (matrixInfo == '*' && flashed) {
//                         break;
//                     } else if (matrixInfo == '#') {
//                         flashed = true;
//                         hwlib::cout << "Flash\n";
//                     }
//                 }
//             }
//         }
//         state = gameLeaderStates::SHOW_BEGIN;
//         playerIndex = 0;
//     }
//     break;
//     }
//     }
// }