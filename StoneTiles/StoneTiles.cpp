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

void StoneTiles::claim() {
    if (StoneTileIsClaimed) return;

    Rules* rules = Rules::getInstance();
    unsigned int maxCards = rules->getNumberMaxOfCardsPerTiles();
    auto& cards1 = getPlayerCardsOnTilesByPlayerId(1);
    auto& cards2 = getPlayerCardsOnTilesByPlayerId(2);

    if (cards1.getSize() > maxCards || cards2.getSize() > maxCards) {
        return;
    }

    // Les deux joueurs ont le maximum de cartes
    if (cards1.getSize() == maxCards && cards2.getSize() == maxCards) {
        CombinationType combo1 = cards1.evaluateCombination(*this);
        CombinationType combo2 = cards2.evaluateCombination(*this);

        if (combo1 > combo2) {
            claimedBy = 1;
            StoneTileIsClaimed = true;
            std::cout << Position << " --------- Joueur 1 a gagné la tuile (combo supérieur) ----------" << std::endl;
        }
        else if (combo2 > combo1) {
            claimedBy = 2;
            StoneTileIsClaimed = true;
            std::cout << Position << " --------- Joueur 2 a gagné la tuile (combo supérieur) ----------" << std::endl;
        }
        else {
            // En cas d'égalité de combinaison
            int sum1 = cards1.getTotalValue();
            int sum2 = cards2.getTotalValue();

            if (sum1 > sum2) {
                claimedBy = 1;
                StoneTileIsClaimed = true;
                std::cout << Position << " --------- Joueur 1 a gagné (égalité combo, somme supérieure) ----------" << std::endl;
            }
            else if (sum2 > sum1) {
                claimedBy = 2;
                StoneTileIsClaimed = true;
                std::cout << Position << " --------- Joueur 2 a gagné (égalité combo, somme supérieure) ----------" << std::endl;
            }
            else if (firstPlayerToFillTheStoneTile != nullptr) {
                claimedBy = firstPlayerToFillTheStoneTile->getPlayerID();
                StoneTileIsClaimed = true;
                std::cout << Position << " --------- Joueur " << claimedBy 
                         << " a gagné (égalité combo et somme, priorité au 1er à remplir) ----------" << std::endl;
            }
        }
    }

    // Revendication anticipée
    try {
        if (cards1.getSize() == maxCards && cards2.getSize() < maxCards) {
            CombinationType combo1 = cards1.evaluateCombination(*this);
            if (combo1 > CombinationType::ColorRun) {
                claimedBy = 1;
                StoneTileIsClaimed = true;
                std::cout << Position << " --------- Joueur 1 revendique (adverse ne peut pas battre combo) ----------" << std::endl;
            }
        } 
        else if (cards2.getSize() == maxCards && cards1.getSize() < maxCards) {
            CombinationType combo2 = cards2.evaluateCombination(*this);
            if (combo2 > CombinationType::ColorRun) {
                claimedBy = 2;
                StoneTileIsClaimed = true;
                std::cout << Position << " --------- Joueur 2 revendique (adverse ne peut pas battre combo) ----------" << std::endl;
            }
        }
    } catch (...) {
        // Ignorer les exceptions lors de l'évaluation incomplète
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
StoneTiles::StoneTiles(unsigned int pos) : Position(pos), NbOfPlayableCards(Rules::getInstance()->getNumberMaxOfCardsPerTiles()) {
    StoneTileIsClaimed=false;
    for (const auto& player : GameLogic::getInstance().getPlayers()) {
        PlayerCards.emplace(player->getPlayerID(), std::make_unique<Set>());
    }
}
