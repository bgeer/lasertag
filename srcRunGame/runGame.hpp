#ifndef RUNGAME_HPP
#define RUNGAME_HPP

#include "rtos.hpp"
#include "gameParameters.hpp"

#include "../srcSender/irLedController.hpp"
#include "../srcReciever/irReciever.hpp"

enum class runGameState{waiting, checkMessage, hitOrData, saveData, countDown, hit, shoot};

class runGame : public rtos::task<>, public msg_listener{

private:

    runGameState state = runGameState::waiting;
    int nMesseges = 0;
    gameParameters parameters;
    rtos::channel<uint32_t, 10> messages;

    uint32_t dubbleMessage = 0b10100000010010101010000001001010; //playerID en gameTime     tijdelijk test bericht
    uint16_t message = dubbleMessage;                                                     //tijdelijk test bericht

    irLedSender & sender;


    rtos::flag triggerFlag;

public:
    runGame(irLedSender& sender): 
    task("Rungame"),
    messages(this, "messages" ),
    sender(sender),
    triggerFlag(this, "vlag")
    {}
    
    void printUint16_t(const uint16_t & message);
    bool checksumMessage(const uint32_t & message);
    bool checkStartrBit(const uint16_t & message);
    bool checkXorMessage(const uint16_t & message);

    int get1to5(const uint16_t & message);
    int get6to10(const uint16_t & message);
    int get1to3(const uint16_t & message);
    int get4to10(const uint16_t & message);
    void setTriggerFlag();
    uint16_t makeShootMessage();
    void msg_received(uint32_t msg) override {messages.write(msg);}
    void main(){
        // uint16_t test = 0b1100010000010001;
        // hwlib::cout<<getCountdown(test)<<hwlib::endl;
        for(;;){
            switch(state){
                case runGameState::waiting:{

                    auto events = wait(messages + triggerFlag);
            
                    if(events == messages){
                        dubbleMessage = messages.read();
                        state = runGameState::checkMessage;
                        break;
                    }
                    if(events == triggerFlag){
                        state = runGameState::shoot;
                        break;
                    }
                }
                case runGameState::checkMessage:{
                    if( !(checksumMessage(dubbleMessage)) ){
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
                    //hwlib::cout<<"hitOrData";
                    if(nMesseges < 2){
                        state = runGameState::saveData;
                        nMesseges++;
                        break;
                    }else{
                        state = runGameState::hit;
                        break;
                    }
                }
                case runGameState::saveData:{
                    hwlib::cout<<"saveData\n";
                    if(nMesseges == 1){
                        parameters.setPlayerNr( get1to5(message) ); //get player ID
                        parameters.setGameTime( get6to10(message) ); //get game time
                        state = runGameState::waiting;
                        break;
                    }else{
                        parameters.setWapenPower( get1to3(message) ); //get Wapen Power
                        parameters.setStartTime( get4to10(message) ); //get start time

                        parameters.setShootData( makeShootMessage() ); //make and save the shoot message

                        state = runGameState::countDown;
                        break;
                    }
                }
                case runGameState::countDown:{
                    if(parameters.getStartTime() == 0){
                        state = runGameState::waiting;
                        break;
                    }
                    parameters.setStartTime( parameters.getStartTime()-1);
                    //update start time on oled
                    hwlib::wait_ms(1000);
                    break;
                }
                case runGameState::hit:{
                    parameters.newHit( get1to5(message) ); //get enemy ID
                    int tempWp = get6to10(message); //get enemy wp
                    parameters.setHitpoits( parameters.getHitpoints()-tempWp ); //update hp, current hp - enemy wp
                    //update hp on oled
                    state = runGameState::waiting;
                    break;
                }




                case runGameState::shoot:{
                    sender.writeChannel( parameters.getShootdata() );
                    state = runGameState::waiting;
                    break;
                }
            }
        }
    }

    
};

#endif