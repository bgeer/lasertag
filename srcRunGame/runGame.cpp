#include "runGame.hpp"
#include "hwlib.hpp"
//hit message
//-     -       -       -       -       -        -       -       -       -       -        -       -       -       -       -
//0     1       2       3       4       5        6       7       8       9       10       11      12      13      14      15
//start (       player id               )    |   (       wapen power             )    |   xor 1,6 xor 2,7 xor 3,8 xor 4,9 xor 5,10


//van rechts naar links (little Endian)
bool getbit(uint8_t index, const uint16_t & byte){
    return (byte & (1 << (index)));
}

//set bit to a bool
void setbit(uint8_t index, uint16_t & byte, bool set){
   
    byte ^= (-set ^ byte) & (1UL << index);
    
}
//prints in big endian
void printBit(const uint16_t & byte){
    for(int i = 15; i >= 0; i--){
        hwlib::cout << getbit(i, byte) ;
    }
    hwlib::cout << '\n';
}

//Encode to ir protocol
uint16_t encode(uint16_t message) {
    for (int i = 4; i >= 0; i--) {
        setbit(i, message, (getbit(i + 10, message) ^ getbit(i + 5, message)));
    }
    return message;
}


//Check if bit came as a whole
bool check(const uint16_t & message){
    for(int i = 4; i >= 0; i--){
        if (getbit(i, message) != bool(getbit(i+10, message) ^ getbit(i+5, message))){
            return 0;
        }
    }
    return 1;
}



void runGame::printUint16_t(const __uint16_t & message){
    hwlib::cout<<"Byte: ";
    for(int i = 15; i >= 0; i--){
        hwlib::cout<<((message & (1<<i)) !=0);
    }
    hwlib::cout<<'\n';
    
}

//van rechts naar links (little Endian)


bool runGame::checksumMessage(const uint32_t & message){
    for(int i = 0; i < 15; i++){
        if( !(getbit(i, uint16_t(message)) == getbit(i, uint16_t(message >> 16)))){
            return false;
        }
    }
    return true;
}

bool runGame::checkStartBit(const uint16_t & message){
    uint16_t temp = (message & (1<<15));
    return getbit(15, temp);
}

//check the xor checksum
bool runGame::checkXorMessage(const uint16_t & message){
    for(int i = 4; i >= 0; i--){
        if (getbit(i, message) != bool(getbit(i+10, message) ^ getbit(i+5, message))){
            hwlib::cout<<i<<"\n";
            hwlib::cout<<getbit(i, message)<<" "<<getbit(i+10, message)<<" "<<getbit(i+5, message)<<"\n";
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
    //runGame::printUint16_t(countdown);
    countdown = countdown >> 5;
    //runGame::printUint16_t(countdown);
    return countdown;
}

void runGame::setTriggerFlag(){
    triggerFlag.set();
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

void runGame::shoot(){
    if( gameDuration.getStartGame_gameTimer() ){
        sender.writeChannel( parameters.getShootdata() );
    }
}