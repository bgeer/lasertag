#ifndef BEEPERCONTROL_HPP
#define BEEPERCONTROL_HPP
/// @file

#include "rtos.hpp"


/// \brief
/// Plays a frequency or does a pitch slide
/// \details
/// Beeper can be controlled by calling fucntions to play a frequency 
/// or pitch slide. Beeper takes 1 phwlib::pin_out in its constructor
class beeperControl : public rtos::task<> {
private:
    hwlib::pin_out & beeper;

    rtos::flag sound1Flag;
    rtos::flag sound2Flag;

public:
    beeperControl(hwlib::pin_out & beeper):
    beeper(beeper),
    sound1Flag(this, "sound 1 flag"),
    sound2Flag(this, "sound 2 flag")
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
    void playSound2();

    void setFlag1(){
        sound1Flag.set();
    }
    void setFlag2(){
        sound2Flag.set();
    }

    void main(){
        for(;;){
            auto events = wait(sound1Flag + sound2Flag);
            if(events == sound1Flag){
                hwlib::cout<<"s1\n";
                playSound1();
            }
            if(events == sound2Flag){
                hwlib::cout<<"s2\n";
                playSound2();
            }
        }
    }
};

#endif
