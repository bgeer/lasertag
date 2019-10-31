#include "runGame.hpp"
#include "hwlib.hpp"
int main(){
    hwlib::wait_ms(1000);
    runGame player101;
    player101.main();
    //hwlib::cout<<player101.checkMessage()<<hwlib::endl;
}