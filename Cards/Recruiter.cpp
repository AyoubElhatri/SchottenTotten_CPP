#include "Recruiter.h"
#include <iostream>

#include "../GameBoard/GameBoard.h"
#include "../Logic/GameLogic.h"


void Recruiter::getEvent(StoneTiles* stoneTiles) {
    int cardsToDraw = 3;
    GameBoard* board = &GameBoard::getInstance();
    Player* currentPlayer = CGameLogic::getInstance().getCurrentPlayer();

    // Phase 1 : Piocher 3 cartes
    while (cardsToDraw > 0) {
        const Set& remainingTacticalCard = board->getRemainingTacticalCards();
        const Set& remainingClanCard = board->getRemainingClanCards();

        DisplayManager::getInstance()->output("Piochez une carte (" + std::to_string(cardsToDraw) + " restantes)");
        DisplayManager::getInstance()->output("Quel type de carte voulez-vous piocher ? (1 pour Tactique, 2 pour Clan)");
        unsigned int type = stoi(DisplayManager::getInstance()->takeInput());

        if (type == 1) {
            if (remainingTacticalCard.getSize() != 0) {
                currentPlayer->drawTacticalCards(1);
                cardsToDraw--;
            } else {
                DisplayManager::getInstance()->output("Plus de cartes tactiques disponibles.");
            }
        } else if (type == 2) {
            if (remainingClanCard.getSize() != 0) {
                currentPlayer->drawClanCards(1);
                cardsToDraw--;
            } else {
                DisplayManager::getInstance()->output("Plus de cartes de clan disponibles.");
            }
        }
    }

    // Phase 2 : Choisir et replacer 2 cartes
    int cardsToReturn = 2;
    DisplayManager::getInstance()->output("\nVotre main actuelle :");
    currentPlayer->getPlayerDeck().printSet();


while (cardsToReturn > 0) {
    DisplayManager::getInstance()->output("\nVotre main actuelle :");
    currentPlayer->getPlayerDeck().printSet();

    DisplayManager::getInstance()->output("Choisissez une carte à remettre sous la pioche (" +
        std::to_string(cardsToReturn) + " restantes)");
    DisplayManager::getInstance()->output("Entrez l'index de la carte (0-" +
        std::to_string(currentPlayer->getPlayerDeck().getSize() - 1) + ") :");

    unsigned int cardIndex = stoi(DisplayManager::getInstance()->takeInput());
    DisplayManager::getInstance()->output("Accès à la carte à l'index : " + std::to_string(cardIndex));

    unsigned int deckSize = currentPlayer->getPlayerDeck().getSize();

    if (cardIndex < deckSize) {
        // Faire une copie intelligente du pointeur de type AVANT déplacement
        bool isTactical = false;
        {
            const Cards* tempCard = currentPlayer->getPlayerDeck().getCardAt(cardIndex);
            if (!tempCard) {
                DisplayManager::getInstance()->output("Carte invalide !");
                return;
            }
            isTactical = dynamic_cast<const TacticalCards*>(tempCard) != nullptr;
        }

        // Puis déplacer la carte (maintenant que le type est connu)
        if (isTactical) {
            currentPlayer->getPlayerDeck().moveCard(cardIndex, GameBoard::getInstance().getRemainingTacticalCards());
        } else {
            currentPlayer->getPlayerDeck().moveCard(cardIndex, GameBoard::getInstance().getRemainingClanCards());
        }


        cardsToReturn--;
    } else {
        DisplayManager::getInstance()->output("Index invalide, veuillez réessayer.");
    }
}
}
