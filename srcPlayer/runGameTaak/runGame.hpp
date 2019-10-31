#ifndef RUNGAME_HPP
#define RUNGAME_HPP

#include "hwlib.hpp"
#include "gameParameters.hpp"

enum class runGameState{
    waitForMessage, hitOrData, saveData
};

class runGame{
private:
runGameState state = runGameState::waitForMessage;
int nMesseges = 0;
gameParameters parameters;


uint32_t dubblemessage = 0b10100000010010101010000001001010; //playerID en gameTime
uint16_t message = dubblemessage;

public:
    runGame(){
        hwlib::wait_ms(1000);
    }
    
    void printUint16_t(const uint16_t & message);
    bool checksumMessage(const uint32_t & message);
    bool checkXorMessage(const uint16_t & message);
    bool getbit(int index, const uint32_t & byte);

    int getPlayerId(const uint16_t & message);
    int getGameTime(const uint16_t & message);
    int getWapenPower(const uint16_t & message);
    int getCountdown(const uint16_t & message);


    void main(){
        uint16_t test = 0b1100010000010001;
        hwlib::cout<<getCountdown(test)<<hwlib::endl;
        //for(;;){
            switch(state){
            
                case runGameState::waitForMessage:{
                    //hwlib::cout<<"waitForMessage\n";
                    //uint32_t message = msgDecoder.messages.read();
                    //uint32_t dubblemessage = 0b01011100111100000101110011110000; //tijdelijk, channel is er nog niet
                    
                    
                    if( !(checksumMessage(dubblemessage)) ){
                        state = runGameState::waitForMessage;
                        hwlib::cout<<"checksum\n";
                        break;
                    }
                    if( !(checkXorMessage(message)) ){
                        state = runGameState::waitForMessage;
                        hwlib::cout<<"xor\n";
                        break;
                    }
                    state = runGameState::hitOrData;
                    break;
                }
                case runGameState::hitOrData:
                    hwlib::cout<<"hitOrData";
                    if(nMesseges < 2){
                        state = runGameState::saveData;
                        nMesseges++;
                        break;
                    }else{
                        //state = runGameState::hit;
                        break;
                    }
                case runGameState::saveData:
                    hwlib::cout<<"saveData\n";
                    if(nMesseges == 1){
                        parameters.setPlayerNr( getPlayerId(message) );
                        //hwlib::cout<<parameters.getPlayerNr()<<hwlib::endl;
                        parameters.setGameTime( getGameTime(message) );
                        //hwlib::cout<<parameters.getGameTime()<<hwlib::endl;
                        state = runGameState::waitForMessage;
                        dubblemessage = 0b11000100000100011100010000010001;
                        break;
                    }else{
                        parameters.setWapenPower( getWapenPower(message) );
                        //hwlib::cout<<getWapenPower(message)<<hwlib::endl;
                        parameters.setWapenPower( getCountdown(message) );
                        //hwlib::cout<<getCountdown(message)<<hwlib::endl;
                    }
            }
        //}
    }
};

#endif