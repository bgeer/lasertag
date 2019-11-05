#ifndef MSG_LISTENER_HPP
#define MSG_LISTENER_HPP


class msg_listener {
  public:
    virtual void msg_received(uint32_t msg) = 0;
};

#endif