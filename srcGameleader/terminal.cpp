#include "terminal.hpp"

void terminal::clear() {
    display.clear();
}

void terminal::flush() {
    display.flush();
}

void terminal::write8x8( const hwlib::string<50> text ) {
    auto w = hwlib::part(
        display, start, end
    );
    auto f = hwlib::font_default_8x8();
    auto d = hwlib::terminal_from( w, f );
    //d << "\f" << text;
    for (unsigned int i = 0; i < text.length(); i++) {
          d << text[i];
    }
}

void terminal::write16x16( const hwlib::string<30> text ) {
    auto w = hwlib::part(
        display, start, end
    );
    auto f = hwlib::font_default_16x16();
    auto d = hwlib::terminal_from( w, f );
    d << "\f";
    for (unsigned int i = 0; i < text.length(); i++) {
        d << text[i];
    }
}
