#include "oledController.hpp"


void oledController::flush(){
    oled.flush();
}

void oledController::clear(){
    oled.clear();
}

void oledController::drawPlayerNumber(int value){
    playerPart
        << "\f"
        << "----------------\n"
        << "Player ID = " << value << "\n"
        << "----------------";
}

void oledController::drawHpTime(int hp, int remainTimeSec){
    int sec = remainTimeSec % 60;
    int min = remainTimeSec / 60;
    scoreTimePart
        << "\f" << "\n"
        << "HP = " << hp << "\n"
        << "Time: " << min << ":" << sec << "\n"
        << "\n----------------\n";
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

void oledController::drawStartMessage(){
    fullScreen
        << "\f"
		<< "========\n"
		<< "waiting\n"
        << "for\n"
		<< "stats\n";
}