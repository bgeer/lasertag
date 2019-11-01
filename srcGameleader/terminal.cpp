#include "terminal.hpp"

void terminal::clear() {
    display.clear();
}

void terminal::flush() {
    display.flush();
}

void terminal::write8x8( const char text[] ) {
    auto w = hwlib::part(
        display, start, end
    );
    auto f = hwlib::font_default_8x8();
    auto d = hwlib::terminal_from( w, f );

    d << "\f";
    for (int i = 0; true; i++) {
        if (text[i] == '\0') {
            break;
        }
        d << text[i];
    }
}

void terminal::write16x16( const char text[] ) {
    auto w = hwlib::part(
        display, start, end
    );
    auto f = hwlib::font_default_16x16();
    auto d = hwlib::terminal_from( w, f );
    
    d << "\f";
    for (int i = 0; true; i++) {
        if (text[i] == '\0') {
            break;
        }
        d << text[i];
    }
}
