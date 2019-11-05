#ifndef GAMEPARAMETERS_HPP
#define GAMEPARAMETERS_HPP

struct playerHitData{ //enemy data
    uint8_t playerId = 0;
    uint16_t hits = 0;
};

class gameParameters{
private:
    int playerNr = 0;
    int gameTime = 0; //hoe lang het spel duurt in secondes
    int wapenpower = 0;
    int startTime = 0; //over hoelang het spel start in secondes
    int hitpoits = 100;
    playerHitData enemyHits[31] = {};
    uint16_t shootData = 0;

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

    void setHitpoits(int newHp){ //updateHp(int wapenpower)     waar willen we shit berekenen?
        hitpoits = newHp;
    }

    int getHitpoints(){
        return hitpoits;
    }

    void newHit(uint8_t enemyNr){
        enemyHits[enemyNr].playerId = enemyNr;
        enemyHits[enemyNr].hits++;
    }

    int gethit(uint8_t enemyNr){
        return enemyHits[enemyNr].hits;
    }

    void setShootData(uint16_t newData){
        shootData = newData;
    }

    uint16_t getShootdata(){
        return shootData;
    }
};

#endif