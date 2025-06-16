#include "Recruiter.h"
#include <iostream>

#include "../GameBoard.h"


void Recruiter::getEvent() {
    int cardsToDraw = 3;
    int draw = 0;

    GameBoard* board = &GameBoard::getInstance();
    while (cardsToDraw != 0) {
        const Set& supraset1 = board->getRemainingTacticalCards();
        DisplayManager::getInstance()->output("RemainingTacticalCards : \n");
        supraset1.printSet();
        const Set& supraset2 = board->getRemainingClanCards();
        DisplayManager::getInstance()->output("RemainingClanCards : \n");
        supraset2.printSet();
        if (supraset1.getSize() != 0) {
            if (
            string message = "How many Tactical cards do you want ? (Number between 0 -")";
            DisplayManager::getInstance()->output(message);

        }




    }



}


