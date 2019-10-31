#ifndef MSG_LOGGER_HPP
#define MSG_LOGGER_HPP

#include "irInterface.hpp"



class run_game : public rtos::task<>, public msg_listener {
  private:
    rtos::channel<uint32_t, 10> messages;

  public:
    msg_logger()
        : task("msg_logger"), messages(this, "messages") {}

    void main() override {
        for (;;) {
            auto msg = messages.read();
            hwlib::cout  << "\ncommand: " << msg << "\n\n";
            hwlib::wait_ms(0);
        }
    }

    void msg_received(uint32_t msg) override {
        messages.write(msg);
    }
};
#endif