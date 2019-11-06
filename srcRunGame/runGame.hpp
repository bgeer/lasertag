#ifndef RUNGAME_HPP
#define RUNGAME_HPP

#include "rtos.hpp"
#include "gameParameters.hpp"
#include "gameTimer.hpp"

#include "../srcSender/irLedController.hpp"
#include "../srcReciever/irReciever.hpp"
#include "oledController.hpp"
#include "../srcBeeper/beeperControl.hpp"


enum class runGameState{waiting, checkMessage, hitOrData, saveData, countDown, hit, gameOver};//shoot

/// @file
/// Class to run the game
/// @details
/// This class is a rtos task, it controls the player. It sends and receives messages and controls an oled and a beeper
class runGame : public rtos::task<>, public msg_listener{
private:
    //boundary objects
    irLedSender & sender;
    gameParameters parameters;
    oledController & oled;
    beeperControl & pieper;
    //trigger pin 5

    //Abstract values
    int nMessages = 0;
    uint16_t message = 0; 
    uint32_t doubleMessage = 0;
    bool playGameOverSound = 0;                                               

    //waitables
    rtos::flag triggerFlag;
    rtos::flag oledUpdateFlag;
    rtos::flag gameOverFlag;
    rtos::channel<uint32_t, 10> messages;
    
    gameTimer gameDuration;

public:

    ///@brief constructor forrunGame
    ///@param sender This is where messages are send to, the sender class controls the IR led.
    ///@param oled This is the screen the oledController writes to.
    ///@param pieper This is the beeper that goes off when you shoot and when the game is over.
    runGame(irLedSender & sender, oledController & oled, beeperControl & pieper): 
    task("Rungame"),
    sender(sender),
    oled(oled),
    pieper(pieper),
    triggerFlag(this, "Trigger Flag"),
    oledUpdateFlag(this, "oledUpdate Flag"),
    gameOverFlag(this, "game over"),
    messages(this, "messages"),
    gameDuration(parameters, oledUpdateFlag, gameOverFlag)
    {}
    
    /// @brief Prints a uint16_t
    /// @details Prints a uint16_t in the command line, it is used to debug.
    void printUint16_t(const uint16_t & message);

    /// @brief Checks the sum of a uint16_t
    /// @details Checks if the first 16 bits are the same as the last 16 bits.
    bool checksumMessage(const uint32_t & message);

    /// @brief Checks the startbit on a uint16_t
    /// @details Checks if bit 0 in a uint16_t is a 1.
    bool checkStartBit(const uint16_t & message);

    /// @brief Checks the xor bits in a uint16_t
    /// @details In a uint16_t, checks if the xor of bit 1 and bit 6 is the same as bit 11
    bool checkXorMessage(const uint16_t & message);

    /// @brief returns bit 1 up to and including bit 5 as a integer value
    int get1to5(const uint16_t & message);

    /// @brief returns bit 6 up to and including bit 10 as a integer value
    int get6to10(const uint16_t & message);

    /// @brief returns bit 1 up to and including bit 3 as a integer value
    int get1to3(const uint16_t & message);

    /// @brief returns bit 4 up to and including bit 10 as a integer value
    int get4to10(const uint16_t & message);

    /// @brief sets the trigger flag
    /// @details This function sets the trigger flag. It is used in a class witch knows runGame.
    /// This way runGame can wait for the flag witch can be set by another class
    void setTriggerFlag();

    /// @brief Compiles the message gat gets send to sender if you shoot.
    /// @details This function makes the message that gets send to the sender channel.
    /// It uses gameParameters to get the correct data.
    uint16_t makeShootMessage();

    /// @brief Writes the shoot message to the sender channel
    /// @details Gets the shoot message from gameParameters and writes it to the sender channel.
    void shoot();

    void msg_received(uint32_t msg) override{
        messages.write(msg);
    }

    /// @brief returns the wapen power
    /// @details gets the wapen power from gameParameters and returns it as a integer
    int getWP(){
        return parameters.getWapenPower();
    }
    
    /// @brief this is the main function in runGame
    /// @details rtos runs this function, it is a endless loop. to keep the function clear it is build up using a switch state
    /// the first state is waiting,
    /// in this state rtos waits for either a new message, the trigger flag, the oled update flag or the game over flag.
    /// if one of these things happends the case will switch to the appropriate case to call the necessary functions.
    void main(){
        runGameState state = runGameState::waiting;
        for(;;){
            switch(state){
                case runGameState::waiting: {

                    auto events = wait(messages + triggerFlag + oledUpdateFlag + gameOverFlag);
                    //hwlib::cout << parameters.getGameTime();
                    if(events == messages){
                        doubleMessage = messages.read();
                        message = doubleMessage >> 16;
                        state = runGameState::checkMessage;
                        break;
                    }
                    if(events == triggerFlag && gameDuration.getStartGame_gameTimer() ){
                        // hwlib::cout << "shoot\n";
                        // state = runGameState::shoot;
                        shoot();
                        printUint16_t( parameters.getShootdata() );
                        pieper.setFlag1();
                        break;
                    }
                    if(events == oledUpdateFlag){
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

                        parameters.setPlayerNr( get1to5(message) ); //get player ID
                        parameters.setGameTime( get6to10(message) * 60); //get game time
                        state = runGameState::waiting;
                        break;
                    }else{
                        hwlib::cout<<"Initialised\n";
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
                        gameDuration.start();
                        break;
                    }
                    //update start time on oled
                    oled.drawGameCountdown( parameters.getStartTime() );
                    oled.flush();

                    parameters.setStartTime( parameters.getStartTime()-1);
                    hwlib::wait_ms(1000);
                    break;
                    
                }
                case runGameState::hit: {
                    int enemyID = get1to5(message); //get enemy ID
                    if(parameters.getPlayerNr() != enemyID ){
                        parameters.newHit( enemyID ); //register enemy hit
                        int tempWp = get6to10(message); //get enemy wp
                        
                        parameters.setHitpoits( parameters.getHitpoints()- (tempWp*3) ); //update hp, current hp - enemy wp
                        //regester hit
                        if(parameters.getHitpoints() < 0){
                            hwlib::cout << "dood\n";
                            state = runGameState::gameOver;
                            break;
                        }

                        oled.drawHpTime(parameters.getHitpoints(), parameters.getGameTime() );
                        oled.flush();
                        }
                        state = runGameState::waiting;
                        
                        break;
                    
                }
                               

                case runGameState::gameOver: {
                    oled.clear();
                    oled.drawGameOver();
                    oled.flush();
                    if(!playGameOverSound){
                        playGameOverSound = 1;
                        pieper.setFlag2();
                    }
                }
            }
        }
    }

    
};

#endif