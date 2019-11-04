#ifndef GAME_TIME_ENTITY_HPP
#define GAME_TIME_ENTITY_HPP

class gameTimeEntity {
private:

    int gametime;

public:

    gameTimeEntity(): 
        gametime(0)
    {}

    void set(int value) {
        gametime = value;
    }

    int get() {
        return gametime;
    }
};

#endif /*gameTimeEntity*/