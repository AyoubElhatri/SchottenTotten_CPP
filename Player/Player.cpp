#include "Player.h"
#include "../Collections/Set.h"
#include "../GameBoard.h"

Player::Player(unsigned int playerId, Set&& playerDecks)
    : playerID(playerId), playerDeck(std::move(playerDecks)) {}

void Player::drawClanCards(unsigned int count) {
    GameBoard &gameBoard = GameBoard::getInstance();
    for (unsigned int i = 0; i < count; i++) {
        std::unique_ptr<Cards> card = gameBoard.drawClanCard();
        if (card) {
            playerDeck.addCard(std::move(card));
        }
    }
}


/*void Player::drawTacticalCards(unsigned int count) {
    // À implémenter si tu veux gérer les cartes tactiques
}*/
