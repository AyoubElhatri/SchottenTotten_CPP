#include "Recruiter.h"
#include <iostream>

#include "../GameBoard/GameBoard.h"
#include "../Logic/GameLogic.h"


void Recruiter::getEvent(StoneTiles* stoneTiles) {
    int cardsToDraw = 3;
    GameBoard* board = &GameBoard::getInstance();
    Player* currentPlayer = CGameLogic::getInstance().getCurrentPlayer();

    //Piocher 3 cartes
    while (cardsToDraw > 0) {
        const Set& remainingTacticalCard = board->getRemainingTacticalCards();
        const Set& remainingClanCard = board->getRemainingClanCards();

        DisplayManager::getInstance()->output("Draw a card (" + std::to_string(cardsToDraw) + " remaining)");
        DisplayManager::getInstance()->output("What type of card do you want to draw? (1 for Tactics, 2 for Clan)");
        unsigned int type = stoi(DisplayManager::getInstance()->takeInput());

        if (type == 1) {
            if (remainingTacticalCard.getSize() != 0) {
                currentPlayer->drawTacticalCards(1);
                cardsToDraw--;
            } else {
                DisplayManager::getInstance()->output("No tactical cards available.");
            }
        } else if (type == 2) {
            if (remainingClanCard.getSize() != 0) {
                currentPlayer->drawClanCards(1);
                cardsToDraw--;
            } else {
                DisplayManager::getInstance()->output("No clan cards available .");
            }
        }
    }

    // Choisir et replacer 2 cartes
    int cardsToReturn = 2;


while (cardsToReturn > 0) {
    DisplayManager::getInstance()->output("\nYour current hand :");
    currentPlayer->getPlayerDeck().printSet();

    DisplayManager::getInstance()->output("Choose a card to put back under the draw pile (" +
        std::to_string(cardsToReturn) + " remaining)");
    DisplayManager::getInstance()->output("Choose the card index (0-" +
        std::to_string(currentPlayer->getPlayerDeck().getSize() - 1) + ") :");

    unsigned int cardIndex = stoi(DisplayManager::getInstance()->takeInput());
    DisplayManager::getInstance()->output("Acessing the card at index : " + std::to_string(cardIndex));

    unsigned int deckSize = currentPlayer->getPlayerDeck().getSize();

    if (cardIndex < deckSize) {

        bool isTactical = false;
        {
            const Cards* tempCard = currentPlayer->getPlayerDeck().getCardAt(cardIndex);
            if (!tempCard) {
                DisplayManager::getInstance()->output("Invalid card !");
                return;
            }
            isTactical = dynamic_cast<const TacticalCards*>(tempCard) != nullptr;
        }


        if (isTactical) {
            currentPlayer->getPlayerDeck().moveCard(cardIndex, GameBoard::getInstance().getRemainingTacticalCards());
        } else {
            currentPlayer->getPlayerDeck().moveCard(cardIndex, GameBoard::getInstance().getRemainingClanCards());
        }


        cardsToReturn--;
    } else {
        DisplayManager::getInstance()->output("Invalid index, please enter the a valid index. ");
    }
}
}
