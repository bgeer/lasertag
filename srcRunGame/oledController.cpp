#include "oledController.hpp"


void oledController::flush(){
    oled.flush();
}

void oledController::clear(){
    oled.clear();
}

void oledController::drawPlayerNumber(int value){
    playerPart
        << "----------------\n"
        << "Player ID = " << value << "\n"
        << "----------------";
}

void oledController::drawHpTime(int hp, int remainTimeSec){
    int sec = remainTimeSec % 60;
    int min = remainTimeSec / 60;
    scoreTimePart
        << "HP = " << hp << "\n"
        << "Time: " << min << ":" << sec << "\n"
        << "----------------\n";
}

void oledController::drawGameOver(){
    fullScreen
        << "\f"
		<< "========\n"
		<< "GameOver\n"
		<< "========\n";
}

void oledController::drawGameCountdown(int sec){
    fullScreen
        << "\f"
		<< "========\n"
		<< sec << " sec\n"
		<< "========\n";
}