#include "Recruiter.h"
#include <iostream>

#include "../GameBoard.h"


void Recruiter::getEvent() {
    int cardsToDraw = 3;

    GameBoard* board = &GameBoard::getInstance();
    while (cardsToDraw != 0) {
        const Set& remainingTacticalCard = board->getRemainingTacticalCards();

        const Set& remainingClanCard = board->getRemainingClanCards();

        DisplayManager::getInstance()->output("Which type of card do you want to draw? (1 for Tactical, 2 for Clan)");
        unsigned int type = stoi(DisplayManager::getInstance()->takeInput());
        if (type==1) {
            if ( remainingTacticalCard.getSize()!=0) {
                //
                cardsToDraw--;
            }else {
        DisplayManager::getInstance()->output("No more tactical cards available to draw.");
            }

        }else if (type==2) {
            if ( remainingClanCard.getSize()!=0) {
                //
                cardsToDraw--;
            }
            else {
                DisplayManager::getInstance()->output("No more clan cards available to draw.");
            }
        }






    }



}


