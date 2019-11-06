#ifndef TERMINAL_HPP
#define TERMINAL_HPP

#include "hwlib.hpp"


/// \@file

/// \brief
/// Terminal used to write text to a hwlib window
/// \details
/// Terminal used to write text to a hwlib window in 2 different character sizes
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

    /// \brief 
    /// clear display buffer
    /// \details
    /// This function is used to clear the buffer of a HWLIB window.
    void clear();
    /// \brief
    /// Flushes display buffer
    /// \details
    /// This function is used for flushing the display buffer of a HWLIB window
    void flush();
    /// \brief 
    /// Writes 8x8 characters in to the display buffer
    /// \details
    /// Adds newline and writes 8x8 of the hwlib window display buffer
    void write8x8( const char text[] );
    /// \brief 
    /// Writes 16x16 characters in to the display buffer
    /// \details
    /// Adds newline and writes 16x16 of the hwlib window display buffer
    void write16x16( const char text[] );    
};

#endif /* TERMINAL_HPP */
