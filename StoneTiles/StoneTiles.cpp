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
    Player* claimant = CGameLogic::getInstance().getPlayerById(playerId);

    // === Revendication anticipée ===
    if ((cards1.getSize() == maxCards && cards2.getSize() != maxCards) ||
        (cards2.getSize() == maxCards && cards1.getSize() != maxCards)) {

        Set& claimantCards = cards1.getSize() == maxCards ? cards1 : cards2;
        Set& opponentCards = cards1.getSize() == maxCards ? cards2 : cards1;
        unsigned int claimantId;
        if (cards1.getSize() == maxCards) {
            claimantId = playerId;
        } else {
            claimantId = player2id;
        }

        // Si carte tactique présente sur la tuile, on bloque la revendication anticipée
        for (auto& [number, set] : PlayerCards) {
            for (Cards* c : set->getRawCards()) {
                if (dynamic_cast<TacticalCards*>(c)){  DisplayManager::getInstance()->output("There is a tactical card on the tile, you cannot pre-claim it.");
                    return;
                }
            }
        }


        bool canStillWin = false;
        std::vector<Cards*> availableCards = opponentCards.getRawCards();
        for (Cards* c : board.getRemainingClanCards().getRawCards()) {
            availableCards.push_back(c);
        }
        for (Cards* c : opponent->getPlayerDeck().getRawCards()) {
            availableCards.push_back(c);
        }

        int n = availableCards.size();
        int k = maxCards;
        std::vector<int> indices(k);
        for (int i = 0; i < k; ++i) indices[i] = i;

        while (true) {
            // Construire la combinaison
            Set simulated;
            bool valid = true;
            for (int idx : indices) {
                const auto* cc = dynamic_cast<ClanCards*>(availableCards[idx]);
                if (!cc) {
                    valid = false;
                    break;
                }
                simulated.addCard(std::make_unique<ClanCards>(*cc));
            }
            if (valid) {
                int evalSim = simulated.evaluateCombination(*this);
                int evalClaimant = claimantCards.evaluateCombination(*this);
                if (evalSim > evalClaimant ||
                    (evalSim == evalClaimant && simulated.getTotalValue() > claimantCards.getTotalValue())) {
                    canStillWin = true;
                    break;
                    }
            }

            int i = k - 1;
            while (i >= 0 && indices[i] == i + n - k) {
                --i;
            }

            if (i < 0) {
                break;
            }

            ++indices[i];
            for (int j = i + 1; j < k; ++j) {
                indices[j] = indices[j - 1] + 1;
            }

            if (!canStillWin) {
                StoneTileIsClaimed = true;
                claimedBy = claimantId;
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
}


StoneTiles::StoneTiles(unsigned int pos) : Position(pos), NbOfPlayableCards(Rules::getInstance()->getNumberMaxOfCardsPerTiles()),firstPlayerToFillTheStoneTile(nullptr) {
    StoneTileIsClaimed=false;
    for (const auto& player : CGameLogic::getInstance().getPlayers()) {
        PlayerCards.emplace(player->getPlayerID(), std::make_unique<Set>());
    }
}
