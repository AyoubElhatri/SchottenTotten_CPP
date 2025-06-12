#include "Player.h"
#include "../Collections/Set.h"
#include "../GameBoard.h"


Player::Player(unsigned int playerId, Set&& playerDecks) : playerID(playerId), playerDeck(std::move(playerDecks)) {}

bool Player::claimStoneTiles(unsigned int position) {
    GameBoard& gameBoard = GameBoard::getInstance();
    const auto& tiles = gameBoard.getSharedTiles();
    auto it = std::find_if(tiles.begin(), tiles.end(),
        [position](const std::shared_ptr<StoneTiles>& t) {
            return t->getPosition() == position;
        });
    if (it == tiles.end())
        return false;

    std::shared_ptr<StoneTiles> tile = *it;
    if (tile->isAlreadyClaimed())
        return false;
    tile->claim(this);
    stoneTiles.push_back(tile);

    return true;
}

void Player::drawClanCards(unsigned int count) {
    GameBoard& gameBoard = GameBoard::getInstance();
    for (unsigned int i = 0; i < count; i++) {
        std::unique_ptr<Cards> card = gameBoard.drawClanCard();
        if (card) {
            playerDeck.addCard(card);
        }
    }
}



