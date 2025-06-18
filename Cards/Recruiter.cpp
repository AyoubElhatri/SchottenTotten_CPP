#include "Recruiter.h"
#include <iostream>

#include "../GameBoard/GameBoard.h"
#include "../Logic2/GameLogic2.h"
#include "../Cards/TacticalCards.h"
#include "../Cards/ClanCards.h"
#include "../Display/DisplayManager.h"

void Recruiter::getEvent(StoneTiles* /* unused */) {
    GameBoard* board = &GameBoard::getInstance();
    Player* currentPlayer = CGameLogic::getInstance().getCurrentPlayer();
    Set& deck = currentPlayer->getPlayerDeck();

    // Retirer la carte Recruiter du deck et la mettre dans la défausse
    for (unsigned int i = 0; i < deck.getSize(); ++i) {
        if (deck.getCardAt(i)->getName() == "Recruiter") {
            deck.moveCard(i, board->getDiscardedCards());
            break;
        }
    }

    DisplayManager::getInstance()->output("Vous allez piocher 3 cartes (clan ou tactique).\n");

    // Phase 1 : piocher 3 cartes
    int cardsToDraw = 3;
    for (int i = 0; i < cardsToDraw; ) {
        DisplayManager::getInstance()->output("Piochez une carte (" + std::to_string(cardsToDraw - i) + " restantes)\n1. Tactique   2. Clan");
        std::string input = DisplayManager::getInstance()->takeInput();

        if (input == "1") {
            if (board->getRemainingTacticalCards().getSize() > 0) {
                board->getRemainingTacticalCards().moveCard(0, deck);
                ++i;
            } else {
                DisplayManager::getInstance()->output("Plus de cartes tactiques disponibles.\n");
            }
        } else if (input == "2") {
            if (board->getRemainingClanCards().getSize() > 0) {
                board->getRemainingClanCards().moveCard(0, deck);
                ++i;
            } else {
                DisplayManager::getInstance()->output("Plus de cartes de clan disponibles.\n");
            }
        } else {
            DisplayManager::getInstance()->output("Choix invalide, veuillez entrer 1 ou 2.\n");
        }
    }

    // Phase 2 : Choisir et replacer 2 cartes
    DisplayManager::getInstance()->output("\nVoici votre main après la pioche :");
    deck.printSet();

    int toReturn = 2;
    while (toReturn > 0) {
        DisplayManager::getInstance()->output("Choisissez une carte à remettre sous la pioche (" + std::to_string(toReturn) + " restantes)");
        DisplayManager::getInstance()->output("Index de carte (0 à " + std::to_string(deck.getSize() - 1) + ") :\n>> ");

        std::string input = DisplayManager::getInstance()->takeInput();
        unsigned int index;

        try {
            index = std::stoi(input);
        } catch (...) {
            DisplayManager::getInstance()->output("Entrée invalide, veuillez entrer un nombre.\n");
            continue;
        }

        if (index >= deck.getSize()) {
            DisplayManager::getInstance()->output("Index hors limites, veuillez réessayer.\n");
            continue;
        }

        Cards* card = deck.getCardAt(index);
        std::unique_ptr<Cards> removedCard = deck.getCardbyIndex(index);

        if (dynamic_cast<TacticalCards*>(card)) {
            board->getRemainingTacticalCards().addCard(std::move(removedCard));
        } else {
            board->getRemainingClanCards().addCard(std::move(removedCard));
        }

        --toReturn;

        // Afficher la main mise à jour après chaque retrait
        DisplayManager::getInstance()->output("\nMain actuelle :");
        deck.printSet();
    }

    DisplayManager::getInstance()->output("Deux cartes ont été remises sous la pioche.\n");
}