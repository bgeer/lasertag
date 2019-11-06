#ifndef GAME_TIME_ENTITY_HPP
#define GAME_TIME_ENTITY_HPP



/// \@file

/// \brief
/// Value of the countdown in GameLeader
/// \details
/// This is the value of the gametime countdown in GameLeader that gets parsed
/// to the players and it gets subtracted by a seperate rtos task called duration.
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
