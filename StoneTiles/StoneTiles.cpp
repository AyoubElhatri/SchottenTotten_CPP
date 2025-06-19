#include "StoneTiles.h"
#include "../Player/Player.h"
#include <memory>
#include "../Logic/GameLogic.h"
#include"../Cards/TacticalCards.h"
#include <functional>

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


void StoneTiles::claim(unsigned int playerId) {
    if (StoneTileIsClaimed) return;

    unsigned int maxCards = getNbOfPlayableCards();
    auto& cards1 = getPlayerCardsOnTilesByPlayerId(playerId);
    unsigned int player2id = 3 - playerId;
    auto& cards2 = getPlayerCardsOnTilesByPlayerId(player2id);

    GameBoard& board = GameBoard::getInstance();
    Player* opponent = CGameLogic::getInstance().getPlayerById(player2id);

    // === Revendication anticipée ===
    if ((cards1.getSize() == maxCards && cards2.getSize() != maxCards) ||
        (cards2.getSize() == maxCards && cards1.getSize() != maxCards)) {

        Set& claimantCards = cards1.getSize() == maxCards ? cards1 : cards2;
        Set& opponentCards = cards1.getSize() == maxCards ? cards2 : cards1;
        unsigned int claimantId = cards1.getSize() == maxCards ? playerId : player2id;

        // Empêche la revendication anticipée si carte tactique sur la tuile
        for (auto& [_, set] : PlayerCards) {
            for (Cards* c : set->getRawCards()) {
                if (dynamic_cast<TacticalCards*>(c)) {
                    DisplayManager::getInstance()->output("There is a tactical card on the tile, you cannot pre-claim it.\n");
                    return;
                }
            }
        }

        // Rassembler toutes les cartes disponibles pour l’adversaire
        std::vector<Cards*> pool = opponentCards.getRawCards();

        // Main
        for (Cards* c : opponent->getPlayerDeck().getRawCards()) {
            pool.push_back(c);
        }

        // Pioche
        for (Cards* c : board.getRemainingClanCards().getRawCards()) {
            pool.push_back(c);
        }

        // Défausse
        for (Cards* c : board.getDiscardedCards().getRawCards()) {
            pool.push_back(c);
        }

        // Toutes les cartes posées sur le plateau (autres tuiles)
        for (auto& tile : board.getSharedTiles()) {
            if (tile.get() != this) {
                for (Cards* c : tile->getPlayerCardsOnTilesByPlayerId(player2id).getRawCards()) {
                    pool.push_back(c);
                }
            }
        }

        // On ne garde que les ClanCards
        std::vector<const ClanCards*> usable;
        for (Cards* c : pool) {
            if (auto* cc = dynamic_cast<ClanCards*>(c)) {
                usable.push_back(cc);
            }
        }

        // Générer toutes les combinaisons possibles de maxCards
        int n = usable.size();
        bool canBeat = false;
        std::vector<int> indices(maxCards);
        for (int i = 0; i < maxCards; ++i) indices[i] = i;

        do {
            Set simulated;
            for (int i : indices) {
                simulated.addCard(std::make_unique<ClanCards>(*usable[i]));
            }

            int evalSim = simulated.evaluateCombination(*this);
            int evalClaim = claimantCards.evaluateCombination(*this);

            if (evalSim > evalClaim ||
                (evalSim == evalClaim && simulated.getTotalValue() > claimantCards.getTotalValue())) {
                canBeat = true;
                break;
            }

            // Générer prochaine combinaison
            int i = maxCards - 1;
            while (i >= 0 && indices[i] == i + n - maxCards) --i;
            if (i < 0) break;
            ++indices[i];
            for (int j = i + 1; j < maxCards; ++j)
                indices[j] = indices[j - 1] + 1;

        } while (true);

        if (!canBeat) {
            StoneTileIsClaimed = true;
            claimedBy = claimantId;
            DisplayManager::getInstance()->output("Revendication anticipée réussie par le joueur " + std::to_string(claimantId) + " sur la tuile " + std::to_string(Position) + "\n");
            return;
        }
    }

    // === Revendication normale ===
    if (cards1.getSize() == maxCards && cards2.getSize() == maxCards) {
        if (comboType == CombinationType::Sum) {
            if (cards1.getTotalValue() > cards2.getTotalValue()) {
                StoneTileIsClaimed = true;
                claimedBy = playerId;
            } else if (cards2.getTotalValue() > cards1.getTotalValue()) {
                StoneTileIsClaimed = true;
                claimedBy = player2id;
            } else {
                StoneTileIsClaimed = true;
                claimedBy = getFirstPlayerToFillTheStoneTile()->getPlayerID();
            }
        } else {
            int eval1 = cards1.evaluateCombination(*this);
            int eval2 = cards2.evaluateCombination(*this);

            if (eval1 > eval2) {
                StoneTileIsClaimed = true;
                claimedBy = playerId;
            } else if (eval2 > eval1) {
                StoneTileIsClaimed = true;
                claimedBy = player2id;
            } else {
                if (cards1.getTotalValue() > cards2.getTotalValue()) {
                    StoneTileIsClaimed = true;
                    claimedBy = playerId;
                } else if (cards2.getTotalValue() > cards1.getTotalValue()) {
                    StoneTileIsClaimed = true;
                    claimedBy = player2id;
                } else {
                    StoneTileIsClaimed = true;
                    claimedBy = getFirstPlayerToFillTheStoneTile()->getPlayerID();
                }
            }
        }
    }
}


StoneTiles::StoneTiles(unsigned int pos) : Position(pos), NbOfPlayableCards(Rules::getInstance()->getNumberMaxOfCardsPerTiles()),firstPlayerToFillTheStoneTile(nullptr) {
    StoneTileIsClaimed=false;
    for (const auto& player : CGameLogic::getInstance().getPlayers()) {
        PlayerCards.emplace(player->getPlayerID(), std::make_unique<Set>());
    }
}
