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

bool runGame::checkStartrBit(const uint16_t & message){
    uint16_t temp = (message & (1<<15));
    return getbit(16, temp);
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

void runGame::setTriggerFlag(){
    trigger.set();
}

uint16_t runGame::makeShootMessage(){
    uint16_t data = 0x00;

    for (int i = 5 - 1; i >= 0; i--) {
        bool bit = (parameters.getPlayerNr() & (1 << i));
        data |= bit << (15 - (5 - i));
    }
    for (int i = 10 - 5 - 1; i >= 0; i--) {
        bool bit = (parameters.getWapenPower() & (1 << i));
        data |= bit << (15 - (10 - i));
    }
    
    return encode(data);
}