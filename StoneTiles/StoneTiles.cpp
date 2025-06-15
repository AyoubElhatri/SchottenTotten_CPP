#include "StoneTiles.h"
#include "../Player/Player.h"
#include <memory>



void StoneTiles::addCardToPlayer(unsigned int playerId, string Cardname,Set provenanceOfTheCard) {

    if (playerId == 1) {
        PlayerCards1.moveCard(Cardname, provenanceOfTheCard);
    }
    else if (playerId == 2) {
    PlayerCards2.moveCard(Cardname, provenanceOfTheCard);}
    else {
        throw std::invalid_argument("Invalid player ID");
    }
}

bool StoneTiles::canPlaceCard() const {
    return !isAlreadyClaimed() ;
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

void StoneTiles::claim() {
    if (StoneTileIsClaimed)
        return;
    Rules* rules = Rules::getInstance();
    unsigned int maxCards = rules->getNumberMaxOfCardsPerTiles();
    if (PlayerCards1.getSize() > maxCards || PlayerCards2.getSize() > maxCards) {
        return;
    }
    CombinationType combo1 = PlayerCards1.evaluateCombination(*this);
    CombinationType combo2 = PlayerCards2.evaluateCombination(*this);
    if (combo1 > combo2) {
        claimedBy = 1;
        StoneTileIsClaimed = true;
        std::cout << Position << "---------Player 1 a gagné la tuile----------"<<endl;
    }
    else if (combo2 > combo1) {
        claimedBy = 2;
        StoneTileIsClaimed = true;
        std::cout << Position << "---------Player 1 a gagné la tuile----------"<<endl;
    }
    else {
        if (firstPlayerToFillTheStoneTile != nullptr) {
            claimedBy = firstPlayerToFillTheStoneTile->getPlayerID();
            StoneTileIsClaimed = true;
            std::cout << Position << " --------- Joueur " << claimedBy
                      << " a gagné la tuile (égalité combo, priorité à celui qui a rempli en premier) ----------"
                      << std::endl;
        } else {
            std::cout <<"Tuile non revendiquée" << endl;
        }
    }



}

