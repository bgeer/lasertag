#ifndef RUNGAME_HPP
#define RUNGAME_HPP

#include "rtos.hpp"
#include "gameParameters.hpp"
#include "gameTimer.hpp"

#include "../srcSender/irLedController.hpp"
#include "../srcReciever/irReciever.hpp"
#include "oledController.hpp"


enum class runGameState{waiting, checkMessage, hitOrData, saveData, countDown, hit, gameOver};//shoot

/// @file
/// Class to run the game
/// @details
/// This class controls the player.
class runGame : public rtos::task<>, public msg_listener{
private:
    //boundary objects
    irLedSender & sender;
    gameParameters parameters;
    oledController & oled;
    //buzzer
    //trigger pin 5

    //Abstract values
    int nMessages = 0;
    uint16_t message = 0; 
    uint32_t doubleMessage = 0;                                                 

    //waitables
    rtos::flag triggerFlag;
    rtos::flag oledUpdateFlag;
    rtos::flag gameOverFlag;
    rtos::channel<uint32_t, 10> messages;
    
    gameTimer gameDuration;

public:

    runGame(irLedSender & sender, oledController & oled): 
    task("Rungame"),
    sender(sender),
    oled(oled),
    triggerFlag(this, "Trigger Flag"),
    oledUpdateFlag(this, "oledUpdate Flag"),
    gameOverFlag(this, "game over"),
    messages(this, "messages"),
    gameDuration(parameters, oledUpdateFlag, gameOverFlag)
    {}
    
    void printUint16_t(const uint16_t & message);
    bool checksumMessage(const uint32_t & message);
    bool checkStartBit(const uint16_t & message);
    bool checkXorMessage(const uint16_t & message);

    int get1to5(const uint16_t & message);
    int get6to10(const uint16_t & message);
    int get1to3(const uint16_t & message);
    int get4to10(const uint16_t & message);

    void setTriggerFlag();
    uint16_t makeShootMessage();

    void shoot();

    void msg_received(uint32_t msg) override{
        messages.write(msg);
    }

    int getWP(){
        return parameters.getWapenPower();
    }
    
    void main(){
        runGameState state = runGameState::waiting;
        for(;;){
            switch(state){
                case runGameState::waiting: {

                    auto events = wait(messages + triggerFlag + oledUpdateFlag + gameOverFlag);
                    //hwlib::cout << parameters.getGameTime();
                    if(events == messages){
                        hwlib::cout << "message\n";
                        doubleMessage = messages.read();
                        message = doubleMessage >> 16;
                        state = runGameState::checkMessage;
                        break;
                    }
                    if(events == triggerFlag){
                        // hwlib::cout << "shoot\n";
                        // state = runGameState::shoot;
                        shoot();
                        break;
                    }
                    if(events == oledUpdateFlag){
                        oled.clear();
                        oled.drawHpTime(parameters.getHitpoints(), parameters.getGameTime() );
                        oled.drawPlayerNumber(parameters.getPlayerNr() );
                        oled.flush();
                        break;
                    }
                    if(events == gameOverFlag){
                        state = runGameState::gameOver;
                        break;
                    }
                    break;
                }

                case runGameState::checkMessage: {
                    hwlib::cout << doubleMessage << '\n';
                    printUint16_t(message);
                    if( !(checksumMessage(doubleMessage))){
                        hwlib::cout<<"checksum\n";
                        state = runGameState::waiting;
                        break;
                    }
                    if( !(checkXorMessage(message)) ){
                        hwlib::cout<<"xor\n";
                        state = runGameState::waiting;
                        break;
                    }
                    else if( !(checkStartBit(message)) ){
                        hwlib::cout<<"startbit\n";
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
                    //hwlib::cout<<"saveData\n";
                    if(nMessages == 1){
                        hwlib::cout<<"m1\n";
                        parameters.setPlayerNr( get1to5(message) ); //get player ID
                        parameters.setGameTime( get6to10(message) * 60); //get game time
                        state = runGameState::waiting;
                        break;
                    }else{
                        hwlib::cout<<"m2\n";
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
                        // oled.clear();
                        // oled.drawHpTime( parameters.getHitpoints(), parameters.getGameTime() );//mischien
                        // oled.flush();
                        gameDuration.start();
                        break;
                    }
                    //update start time on oled
                    oled.clear();
                    oled.drawGameCountdown( parameters.getStartTime() );
                    oled.flush();

                    parameters.setStartTime( parameters.getStartTime()-1);
                    hwlib::wait_ms(1000);
                    break;
                    
                }
                case runGameState::hit: {
                    parameters.newHit( get1to5(message) ); //get enemy ID
                    int tempWp = get6to10(message); //get enemy wp
                    parameters.setHitpoits( parameters.getHitpoints()-tempWp ); //update hp, current hp - enemy wp
                    //regester hit
                    if(parameters.getHitpoints() < 0){
                        state = runGameState::gameOver;
                        break;
                    }

                    oled.clear();
                    oled.drawHpTime(parameters.getHitpoints(), parameters.getGameTime() );
                    oled.flush();
                    state = runGameState::waiting;
                    break;
                }
                
                // case runGameState::shoot: {
                //     if( gameDuration.getStartGame_gameTimer() ){
                //         sender.writeChannel( parameters.getShootdata() );
                //     }
                //     state = runGameState::waiting;
                //     break;
                // }
                

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