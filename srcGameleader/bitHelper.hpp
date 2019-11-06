#ifndef BIT_HELPER_HPP
#define BIT_HELPER_HPP

#include "hwlib.hpp"
// \@file


/// \brief
/// Gets bit from givin index in givin uint16_t
/// \details
/// Gets bit from givin index in givin uint16_t in little endian.
bool getbit(uint8_t index, const uint16_t & byte){
    return (byte & (1 << (index)));
}

/// \brief
/// Sets bit in givin index in givin uint16_t to givin bool
/// \details
/// Sets bit in givin index in givin uint16_t to givin bool in little Endian.
void setbit(uint8_t index, uint16_t & byte, bool set){
   
    byte ^= (-set ^ byte) & (1UL << index);
    
}

/// \brief
/// Prints givin uint16_t
/// \details
/// Prints givin uint16_t in Big endian
void printBit(const uint16_t & byte){
    for(int i = 16; i > 0; i--){
        hwlib::cout << getbit(i, byte) ;
    }
    hwlib::cout << '\n';
}

/// \brief
/// Encodes bit for use in IR protocol.
/// \details
/// Encodes bit for use in IR protocol.
uint16_t encode(uint16_t message) {
    for (int i = 4; i >= 0; i--) {
        setbit(i, message, (getbit(i + 10, message) ^ getbit(i + 5, message)));
    }
    return message;
}

/// \brief
/// Decodes bit for use in IR protocol and returns true if byte is received without losingdata.
/// \details
/// Decodes bit for use in IR protocol and returns true if byte is received without losingdata.
bool check(const uint16_t & message){
    for(int i = 4; i >= 0; i--){
        if (getbit(i, message) != bool(getbit(i+10, message) ^ getbit(i+5, message))){
            return 0;
        }
    }
    return 1;
}


#endif
