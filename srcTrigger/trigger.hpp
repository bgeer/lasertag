#ifndef TRIGGER_HPP
#define TRIGGER_HPP

#include "hwlib.hpp"
#include "runGame.hpp"

class trigger{
private:
    runGame &game;
    hwlib::pin_in &button;

public:
    trigger(runGame &game, hwlib::pin_in &button):
    game(game), button(button)
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