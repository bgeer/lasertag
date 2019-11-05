#ifndef OLEDCONTROLLER_HPP
#define OLEDCONTROLLER_HPP

#include "hwlib.hpp"

class oledController{
private:
    hwlib::window & oled;
    hwlib::terminal_from & playerPart;
    hwlib::terminal_from & scoreTimePart;
    hwlib::terminal_from & fullScreen;

public:
    oledController(
    hwlib::window & oled, 
    hwlib::terminal_from & playerPart,
    hwlib::terminal_from & scoreTimePart,
    hwlib::terminal_from & fullScreen):
    oled(oled),
    playerPart(playerPart),
    scoreTimePart(scoreTimePart),
    fullScreen(fullScreen)
    {
    oled.clear();
    oled.flush();
    }

    void flush();

    void clear();

    void drawPlayerNumber(int value);

    void drawHpTime(int hp, int remainTimeSec);

    void drawGameOver();

    void drawGameCountdown(int sec);
};

#endif //OLEDCONTROLLER_HPP