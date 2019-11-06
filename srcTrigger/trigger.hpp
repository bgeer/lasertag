#ifndef TRIGGER_HPP
#define TRIGGER_HPP

#include "rtos.hpp"
#include "../srcRunGame/runGame.hpp"
/// @file

/// \brief
/// This task listens to an pin input 
/// \details
/// This task is used for listening for the input for the trigger button.
/// If the input is high, a flag gets setted.
class trigger : public rtos::task<>{
private:
    runGame &game;
    hwlib::target::pin_in button = hwlib::target::pins::d5;

public:
    trigger(runGame &game):
    task("Trigger Input"),
    game(game)
    {}


    void main(){
        for(;;){
            hwlib::wait_ms(10);
            button.refresh();
            //hwlib::cout<<"triggertask\n";
            if(button.read()){
                hwlib::cout<<"trigger\n";
                game.setTriggerFlag();
                hwlib::wait_ms( game.getWP()*1000 ); //shoot delay, should be wapen power
            }
        }
    }
   

};

#endif //TRIGGER_HPP
