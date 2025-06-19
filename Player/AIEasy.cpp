#include "AIEasy.h"
#include "../GameBoard/GameBoard.h"
#include "../Display/DisplayManager.h"
#include <cstdlib>

void AIEasy::playCard() {
    GameBoard& board = GameBoard::getInstance();
    Set& deck = getPlayerDeck();

    if (deck.getSize() == 0) return;

    int cardIndex = rand() % deck.getSize();
    Cards* selectedCard = deck.getCardAt(cardIndex);


    int tileIndex = rand() % board.getBoardSize();
    for (int offset = 0; offset < board.getBoardSize(); ++offset) {
        int index = (tileIndex + offset) % board.getBoardSize();
        if (!board.getSharedTiles()[index]->isAlreadyClaimed()) {
            tileIndex = index;
            break;
        }
    }


    board.placeCardOnTileByIndexOfTheTile(tileIndex, *selectedCard, getPlayerID());

    auto& tile = board.getSharedTiles()[tileIndex];
    if (tile->getPlayerCardsOnTilesByPlayerId(getPlayerID()).getSize() == tile->getNbOfPlayableCards()
        && tile->getFirstPlayerToFillTheStoneTile() == nullptr) {
        tile->setFirstPlayerToFillTheStoneTile(this);
        }


    if (board.getRemainingClanCards().getSize() > 0) {
        drawClanCards();
    }
}

void AIEasy::playTurn() {
    DisplayManager::getInstance()->output("Tour de l'IA (joueur " + std::to_string(getPlayerID()) + ")\n");

    GameBoard& board = GameBoard::getInstance();
    int boardSize = board.getBoardSize();


    if (rand() % 100 < 20) {
        for (int i = 0; i < boardSize; ++i) {
            auto& tile = board.getSharedTiles()[i];
            if (!tile->isAlreadyClaimed()) {
                tile->claim(getPlayerID());
                if (tile->isAlreadyClaimed()) {
                    DisplayManager::getInstance()->output("L'IA a revendiqué la tuile " + std::to_string(i) + "\n");
                    return;
                }
            }
        }
    }

    playCard();
}