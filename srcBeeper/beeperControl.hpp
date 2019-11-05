#ifndef BEEPERCONTROL_HPP
#define BEEPERCONTROL_HPP
/// \@file

#include "hwlib.hpp"


/// \brief
/// Plays a frequency or does a pitch slide
/// \details
/// Beeper can be controlled by calling fucntions to play a frequency 
/// or pitch slide. Beeper takes 1 phwlib::pin_out in its constructor
class beeperControl{
private:
    hwlib::pin_out & beeper;
public:
    beeperControl(hwlib::pin_out & beeper):
    beeper(beeper)
    {}
    /// \brief
    /// Beeper plays givin frequency
    void playFreq(int freq, int times);
    /// \brief
    /// Beeper plays givin start frequency and slides to the end frequency
    void portamento(int start, int end, int speed);
    /// \brief
    /// Plays programmed sound
    void playSound1();
    /// \brief
    /// Plays programmed sound
    void playSound2(int wp);
};

#endif