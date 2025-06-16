#include "Player.h"
#include "../Collections/Set.h"
#include "../GameBoard.h"

Player::Player(unsigned int playerId, Set&& playerDecks)
    : playerID(playerId), playerDeck(std::move(playerDecks)) {}

/*void Player::drawClanCards(unsigned int count) {
    GameBoard &gameBoard = GameBoard::getInstance();

    for (unsigned int i = 0; i < count; i++) {
        Set& remainingClanCards = gameBoard.getRemainingClanCards();
        remainingClanCards.moveCard(0, playerDeck);
    }

}



void Player::drawTacticalCards(unsigned int count) {
    GameBoard &gameBoard = GameBoard::getInstance();

    for (unsigned int i = 0; i < count; i++) {
        Set& remainingTacticalCards = gameBoard.getRemainingTacticalCards();
        remainingTacticalCards.moveCard(0, playerDeck);
    }
}*/