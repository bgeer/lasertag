#ifndef OLEDCONTROLLER_HPP
#define OLEDCONTROLLER_HPP

#include "hwlib.hpp"

/// @file


/// @brief Class for the OLED display
/// @details
/// This class draws certains screens on the display for the player of the game.
class oledController{
private:
    hwlib::window & oled;
    hwlib::terminal_from & playerPart;
    hwlib::terminal_from & scoreTimePart;
    hwlib::terminal_from & fullScreen;

public:
    /// @brief Constucter for the oledController
    /// @param oled this is the display where the screens are displayed on.
    /// @param playerPart This is the part where the player number is located.
    /// @param scoreTimePart This is the part where the Hp and the time is located.
    /// @param fullScreen On this part are the game over and countdown screen shown.
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

    /// @brief Flush the display.
    /// @details This function writes the buffer to the display over the i2c bus.
    void flush();

    /// @brief Clear the display
    /// @details This function  clears the buffer of the display.
    void clear();

    /// @brief Draw the player number.
    /// @details This function draws the player number on the oled dispay over the i2c bus.
    /// @param value This is the player number.
    void drawPlayerNumber(int value);

    /// @brief Draw Hp and Time.
    /// @details This function draws the player Hp and the remaining time over the i2c bus.
    /// @param hp This is the remaining hp of the player.
    /// @param remainTimeSec This is the remaining game time in seconds.
    void drawHpTime(int hp, int remainTimeSec);

    /// @brief Draw game over.
    /// @details 
    /// This functions draw the game over screen to the display over the i2c bus.
    /// This screen is drawn when the hp is 0 or the remaining game time is 0.
    void drawGameOver();

    /// @brief Draw game countdown.
    /// @details This function draws the countdown when the game is not started yet.
    /// @param sec The remaining time in seconds untill the game starts.
    void drawGameCountdown(int sec);
};

#endif //OLEDCONTROLLER_HPP