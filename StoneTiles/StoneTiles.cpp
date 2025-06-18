#include "StoneTiles.h"
#include "../Player/Player.h"
#include <memory>
#include "../Logic/GameLogic.h"


void StoneTiles::addCardOnTilesOfPlayer(unsigned int playerId, const string& cardName, Set& provenanceOfTheCard) {
    unsigned int nbrMaxOnStoneTile = getNbOfPlayableCards();

    // Vérifier si le joueur a déjà le nombre maximum de cartes
    if (getPlayerCardsOnTilesByPlayerId(playerId).getSize() >= nbrMaxOnStoneTile) {
        throw std::out_of_range("Player " + std::to_string(playerId) + 
                               " already has the maximum number of cards on this tile.");
    }

    // Déplacer la carte
    provenanceOfTheCard.moveCard(cardName, getPlayerCardsOnTilesByPlayerId(playerId));
}

std::unique_ptr<Cards> StoneTiles::removeCardFromPlayer(unsigned int playerId, unsigned int cardIndex) {
    Set& playerCards = getPlayerCardsOnTilesByPlayerId(playerId);
    
    if (cardIndex >= playerCards.getSize()) {
        throw std::out_of_range("Index invalide pour le joueur " + std::to_string(playerId));
    }
    
    return playerCards.getCardbyIndex(cardIndex);
}

void StoneTiles::claim(unsigned int playerId) {

    if (StoneTileIsClaimed) return;

    unsigned int maxCards = getNbOfPlayableCards();
    auto& cards1 = getPlayerCardsOnTilesByPlayerId(playerId);
    unsigned int player2id=3- playerId; // Assuming player IDs are 1 and 2
    auto& cards2 = getPlayerCardsOnTilesByPlayerId(3-playerId);


    // Vérifier si le joueur a déjà le nombre maximum de cartes
    if (cards1.getSize()== maxCards && cards2.getSize() == maxCards) {
        if (comboType == CombinationType::Sum) {
            if (cards1.getTotalValue() > cards2.getTotalValue()) {
                StoneTileIsClaimed = true;
                claimedBy = playerId;
                }
            else if (cards2.getTotalValue()>cards1.getTotalValue()) {
                StoneTileIsClaimed = true;
                claimedBy = 3-playerId;
            }
            else {
                StoneTileIsClaimed = true;
                claimedBy = getFirstPlayerToFillTheStoneTile()->getPlayerID();
            }
        }
        else  {
            if (cards1.evaluateCombination(*this) > cards2.evaluateCombination(*this)) {  // le 1 claim
                StoneTileIsClaimed = true;
                claimedBy = playerId;
            }
            else if (cards2.evaluateCombination(*this) > cards1.evaluateCombination(*this)) {
                StoneTileIsClaimed = true;
                claimedBy = 3-playerId;
            }
            else {
                StoneTileIsClaimed = true;
                claimedBy = getFirstPlayerToFillTheStoneTile()->getPlayerID();
            }
        }
    }
    else {

        //revendication anticipé
    }
}

void StoneTiles::printStoneTiles() {
    DisplayManager::getInstance()->output("StoneTiles " + std::to_string(getPosition()) + " :\n");

    // Utiliser la map complète pour l'itération
    for (const auto& [playerId, cardSet] : getPlayerCards()) {
        DisplayManager::getInstance()->output("Joueur " + std::to_string(playerId) + " :");
        cardSet->printSet();
        DisplayManager::getInstance()->output("\n");
    }

    DisplayManager::getInstance()->output("Cartes en mode combat :");
    getCombatModeCards().printSet();
    DisplayManager::getInstance()->output("\n");
}
StoneTiles::StoneTiles(unsigned int pos) : Position(pos), NbOfPlayableCards(Rules::getInstance()->getNumberMaxOfCardsPerTiles()),firstPlayerToFillTheStoneTile(nullptr) {
    StoneTileIsClaimed=false;
    for (const auto& player : GameLogic::getInstance().getPlayers()) {
        PlayerCards.emplace(player->getPlayerID(), std::make_unique<Set>());
    }
}
