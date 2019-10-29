#ifndef TERMINAL_HPP
#define TERMINAL_HPP

#include "hwlib.hpp"


class terminal {
private:

    hwlib::window &display;

    int index;
    hwlib::string<16> data[8];

public:

    terminal(hwlib::window &display):
        display(display),
        index(0)
    {}

    bool replace( const hwlib::string<16> s, int index_change );
    void write();
    void add( const hwlib::string<16> s );
    void clear();

};

#endif /* TERMINAL_HPP */
