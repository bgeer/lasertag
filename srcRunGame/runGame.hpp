#ifndef RUNGAME_HPP
#define RUNGAME_HPP

#include "rtos.hpp"
#include "gameParameters.hpp"
#include "irLedController.hpp"

enum class runGameState{waiting, checkMessage, hitOrData, saveData, hit, shoot};

class runGame : public rtos::task<>{

private:

    runGameState state = runGameState::waiting;
    int nMesseges = 0;
    gameParameters parameters;


    uint32_t dubblemessage = 0b10100000010010101010000001001010; //playerID en gameTime     tijdelijk test bericht
    uint16_t message = dubblemessage;                                                     //tijdelijk test bericht

    irLedSender & sender;


    rtos::flag trigger;

public:
    runGame(irLedSender& sender): 
    sender(sender)
    {}
    
    void printUint16_t(const uint16_t & message);
    bool checksumMessage(const uint32_t & message);
    bool checkStartrBit(const uint16_t & message);
    bool checkXorMessage(const uint16_t & message);
    bool getbit(int index, const uint32_t & byte);

    int get1to5(const uint16_t & message);
    int get6to10(const uint16_t & message);
    int get1to3(const uint16_t & message);
    int get4to10(const uint16_t & message);
    void setTriggerFlag();
    void makeShootMessage();


    void main(){
        // uint16_t test = 0b1100010000010001;
        // hwlib::cout<<getCountdown(test)<<hwlib::endl;
        for(;;){
            switch(state){
                case runGameState::waiting:{
                    if(msgDecoder.messages){
                        uint32_t message = msgDecoder.messages.read();
                        state = runGameState::checkMessage;
                        break;
                    }
                    if(trigger){
                        state = runGameState::shoot;
                        break;
                    }
                }
                case runGameState::checkMessage:{
                    if( !(checksumMessage(dubblemessage)) ){
                        state = runGameState::waiting;
                        hwlib::cout<<"checksum\n";
                        break;
                    }
                    if( !(checkStartrBit(message)) ){
                        state = runGameState::waiting;
                        hwlib::cout<<"startBit\n";
                        break;
                    }
                    if( !(checkXorMessage(message)) ){
                        state = runGameState::waiting;
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
                        parameters.setStartTime( get4to10(message) ); //get start time
                        //hwlib::cout<<get4to10(message)<<hwlib::endl;

                        parameters.setShootData( makeShootMessage() ); //make and save the shoot message

                        state = runGameState::waiting;
                        break;
                    }
                }
                case runGameState::hit:{
                    parameters.newHit( get1to5(message) ); //get enemy ID
                    int tempWp = get6to10(message); //get enemy wp
                    parameters.setHitpoits( parameters.getHitpoints()-tempWp ); //update hp, current hp - enemy wp
                    //update hp op scherm
                    state = runGameState::waiting;
                    break;
                }
                case runGameState::shoot:{
                    uintchannel.write( parameters.getShootdata() );
                    state = runGameState::waiting;
                    break;
                }
            }
        }
    }
};

#endif