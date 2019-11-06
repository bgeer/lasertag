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
    drawStartMessage();
    oled.flush();
    }
    /// \brief
    /// Flushes display buffer
    /// \details
    /// This function is used for flushing the display buffer of a HWLIB window
    void flush();
    /// \brief 
    /// clear display buffer
    /// \details
    /// This function is used to clear the buffer of a HWLIB window.
    void clear();

    /// \brief
    /// Draws player number to the display buffer.
    void drawPlayerNumber(int value);

    /// \brief
    /// Draws player hp and remaining time to display buffer.
    void drawHpTime(int hp, int remainTimeSec);

    /// \brief
    /// Draws Gameover screen to the display buffer
    void drawGameOver();

    /// \brief
    /// Draws countdown to display buffer
    void drawGameCountdown(int sec);

    /// \brief
    /// Draws the start message to the display buffer
    void drawStartMessage();
};

#endif //OLEDCONTROLLER_HPP
