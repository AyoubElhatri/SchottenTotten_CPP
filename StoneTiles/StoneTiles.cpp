#include "StoneTiles.h"
#include "../Player/Player.h"
#include <memory>
#include "../Logic/GameLogic.h"
#include"../Cards/TacticalCards.h"


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

// void StoneTiles::claim(unsigned int playerId) {
//
//     if (StoneTileIsClaimed) return;
//
//     unsigned int maxCards = getNbOfPlayableCards();
//     auto& cards1 = getPlayerCardsOnTilesByPlayerId(playerId);
//     unsigned int player2id=3- playerId; // Assuming player IDs are 1 and 2
//     auto& cards2 = getPlayerCardsOnTilesByPlayerId(player2id);
//
//     /*z
//     if ((cards1.getSize() == maxCards && cards2.getSize() != maxCards) ||
//     (cards1.getSize() != maxCards && cards2.getSize() == maxCards)) {
//
//     // === Revendication anticipée ===
//     // On considère que cards1 est celui qui tente de revendiquer
//
//     Set& claimantCards = cards1.getSize() == maxCards ? cards1 : cards2;
//     Set& opponentCards = cards1.getSize() == maxCards ? cards2 : cards1;
//     unsigned int claimantId = cards1.getSize() == maxCards ? playerId : player2id;
//
//     // Vérifie que l'adversaire n'a pas de carte tactique
//     for (auto* c : opponentCards.getRawCards()) {
//         if (dynamic_cast<TacticalCards*>(c)) return; // Interdit la revendication anticipée
//     }
//
//     // Récupération des cartes restantes
//     std::vector<Cards*> pool;
//     GameBoard& board = GameBoard::getInstance();
//
//     for (auto* c : board.getRemainingClanCards().getRawCards()) {
//         pool.push_back(c);
//     }
//     Player* opponent = GameLogic::getInstance().getPlayerById(3 - claimantId);
//     for (auto* c : opponent->getPlayerDeck().getRawCards()) {
//         pool.push_back(c);
//     }
//
//     int needed = maxCards - opponentCards.getSize();
//
//     bool canBeat = false;
//     std::vector<Cards*> current = opponentCards.getRawCards();
//
//     std::function<bool(int, std::vector<Cards*>&)> dfs;
//     dfs = [&](int index, std::vector<Cards*>& temp) -> bool {
//         if ((int)temp.size() == maxCards) {
//             Set simulatedSet;
//             for (auto* c : temp) {
//                 const ClanCards* cc = dynamic_cast<ClanCards*>(c);
//                 if (!cc) return false;  // Skip invalid
//                 simulatedSet.addCard(std::make_unique<ClanCards>(*cc));
//             }
//             if (simulatedSet.evaluateCombination(*this) > claimantCards.evaluateCombination(*this)) return true;
//             if (simulatedSet.evaluateCombination(*this) == claimantCards.evaluateCombination(*this) &&
//                 simulatedSet.getTotalValue() > claimantCards.getTotalValue()) return true;
//             return false;
//         }
//
//         for (size_t i = index; i < pool.size(); ++i) {
//             temp.push_back(pool[i]);
//             if (dfs(i + 1, temp)) return true;
//             temp.pop_back();
//         }
//         return false;
//     };
//
//     std::vector<Cards*> attempt = current;
//     canBeat = dfs(0, attempt);
//
//     if (!canBeat) {
//         StoneTileIsClaimed = true;
//         claimedBy = claimantId;
//         std::cout << "Revendication anticipée réussie par le joueur " << claimantId
//                   << " sur la tuile " << Position << std::endl;
//         return;
//     }
// }*/
//     // Vérifier si le joueur a déjà le nombre maximum de cartes
//     if (cards1.getSize()== maxCards && cards2.getSize() == maxCards) {
//         if (comboType == CombinationType::Sum) {
//             if (cards1.getTotalValue() > cards2.getTotalValue()) {
//                 StoneTileIsClaimed = true;
//                 claimedBy = playerId;
//                 }
//             else if (cards2.getTotalValue()>cards1.getTotalValue()) {
//                 StoneTileIsClaimed = true;
//                 claimedBy = player2id;
//             }
//             else {
//                 StoneTileIsClaimed = true;
//                 claimedBy = getFirstPlayerToFillTheStoneTile()->getPlayerID();
//             }
//         }
//         else  {
//             if (cards1.evaluateCombination(*this) > cards2.evaluateCombination(*this)) {  // le 1 claim
//                 StoneTileIsClaimed = true;
//                 claimedBy = playerId;
//
//             }
//             else if (cards2.evaluateCombination(*this) > cards1.evaluateCombination(*this)) {
//                 StoneTileIsClaimed = true;
//                 claimedBy = player2id;
//             }
//             else {
//                 if (cards1.getTotalValue() > cards2.getTotalValue()) {
//                     StoneTileIsClaimed = true;
//                     claimedBy = playerId;
//                 }
//                 else if (cards2.getTotalValue()>cards1.getTotalValue()) {
//                     StoneTileIsClaimed = true;
//                     claimedBy = player2id;
//                 }
//                 else {
//                     StoneTileIsClaimed = true;
//                     claimedBy = getFirstPlayerToFillTheStoneTile()->getPlayerID();
//                 }
//             }
//         }
//     }
//     else {
//
//     }
// }
void StoneTiles::claim(unsigned int playerId) {
    if (StoneTileIsClaimed) return;

    unsigned int maxCards = getNbOfPlayableCards();
    auto& cards1 = getPlayerCardsOnTilesByPlayerId(playerId);
    unsigned int player2id = 3 - playerId;
    auto& cards2 = getPlayerCardsOnTilesByPlayerId(player2id);

    GameBoard& board = GameBoard::getInstance();
    Player* opponent = GameLogic::getInstance().getPlayerById(player2id);
    Player* claimant = GameLogic::getInstance().getPlayerById(playerId);

    // === Revendication anticipée ===
    if ((cards1.getSize() == maxCards && cards2.getSize() != maxCards) ||
        (cards2.getSize() == maxCards && cards1.getSize() != maxCards)) {

        Set& claimantCards = cards1.getSize() == maxCards ? cards1 : cards2;
        Set& opponentCards = cards1.getSize() == maxCards ? cards2 : cards1;
        unsigned int claimantId = cards1.getSize() == maxCards ? playerId : player2id;
        unsigned int opponentId = 3 - claimantId;

        // Si carte tactique présente sur la tuile, on bloque la revendication anticipée
        for (auto& [_, set] : PlayerCards) {
            for (Cards* c : set->getRawCards()) {
                if (dynamic_cast<TacticalCards*>(c)) return;
            }
        }

        // Récupérer toutes les cartes restantes potentielles de l'adversaire
        std::vector<Cards*> availableCards = opponentCards.getRawCards();  // celles déjà posées
        for (Cards* c : board.getRemainingClanCards().getRawCards()) {
            availableCards.push_back(c);
        }
        for (Cards* c : opponent->getPlayerDeck().getRawCards()) {
            availableCards.push_back(c);
        }

        int missing = maxCards - opponentCards.getSize();

        // Générer toutes les combinaisons possibles
        std::function<bool(int, std::vector<Cards*>&)> dfs;
        dfs = [&](int idx, std::vector<Cards*>& combination) -> bool {
            if ((int)combination.size() == maxCards) {
                Set simulated;
                for (Cards* c : combination) {
                    const auto* cc = dynamic_cast<ClanCards*>(c);
                    if (!cc) return false;
                    simulated.addCard(std::make_unique<ClanCards>(*cc));
                }

                int evalSim = simulated.evaluateCombination(*this);
                int evalClaimant = claimantCards.evaluateCombination(*this);
                if (evalSim > evalClaimant ||
                    (evalSim == evalClaimant && simulated.getTotalValue() > claimantCards.getTotalValue())) {
                    return true;  // Peut battre le demandeur
                }
                return false;
            }

            for (size_t i = idx; i < availableCards.size(); ++i) {
                combination.push_back(availableCards[i]);
                if (dfs(i + 1, combination)) return true;
                combination.pop_back();
            }
            return false;
        };

        std::vector<Cards*> attempt = opponentCards.getRawCards(); // base
        bool canStillWin = dfs(0, attempt);

        if (!canStillWin) {
            StoneTileIsClaimed = true;
            claimedBy = claimantId;
            std::cout << "🏁 Revendication anticipée réussie par le joueur " << claimantId
                      << " sur la tuile " << Position << std::endl;
            return;
        }
    }

    // === Revendication normale ===
    if (cards1.getSize() == maxCards && cards2.getSize() == maxCards) {
        if (comboType == CombinationType::Sum) {
            if (cards1.getTotalValue() > cards2.getTotalValue()) {
                StoneTileIsClaimed = true;
                claimedBy = playerId;
            }
            else if (cards2.getTotalValue() > cards1.getTotalValue()) {
                StoneTileIsClaimed = true;
                claimedBy = player2id;
            }
            else {
                StoneTileIsClaimed = true;
                claimedBy = getFirstPlayerToFillTheStoneTile()->getPlayerID();
            }
        } else {
            int eval1 = cards1.evaluateCombination(*this);
            int eval2 = cards2.evaluateCombination(*this);

            if (eval1 > eval2) {
                StoneTileIsClaimed = true;
                claimedBy = playerId;
            }
            else if (eval2 > eval1) {
                StoneTileIsClaimed = true;
                claimedBy = player2id;
            }
            else {
                if (cards1.getTotalValue() > cards2.getTotalValue()) {
                    StoneTileIsClaimed = true;
                    claimedBy = playerId;
                }
                else if (cards2.getTotalValue() > cards1.getTotalValue()) {
                    StoneTileIsClaimed = true;
                    claimedBy = player2id;
                }
                else {
                    StoneTileIsClaimed = true;
                    claimedBy = getFirstPlayerToFillTheStoneTile()->getPlayerID();
                }
            }
        }
    }
}
//version originale
/*void StoneTiles::claim(unsigned int playerId) {
    if (StoneTileIsClaimed) return;

    unsigned int maxCards = getNbOfPlayableCards();
    auto& cards1 = getPlayerCardsOnTilesByPlayerId(playerId);
    unsigned int player2id = 3 - playerId; // Assuming player IDs are 1 and 2
    auto& cards2 = getPlayerCardsOnTilesByPlayerId(player2id);

    if ((cards1.getSize() == maxCards && cards2.getSize() != maxCards) ||
        (cards1.getSize() != maxCards && cards2.getSize() == maxCards)) {
        // Revendication anticipée
        // (Logique à ajouter ici)
    }
    else if (cards1.getSize() == maxCards && cards2.getSize() == maxCards) {
        if (comboType == CombinationType::Sum) {
            if (cards1.getTotalValue() > cards2.getTotalValue()) {
                StoneTileIsClaimed = true;
                claimedBy = playerId;
            }
            else if (cards2.getTotalValue() > cards1.getTotalValue()) {
                StoneTileIsClaimed = true;
                claimedBy = player2id;
            }
            else {
                StoneTileIsClaimed = true;
                claimedBy = getFirstPlayerToFillTheStoneTile()->getPlayerID();
            }
        }
        else {
            int eval1 = cards1.evaluateCombination(*this);
            int eval2 = cards2.evaluateCombination(*this);

            if (eval1 > eval2) {
                StoneTileIsClaimed = true;
                claimedBy = playerId;
            }
            else if (eval2 > eval1) {
                StoneTileIsClaimed = true;
                claimedBy = player2id;
            }
            else {
                if (cards1.getTotalValue() > cards2.getTotalValue()) {
                    StoneTileIsClaimed = true;
                    claimedBy = playerId;
                }
                else if (cards2.getTotalValue() > cards1.getTotalValue()) {
                    StoneTileIsClaimed = true;
                    claimedBy = player2id;
                }
                else {
                    StoneTileIsClaimed = true;
                    claimedBy = getFirstPlayerToFillTheStoneTile()->getPlayerID();
                }
            }
        }
    }
    else {
        // Aucun joueur n'a encore rempli complètement les cartes
    }
}*/


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
