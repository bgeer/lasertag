#ifndef BIT_HELPER_HPP
#define BIT_HELPER_HPP

#include "hwlib.hpp"


//van rechts naar links (little Endian)
bool getbit(uint8_t index, const uint16_t & byte){
    return (byte & (1 << (index - 1)));
}

//set bit to a bool
void setbit(uint8_t index, uint16_t & byte, bool set){
   
    byte ^= (-set ^ byte) & (1UL << index);
    
}
//prints in big endian
void printBit(const uint16_t & byte){
    for(int i = 16; i > 0; i--){
        hwlib::cout << getbit(i, byte) ;
    }
    hwlib::cout << '\n';
}

//Encode to ir protocol
uint16_t encode(uint16_t message){
    for(int i = 1; i < 6; i++){
        setbit(9 + i, message, (getbit(i, message) ^ getbit(i+5, message)));
    }
    return message;
}

//Check if bit came as a whole
bool check(const uint16_t & message){
    for(int i = 1; i < 6; i++){
        if (!(getbit(10+i, message) == bool(getbit(i, message) ^ getbit(i+5, message)))){
            return 0;
        }
    }
    return 1;
}


#endif