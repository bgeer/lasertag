#include "terminal.hpp"

void terminal::write() {
    //clear the display buffer
    display.clear();

    // Write text to buffer
    for (int i = 0; i < index; i++) {
        auto w = hwlib::part(
            display, hwlib::xy( 0, (i*8) ), hwlib::xy( 128, (i*8)+8 )
        );
        auto f = hwlib::font_default_8x8();
        auto d = hwlib::terminal_from( w, f );
        d << data[i];
    }

    // Write buffer to display
    display.flush();
}

bool terminal::replace( const hwlib::string<16> s, int index_change ) {
    // Change if index is lower than index then
    // return true
    if (index_change < index) {
        data[index] = s;
        return true;
    }
    // If not able to change return false
    return false;
}

void terminal::add( const hwlib::string<16> s) {
    // Higher index if smaller than 8 (max commands showable)
    if (index < 8) {
        index++;
    }

    // Move array so that oldest data if index > 8 will disappear
    for (int i = index-1; i > 0; --i) {
        data[i] = data[i-1];
    }

    // Set newest command at beginning 
    data[0] = s;
    write();
}

void terminal::clear() {
    // Set index to 0
    index = 0;

    // Clear and flush the screen
    display.clear();
    display.flush();
}