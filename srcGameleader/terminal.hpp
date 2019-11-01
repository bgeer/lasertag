#ifndef TERMINAL_HPP
#define TERMINAL_HPP

#include "hwlib.hpp"

class terminal {
private:

    hwlib::window &display;
    hwlib::xy &start;
    hwlib::xy &end;

public:

    terminal(
        hwlib::window &display,
        hwlib::xy &start,
        hwlib::xy &end    
    ):
        display(display),
        start(start),
        end(end)
    {   
        display.clear();
        display.flush();
    }

    void clear();
    void flush();
    void write8x8( const char text[] );
    void write16x16( const char text[] );    
};

#endif /* TERMINAL_HPP */
