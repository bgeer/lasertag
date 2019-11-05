#ifndef RUNGAME_HPP
#define RUNGAME_HPP

#include "rtos.hpp"
#include "gameParameters.hpp"
#include "gameTimer.hpp"

#include "../srcSender/irLedController.hpp"
#include "../srcReciever/irReciever.hpp"
#include "oledController.hpp"


enum class runGameState{waiting, checkMessage, hitOrData, saveData, countDown, hit, shoot, gameOver};

class runGame : public rtos::task<>, public msg_listener{

private:
    //states
    
    
    //boundary objects
    irLedSender & sender;
    gameParameters parameters;
    oledController & oled;

    //oled
    //buzzer

    //Abstract values
    int nMessages = 0;
    uint32_t doubleMessage = 0; 
    uint16_t message = doubleMessage;                                                  

    //waitables
    rtos::flag triggerFlag;
    rtos::flag oledUpdateFlag;
    rtos::channel<uint32_t, 10> messages;
    
    gameTimer gameDuration;

public:

    runGame(irLedSender & sender, oledController & oled): 
    task("Rungame"),
    sender(sender),
    oled(oled),
    triggerFlag(this, "Trigger Flag"),
    oledUpdateFlag(this, "oledUpdate falg"),
    messages(this, "messages"),
    gameDuration(parameters, oledUpdateFlag)
    {}
    
    void printUint16_t(const uint32_t & message);
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
        runGameState state = runGameState::waiting;
        //===============================================================================================================
        for(;;){
            switch(state){
                case runGameState::waiting: {

                    auto events = wait(messages + triggerFlag + oledUpdateFlag);
                    //hwlib::cout << parameters.getGameTime();
                    if(events == messages){
                        hwlib::cout << "message\n";
                        doubleMessage = messages.read();
                        state = runGameState::checkMessage;
                        break;
                    }
                    if(events == triggerFlag){
                        state = runGameState::shoot;
                        break;
                    }
                    if(events == oledUpdateFlag){
                        oled.clear();
                        oled.drawGameCountdown( parameters.getGameTime() );
                        oled.flush();
                        break;
                    }
                    break;
                }

                case runGameState::checkMessage: {
                    message = doubleMessage >> 16;
                    if( !(checkXorMessage(message)) ){
                        state = runGameState::waiting;
                        break;
                    }
                    else if( !(checkStartrBit(message)) ){
                        state = runGameState::waiting;
                        break;
                    }
                    hwlib::cout << "+\n";
                    state = runGameState::hitOrData;
                    break;
                }
                
                case runGameState::hitOrData: {
                    if(nMessages < 2){
                        state = runGameState::saveData;
                        nMessages++;
                        break;
                    }else{
                        state = runGameState::hit;
                        break;
                    }
                }
                
                case runGameState::saveData: {
                    hwlib::cout<<"saveData\n";
                    if(nMessages == 1){
                        parameters.setPlayerNr( get1to5(message) ); //get player ID
                        parameters.setGameTime( get6to10(message) * 60); //get game time
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
                
                case runGameState::countDown: {
                    if(parameters.getStartTime() == 0){
                        state = runGameState::waiting;
                        //update oled
                        gameDuration.start();
                        break;
                    }
                    parameters.setStartTime( parameters.getStartTime()-1);
                    //update start time on oled
                    oled.clear();
                    oled.drawGameCountdown( parameters.getStartTime() );
                    oled.flush();
                    hwlib::wait_ms(1000);
                    break;
                    
                }
                case runGameState::hit: {
                    parameters.newHit( get1to5(message) ); //get enemy ID
                    int tempWp = get6to10(message); //get enemy wp
                    parameters.setHitpoits( parameters.getHitpoints()-tempWp ); //update hp, current hp - enemy wp
                    //update hp on oled
                    oled.clear();
                    oled.drawHpTime(parameters.getHitpoints(), parameters.getGameTime() );
                    oled.flush();
                    state = runGameState::waiting;
                    break;
                }
                
                case runGameState::shoot: {
                    sender.writeChannel( parameters.getShootdata() );
                    state = runGameState::waiting;
                    break;
                }
                

                case runGameState::gameOver: {
                    oled.clear();
                    oled.drawGameOver();
                    oled.flush();
                }
            }
        }
    }

    
};

#endif