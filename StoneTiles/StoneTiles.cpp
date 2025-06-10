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

}