#ifndef TRIGGER_HPP
#define TRIGGER_HPP

#include "rtos.hpp"
#include "../srcRunGame/runGame.hpp"

class trigger : public rtos::task<>{
private:
    runGame &game;
    hwlib::target::pin_in button = hwlib::target::pins::d5;

public:
    trigger(runGame &game):
    task("Trigger Input")
    game(game)
    {}


    void main(){
        for(;;){
            hwlib::wait_ms(10);
            button.refresh();
            if(button.read()){
                game.setTriggerFlag();
            }
        }
    }
   

};

#endif //TRIGGER_HPP