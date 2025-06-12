#include "StoneTiles.h"

/*bool StoneTiles::isClaimable(Player* player) const {
    if (!player) return false;

    const Set& playerCards = (player->getPlayerID() == 1) ? PlayerCards1 : PlayerCards2;
    const Set& opponentCards = (player->getPlayerID() == 1) ? PlayerCards2 : PlayerCards1;

    if (playerCards.getSize() < PlayableCards || opponentCards.getSize() < PlayableCards)
        return false;

    int playerTotal = playerCards.getTotalValue();
    int opponentTotal = opponentCards.getTotalValue();

    return playerTotal > opponentTotal;
}*/
/*
void StoneTiles::claim(Player* player) {
    if (!isAlreadyClaimed())
        return;
    if (!PlayerCards1.isComplete() || !PlayerCards2.isComplete())
        return;
    auto combo1 = PlayerCards1.evaluateCombination();
    auto combo2 = PlayerCards2.evaluateCombination();
    if (combo1 > combo2 && player == PlayerCards1.getOwner()) {
        claimedBy = unique_ptr<Player>(player);
        StoneTileIsClaimed = true;
    }
    else if (combo2 > combo1 && player == PlayerCards2.getOwner()) {
        claimedBy = unique_ptr<Player>(player);
        StoneTileIsClaimed = true;
    }

}*/

void StoneTiles::addCardToPlayer(unsigned int playerId, std::unique_ptr<Cards> cards) {
    if (playerId == 1) {
        PlayerCards1.addCard(move(cards));
    }
    else if (playerId == 2) {
    PlayerCards2.addCard(move(cards));}
    else {
        throw std::invalid_argument("Invalid player ID");
    }
}

bool StoneTiles::canPlaceCard() const {
    return !this->isAlreadyClaimed() ;
}

std::unique_ptr<Cards> StoneTiles::removeCardFromPlayer(unsigned int playerId, unsigned int cardIndex) {
    if (playerId == 1) {
        if (cardIndex >= PlayerCards1.getSize()) {
            throw std::out_of_range("Index invalide dans PlayerCards1");
        }
        return PlayerCards1.getCardbyIndex(cardIndex);
    } else if (playerId == 2) {
        if (cardIndex >= PlayerCards2.getSize()) {
            throw std::out_of_range("Index invalide dans PlayerCards2");
        }
        return PlayerCards2.getCardbyIndex(cardIndex);
    } else {
        throw std::invalid_argument("ID joueur invalide (doit être 1 ou 2)");
    }
}
