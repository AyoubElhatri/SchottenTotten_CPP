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



StoneTiles::StoneTiles(unsigned int pos) : Position(pos), NbOfPlayableCards(Rules::getInstance()->getNumberMaxOfCardsPerTiles()),firstPlayerToFillTheStoneTile(nullptr) {
    StoneTileIsClaimed=false;
    for (const auto& player : CGameLogic::getInstance().getPlayers()) {
        PlayerCards.emplace(player->getPlayerID(), std::make_unique<Set>());
    }
}
