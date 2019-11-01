#ifndef RUNGAME_HPP
#define RUNGAME_HPP

#include "hwlib.hpp"
#include "gameParameters.hpp"

enum class runGameState{
    waitForMessage, hitOrData, saveData, hit
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

    int get1to5(const uint16_t & message);
    int get6to10(const uint16_t & message);
    int get1to3(const uint16_t & message);
    int get4to10(const uint16_t & message);


    void main(){
        uint16_t test = 0b1100010000010001;
        hwlib::cout<<get4to10(test)<<hwlib::endl;
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
                case runGameState::hitOrData:{
                    hwlib::cout<<"hitOrData";
                    if(nMesseges < 2){
                        state = runGameState::saveData;
                        nMesseges++;
                        break;
                    }else{
                        //state = runGameState::hit;
                        break;
                    }
                }
                case runGameState::saveData:{
                    hwlib::cout<<"saveData\n";
                    if(nMesseges == 1){
                        parameters.setPlayerNr( get1to5(message) ); //get player ID
                        //hwlib::cout<<parameters.getPlayerNr()<<hwlib::endl;
                        parameters.setGameTime( get6to10(message) ); //get game time
                        //hwlib::cout<<parameters.getGameTime()<<hwlib::endl;
                        break;
                    }else{
                        parameters.setWapenPower( get1to3(message) ); //get Wapen Power
                        //hwlib::cout<<get1to3(message)<<hwlib::endl;
                        parameters.setWapenPower( get4to10(message) );
                        //hwlib::cout<<get4to10(message)<<hwlib::endl;
                        state = runGameState::waitForMessage;
                        break;
                    }
                }
                case runGameState::hit:{
                    parameters.newHit( get1to5(message) ); //get enemy ID
                    int tempWp = get6to10(message); //get enemy wp
                    parameters.setHitpoits(parameters.getHitpoints()-tempWp); //update hp, current hp - enemy wp
                    //update hp op scherm
                    state = runGameState::waitForMessage;
                    break;
                }
            }
        //}
    }
};

#endif