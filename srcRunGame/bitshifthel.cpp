#include "runGame.hpp"
#include "hwlib.hpp"

//hit message
//-     -       -       -       -       -        -       -       -       -       -        -       -       -       -       -
//0     1       2       3       4       5        6       7       8       9       10       11      12      13      14      15
//start (       player id               )    |   (       wapen power             )    |   xor 1,6 xor 2,7 xor 3,8 xor 4,9 xor 5,10

void printUint16_t(uint16_t message){
    hwlib::cout<<"Byte: ";
    for(int i = 15; i >= 0; i--){
        hwlib::cout<<((message & (1<<i)) !=0);
    }
    hwlib::cout<<'\n';
}

bool contains1(uint16_t message){
    for(int i = 15; i >= 0; i--){
        if((((message & (1<<i)) !=0))){
            return 1;
        }
    }
    return 0;
}

bool runGame::checkMessage(){
    //uint16_t message = msgDecoder.messages.read();
    uint16_t message = 0b0101110011110000;     //0x5CF0     0b0101110011110000
                       //0123456789012345
                    
    for(unsigned int i = 1; i < 6; i++){
        
        uint16_t lhs = (message & (1 << (15 - i) ) );
        //printUint16_t(lhs);
        uint16_t rhs = (message & (1 << (10 - i) ) );
        //printUint16_t(rhs);
        bool xortemp = contains1(lhs) ^ contains1(rhs);
        //printUint16_t(xortemp);

        bool controlbit = contains1(message & (1 << (5 - i) ) );

        bool test = xortemp & controlbit;

        if(test == 0){
            return 0;
        }
        //hwlib<<cout
    }
    return 1;
}

