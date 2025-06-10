#include "Player.h"
#include "../Collections/Set.h"


Player::Player(unsigned int playerId, Set playerDecks) :playerID(playerId), playerDeck(std::move(playerDecks)) {}

bool Player::claimStoneTiles(unsigned int position) {
    shared_ptr<StoneTiles> tile;
    if (!tile)
        return false;
    if (tile ->isAlreadyClaimed())
        return false;
    if (!tile->isClaimable(this))
        return false;
    tile->claim(this);
    stoneTiles.push_back(tile);
    return true;
}



