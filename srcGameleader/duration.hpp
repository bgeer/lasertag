#ifndef DURATION_HPP
#define DURATION_HPP

#include "rtos.hpp"
#include "gameTimeEntity.hpp"

class duration : public rtos::task<> {

private: 

    bool startTimer = false;
    rtos::clock oneSecondClock;
    gameTimeEntity &time;

public:

    duration(gameTimeEntity &time): 
        task("timer"), 
        oneSecondClock(this, 1'000'000, "OneSecondClock"),
        time(time)
    {}


    void main(){ 
        for(;;){
            wait(oneSecondClock);
            if(time.get() > 0 && startTimer) {
                time.set(time.get() - 1 );
                //hwlib::cout << time.get() << hwlib::endl;
            }
        }

    }

    void start(){
        startTimer = true;
    }

    void stop(){
        startTimer = false;
    }
};


#endif