#ifndef MSG_DECODER_HPP
#define MSG_DECODER_HPP

#include "irInterface.hpp"


enum class msg_decoder_state {
    idle,
    reading
};


class msg_decoder : public rtos::task<>, public pause_listener {
  private:
    msg_listener& listener;
    msg_decoder_state state = msg_decoder_state::idle;
    rtos::channel<int, 200> pauses;

  public:
    msg_decoder(msg_listener& listener)
        : task("msg_decoder"), listener(listener), pauses(this, "pauses") {}

    void main() override {
        int pause, num_bits, data = 0;
        for (;;) {
            pause = pauses.read();
            switch (state) {
                case msg_decoder_state::idle:
                    if (pause > 3'500 && pause < 5'000) {
                        // When pause after start signal
                        num_bits = data = 0;
                        state = msg_decoder_state::reading;
                    }
                    break;
                case msg_decoder_state::reading:
                    if (num_bits == 32) {
                        state = msg_decoder_state::idle;
                        listener.msg_received(data);
                        hwlib::cout << "message ontvangt";
                        

                    } else {
                        
                        data <<= 1;
                        data |= pause > 1'000 ? 0 : 1;
                        num_bits++;
                    }
                    break;
            }
        }
    }

    void pause_detected(int length) override {
        pauses.write(length);
    }


};

#endif