#ifndef PAUSE_LISTENER_HPP
#define PAUSE_LISTENER_HPP

class pause_listener {
  public:
    virtual void pause_detected(int length) = 0;
};

#endif