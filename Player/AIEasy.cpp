#include "AIEasy.h"
#include "../GameBoard/GameBoard.h"
#include "../Cards/EliteTroopsCards.h"
#include "../Cards/CombatModeCards.h"
#include "../Cards/RusesCards.h"
#include "../Logic/GameLogic.h"
#include "../Display/DisplayManager.h"
#include <random>

void AIEasy::playCard() {
    GameBoard& board = GameBoard::getInstance();
    Set& deck = getPlayerDeck();

    if (deck.getSize() == 0) return;

    int cardIndex = rand() % deck.getSize();
    Cards* selectedCard = deck.getCardAt(cardIndex);

    int tileIndex = -1;

    if (auto eliteTroop = dynamic_cast<EliteTroopsCards*>(selectedCard)) {
        do {
            tileIndex = rand() % board.getBoardSize();
        } while (board.getSharedTiles()[tileIndex]->isAlreadyClaimed());

        board.placeCardOnTileByIndexOfTheTile(tileIndex, *selectedCard, getPlayerID());
    }
    else if (auto combatMode = dynamic_cast<CombatModeCards*>(selectedCard)) {
        do {
            tileIndex = rand() % board.getBoardSize();
        } while (board.getSharedTiles()[tileIndex]->isAlreadyClaimed());

        combatMode->getEvent(board.getSharedTiles()[tileIndex].get());
        deck.moveCard(cardIndex, board.getSharedTiles()[tileIndex]->getCombatModeCards());
    }
    else if (auto ruse = dynamic_cast<RusesCards*>(selectedCard)) {
        ruse->getEvent(nullptr);
        deck.moveCard(cardIndex, board.getDiscardedCards());
    }
    else {
        do {
            tileIndex = rand() % board.getBoardSize();
        } while (board.getSharedTiles()[tileIndex]->isAlreadyClaimed());

        board.placeCardOnTileByIndexOfTheTile(tileIndex, *selectedCard, getPlayerID());
    }

    if (tileIndex != -1) {
        auto& tile = board.getSharedTiles()[tileIndex];
        if (tile->getPlayerCardsOnTilesByPlayerId(getPlayerID()).getSize() == tile->getNbOfPlayableCards()
            && tile->getFirstPlayerToFillTheStoneTile() == nullptr) {
            tile->setFirstPlayerToFillTheStoneTile(this);
        }
    }

    // Piocher une carte aléatoire (si disponible)
    bool canDrawClan = board.getRemainingClanCards().getSize() > 0;
    bool canDrawTactical = board.getRemainingTacticalCards().getSize() > 0;

    if (canDrawClan && canDrawTactical) {
        if (rand() % 2 == 0) drawClanCards();
        else drawTacticalCards();
    } else if (canDrawClan) {
        drawClanCards();
    } else if (canDrawTactical) {
        drawTacticalCards();
    }
}

void AIEasy::playTurn() {
    DisplayManager::getInstance()->output(" Tour de l'IA (joueur " + std::to_string(getPlayerID()) + ")\n");

    GameBoard& board = GameBoard::getInstance();
    int boardSize = board.getBoardSize();

    // 20% de chance d'essayer de revendiquer une tuile
    if (rand() % 100 < 20) {
        for (int i = 0; i < boardSize; ++i) {
            auto& tile = board.getSharedTiles()[i];
            if (!tile->isAlreadyClaimed()) {
                unsigned int id = getPlayerID();
                tile->claim(id);
                if (tile->isAlreadyClaimed()) {
                    DisplayManager::getInstance()->output("L'IA a revendiqué la tuile " + std::to_string(i) + "\n");
                    return;
                }
            }
        }
    }

    playCard();
}