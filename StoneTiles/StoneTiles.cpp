#include "StoneTiles.h"
#include "../Player/Player.h"
#include <memory>



void StoneTiles::addCardToPlayer(unsigned int playerId, string Cardname,Set provenanceOfTheCard) {
    unsigned int nbrMaxOnStoneTile = getNbOfPlayableCards();
    if (playerId == 1) {
        if (nbrMaxOnStoneTile == PlayerCards1.getSize()) {
            throw std::out_of_range("Player 1 already has the maximum number of cards on this tile.");
        }
        PlayerCards1.moveCard(Cardname, provenanceOfTheCard);
    }
    else if (playerId == 2) {
    if (nbrMaxOnStoneTile == PlayerCards2.getSize()) {
        throw std::out_of_range("Player 1 already has the maximum number of cards on this tile.");
    }
    PlayerCards2.moveCard(Cardname, provenanceOfTheCard);}
    else {
        throw std::invalid_argument("Invalid player ID");
    }
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

    if (PlayerCards1.getSize() == maxCards && PlayerCards2.getSize() == maxCards && maxCards < 4) {
        CombinationType combo1 = PlayerCards1.evaluateCombination(*this);
        CombinationType combo2 = PlayerCards2.evaluateCombination(*this);

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
            int sum1 = PlayerCards1.getTotalValue();
            int sum2 = PlayerCards2.getTotalValue();

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
            else {
                // Égalité parfaite : priorité à celui qui a joué la 3e carte en premier
                if (firstPlayerToFillTheStoneTile != nullptr) {
                    claimedBy = firstPlayerToFillTheStoneTile->getPlayerID();
                    StoneTileIsClaimed = true;
                    std::cout << Position << " --------- Joueur " << claimedBy
                              << " a gagné (égalité combo et somme, priorité au 1er à remplir) ----------" << std::endl;
                } else {
                    std::cout << " Tuile " << Position << " : égalité parfaite, mais aucun joueur enregistré comme 1er.\n";
                }
            }
        }
    }


    else if (PlayerCards1.getSize() == maxCards && PlayerCards2.getSize() < maxCards && maxCards < 4) {
        claimedBy = 1;
        StoneTileIsClaimed = true;
        std::cout << Position << " --------- Joueur 1 a gagné (adverse incomplet) ----------" << std::endl;
    }
    else if (PlayerCards2.getSize() == maxCards && PlayerCards1.getSize() < maxCards && maxCards < 4) {
        claimedBy = 2;
        StoneTileIsClaimed = true;
        std::cout << Position << " --------- Joueur 2 a gagné (adverse incomplet) ----------" << std::endl;
    }
}





