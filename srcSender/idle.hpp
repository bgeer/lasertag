#include <rtos.hpp>


class idle : public rtos::task<> {

private:

    int time;
    rtos::clock klock;
    

public: 

    idle():
    task("idle"),
    klock(this, 1000, "clock"){}


    void main() override{



        
        for(;;){
            wait(klock);
            time++;
        }

    }

};