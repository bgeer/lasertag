#include <iostream>


void write(uint16_t message){
        for(int i = 15; i > -1; i--){
            std::cout << (1 & (message >> i));
        }        
}


int main(){
    


    uint16_t message = 1;
    write(message);






}