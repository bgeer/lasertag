#include "runGame.hpp"
#include "hwlib.hpp"
//hit message
//-     -       -       -       -       -        -       -       -       -       -        -       -       -       -       -
//0     1       2       3       4       5        6       7       8       9       10       11      12      13      14      15
//start (       player id               )    |   (       wapen power             )    |   xor 1,6 xor 2,7 xor 3,8 xor 4,9 xor 5,10

void runGame::printUint16_t(const __uint16_t & message){
    hwlib::cout<<"Byte: ";
    for(int i = 15; i >= 0; i--){
        hwlib::cout<<((message & (1<<i)) !=0);
    }
    hwlib::cout<<'\n';
}

//van rechts naar links (little Endian)
bool runGame::getbit(int index, const uint32_t & byte){
    return (byte & (1 << (index - 1)));
}

bool runGame::checksumMessage(const uint32_t & message){
    for(int i = 0; i < 16; i++){
        if( !(runGame::getbit(i, message) == runGame::getbit(i+16, message)) ){
            return false;
        }
    }
    return true;
}

//check the xor checksum
bool runGame::checkXorMessage(const uint16_t & message){
    for(int i = 1; i < 6; i++){
        if (!(getbit(10+i, message) == bool(getbit(i, message) ^ getbit(i+5, message)))){
            return false;
        }
    }
    return true;
}

int runGame::get1to5(const uint16_t & message){
    int playerId = message & 31744; //111110000000000
    playerId = playerId >> 10;
    return playerId;
}

int runGame::get6to10(const uint16_t & message){
    int gameTime = message & 992; //1111100000
    gameTime = gameTime >> 5;
    return gameTime;
}

int runGame::get1to3(const uint16_t & message){
    int wapenPower = message & 28672; //111000000000000
    wapenPower = wapenPower >> 11;
    return wapenPower;
}

int runGame::get4to10(const uint16_t & message){
    int countdown = message & 4064; //111111100000
    runGame::printUint16_t(countdown);
    countdown = countdown >> 4;
    runGame::printUint16_t(countdown);
    return countdown;
}