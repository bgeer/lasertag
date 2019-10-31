#ifndef GAMEPARAMETERS_HPP
#define GAMEPARAMETERS_HPP

struct playerHitData{ //enemy data
    uint8_t playerId = 0;
    uint16_t hits = 0;
};

class gameParameters{
private:
    int playerNr = 0;
    int gameTime = 0; //hoe lang het spel duurt in minuten
    int wapenpower = 0;
    int startTime = 0; //over hoelang het spel start in secondes
    playerHitData enemyHits[31] = {};

public:
    gameParameters(){}

    void setPlayerNr(int nr){
        playerNr = nr;
    }
    int getPlayerNr(){
        return playerNr;
    }

    void setGameTime(int time){
        gameTime = time;
    }
    int getGameTime(){
        return gameTime;
    }

    void setWapenPower(int wp){
        wapenpower = wp;
    }
    int getWapenPower(){
        return wapenpower;
    }

    void setStartTime(int time){
        startTime = time;
    }

    int getStartTime(){
        return startTime;
    }

    void newHit(uint8_t enemyNr){
        enemyHits[enemyNr].playerId = enemyNr;
        enemyHits[enemyNr].hits++;
    }

    int gethit(uint8_t enemyNr){
        return enemyHits[enemyNr].hits;
    }
};

#endif