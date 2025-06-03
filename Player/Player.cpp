#include "Player.h"
#include "../Collections/Set.h"


Player::Player(unsigned int playerId, Set playerDecks) :playerID(playerId), playerDeck(std::move(playerDecks)) {}


