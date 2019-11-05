#ifndef BIT_HELPER_HPP
#define BIT_HELPER_HPP

#include "hwlib.hpp"


//van rechts naar links (little Endian)
bool getbit(uint8_t index, const uint16_t & byte){
    return (byte & (1 << (index)));
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
// uint16_t encode(uint16_t message){
//     for(int i = 14; i >= 9; i--){
//         setbit(6 - i, message, (getbit(15 - i, message) ^ getbit(10 - i, message)));
//     }
//     return message;
// }

uint16_t encode(uint16_t message) {
    for (int i = 4; i >= 0; i--) {
        setbit(i, message, (getbit(i + 10, message) ^ getbit(i + 5, message)));
    }
    return message;
}

//Check if bit came as a whole
bool check(const uint16_t & message){
    for(int i = 4; i >= 0; i--){
        if (getbit(i, message) != bool(getbit(i+10, message) ^ getbit(i+5, message))){
            return 0;
        }
    }
    return 1;
}


#endif