#ifndef IR_LED_CONTROLLER
#define IR_LED_CONTROLLER

#define HIGH 1
#define LOW 0

#include "irLed.hpp"
#include <rtos.hpp>
/// @file


/// \brief
/// decodes message to ir Protocol and sends it out.
/// \details
/// This class is used for sending IR messages to an IR led using the IR pause protocol.
class irLedSender : public rtos::task<>{

private:

    irLed &output;
    rtos::channel<uint16_t, 10> uintChannel;
    

public:

    irLedSender(irLed &output):
        task("irLedSender"),
        output(output),
        uintChannel(this, "uintChannel")
    {}


private:
    /// \brief
    /// Sends zero using IR protocol
    /// \details
    /// Sends a zero using the IR pause Protocol via an IR led.
    void sendZero(){
        output.write(HIGH);
        hwlib::wait_us_busy(800);
        output.write(LOW);
        hwlib::wait_us_busy(1600);
    }  
    
    /// \brief
    /// Sends one using IR protocol
    /// \details
    /// Sends an one using the IR pause Protocol via an IR led.
    void sendOne(){
        output.write(HIGH);
        hwlib::wait_us_busy(1600);
        output.write(LOW);
        hwlib::wait_us_busy(800);
    }

    /// \brief
    /// This fucntion makes a closing message.
    /// \details
    /// This fucntion sends an closing message so that 
    /// the message knows that the message has ended and it should
    /// decode a different message.
    void endMessage(){
        hwlib::wait_ms(1);
        output.write(HIGH);
        hwlib::wait_us_busy(100);
        output.write(LOW);
        hwlib::wait_ms(1);
        output.write(HIGH);
        hwlib::wait_us_busy(100);
        output.write(LOW);
    }

    /// \brief
    /// Parses a messages to the sendzero and sendone functions.
    /// \details
    /// Bit shifts an UINT16_t and calls the sendzero or one function depending on the value of the bit.
    void write(const uint16_t & message){
        sendOne();
        hwlib::wait_us_busy(3500);
        for(uint8_t i = 0; i < 2; i++){
         
            for(int i = 15; i > -1; i--){
                if (1 & (message >> i)) {
                    sendOne();
                } else {
                    sendZero();
                }
            } 
        }
        endMessage();

    }

public:

    /// \brief
    /// writes a message to the channel
    /// \details
    /// Writes an uint16_t to the channel, these messages are going to be parsed to the
    void writeChannel(const uint16_t & message){
        uintChannel.write(message);
    }


    void main() override {
        for(;;){
            auto message = uintChannel.read();
            write(message); 
        }
    }

};


#endif










