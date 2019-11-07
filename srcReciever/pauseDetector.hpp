#ifndef PAUSE_DETECTOR_HPP
#define PAUSE_DETECTOR_HPP
/// @file

#include "irInterface.hpp"

enum class pause_detector_state {
    // Waiting for signal (when input is high)
    idle,
    // Receiving signal (when input low)
    signal,
};

/// \brief
/// This class detects pauses from an ir led.
/// \details
/// This class detects pause lengths and calls a function from message decoder that puts them inside a channel
class pause_detector : public rtos::task<> {
  private:
    hwlib::target::pin_in signal;
    pause_listener& listener;
    rtos::clock clock;
    pause_detector_state state = pause_detector_state::idle;

  public:
    pause_detector(pause_listener& listener, hwlib::target::pin_in pin)
        : task("pause_detector"), signal(pin), listener(listener), clock(this, 100, "clock") {}

    void main() override {
        int n = 0;
        for (;;) {
            wait(clock);
            switch (state) {
                case pause_detector_state::idle:
                    if (signal.read() == LOW) {
                        // When receiving an IR signal
                        listener.pause_detected(n);
                        state = pause_detector_state::signal;
                    } else {
                        // When NOT receiving an IR signal
                        n += 100;
                    }
                    break;
                case pause_detector_state::signal:
                    if (signal.read() == HIGH) {
                        // When NOT receiving an IR signal
                        n = 0;
                        state = pause_detector_state::idle;
                    }
                    break;
            }
        }
    }
};


#endif
