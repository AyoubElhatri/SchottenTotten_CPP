#include "AIEasy.h"
#include <cstdlib>  // pour rand()
#include <ctime>    // pour time()

#include "AI.h"
#include "../GameBoard.h"
#include "../Player/Player.h"

void AIEasy::playTurn(std::vector<std::unique_ptr<Cards>>& playerCards, GameBoard& gameBoard) {
    int cardIndex = chooseCardIndex(playerCards);
    int tileIndex = chooseTileIndex(gameBoard);

    if (cardIndex == -1 || tileIndex == -1) return;

    // Récupérer la carte choisie (transfert de propriété)
    std::unique_ptr<Cards> selectedCard = std::move(playerCards[cardIndex]);

    // Poser la carte sur le plateau (tu peux adapter cette méthode)
    bool success = gameBoard.placeCardOnTile(tileIndex, *selectedCard, m_playerID);

    if (success) {
        // Retirer la carte du vecteur (puisque std::move a laissé un nullptr)
        playerCards.erase(playerCards.begin() + cardIndex);
    } else {
        // Remettre la carte dans le vecteur si échec
        playerCards[cardIndex] = std::move(selectedCard);
    }
}

int AIEasy::chooseCardIndex(const std::vector<std::unique_ptr<Cards>>& cards) {
    if (cards.empty())
        return -1;
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
