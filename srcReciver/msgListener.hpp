#ifndef MSG_LISTENER_HPP
#define MSG_LISTENER_HPP

#include "irMessage.hpp"

class msg_listener {
  public:
    virtual void msg_received(ir_msg msg) = 0;
};

#endif