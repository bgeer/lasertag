#ifndef GAMEPARAMETERS_HPP
#define GAMEPARAMETERS_HPP
/// @file

/// @brief A struct to save the enemy data in.
struct playerHitData{ //enemy data
    uint8_t playerId = 0;
    uint16_t hits = 0;
};

/// @brief Game Parameters entity
/// @detail A class that contains the game parameters.
class gameParameters{
private:
    int playerNr = 0;
    int gameTime = 0;
    int wapenpower = 0;
    int startTime = 0; //over hoelang het spel start in secondes
    int hitpoits = 100;
    playerHitData enemyHits[31] = {};
    uint16_t shootData = 0;

public:
    /// @file entity class gameParameters
    /// @details This class saves all the game parameters used in runGame
    gameParameters(){}

    /// @brief sets player nr as an integer
    void setPlayerNr(int nr){
        playerNr = nr;
    }
    /// @brief returns player nr as an integer
    int getPlayerNr(){
        return playerNr;
    }

    /// @brief sets the game time as an integer
    /// @details the game time is how long the game lasts in seconds
    void setGameTime(int time){
        gameTime = time;
    }
    /// @brief returns the game time as an integer
    /// @details the game time is how long the game lasts in seconds
    int getGameTime(){
        return gameTime;
    }

    /// @brief sets the wapenpower as an integer
    /// @details the wapen power is used to calculate how much damage you do
    void setWapenPower(int wp){
        wapenpower = wp;
    }
    /// @brief returns the wapen power as an integer
    /// @details the wapen power is used to calculate how much damage you do
    int getWapenPower(){
        return wapenpower;
    }

    /// @brief sets the start time in seconds
    /// @details the start time is in how long the game will start after you got the game parameters
    void setStartTime(int time){
        startTime = time;
    }
    /// @brief returns the start time as an integer
    /// @details the start time is in how long the game will start after you got the game parameters
    int getStartTime(){
        return startTime;
    }

    /// @brief sets the hitpoints as an integer
    void setHitpoits(int newHp){
        hitpoits = newHp;
    }
    /// @brief returns the hit points as an integer
    int getHitpoints(){
        return hitpoits;
    }

    /// @brief register a new hit
    void newHit(uint8_t enemyNr){
        enemyHits[enemyNr].playerId = enemyNr;
        enemyHits[enemyNr].hits++;
    }

    /// @brief returns the number of times 1 enemy ha hit you as an integer
    int gethit(uint8_t enemyNr){
        return enemyHits[enemyNr].hits;
    }

    /// @brief sets the shoot data as an uint16_t
    void setShootData(uint16_t newData){
        shootData = newData;
    }
    /// @brief gets the shoot data as an uint16_t
    uint16_t getShootdata(){
        return shootData;
    }
};

#endif