#ifndef MSG_LOGGER_HPP
#define MSG_LOGGER_HPP

#include "irInterface.hpp"



class msg_logger : public rtos::task<>, public msg_listener {
  private:
    rtos::channel<ir_msg, 10> messages;

  public:
    msg_logger()
        : task("msg_logger"), messages(this, "messages") {}

    void main() override {
        for (;;) {
            auto msg = messages.read();
            hwlib::cout  << "\ncommand: " << msg.command << "\n\n";
            hwlib::wait_ms(0);
        }
    }

    void msg_received(ir_msg msg) override {
        messages.write(msg);
    }
};
#endif