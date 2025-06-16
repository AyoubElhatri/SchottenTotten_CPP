#include "AIEasy.h"
#include"Player.h"
#include <cstdlib>  // rand()
#include <ctime>    // time()


AIEasy::AIEasy(unsigned int playerId, Set&& deck)
    : AI(playerId, std::move(deck)) {}

void AIEasy::playTurn(vector<unique_ptr<Cards>>& playerCards, GameBoard& gameBoard) {
    int cardIndex = chooseCardIndex(playerCards);
    int tileIndex = chooseTileIndex(gameBoard);

    if (cardIndex == -1 || tileIndex == -1) return;
    unique_ptr<Cards> selectedCard = std::move(playerCards[cardIndex]);

    // placeCardOnTile retourne void, donc on ne stocke pas de booléen ici
    gameBoard.placeCardOnTile(tileIndex, *selectedCard, m_playerID);

    // On supprime la carte du vecteur car elle est jouée
    playerCards.erase(playerCards.begin() + cardIndex);
}

int AIEasy::chooseCardIndex(const vector<unique_ptr<Cards>>& cards) {
    if (cards.empty()) return -1;
    return rand() % cards.size();
}

int AIEasy::chooseTileIndex(const GameBoard& gameBoard) {
    int boardSize = gameBoard.getBoardSize();
    for (int tries = 0; tries < boardSize * 2; ++tries) {
        int index = rand() % boardSize;
        if (gameBoard.isTileFree(index)) return index;
    }
    return -1;
}