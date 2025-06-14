/*#include "Stratege.h"
#include "../GameBoard.h"
#include <iostream>
#include <vector>
#include <tuple>

void Stratege::getEvent() {
    GameBoard& gameBoard = GameBoard::getInstance();
    unsigned int currentPlayerId = gameBoard.getCurrentPlayerId();

    std::cout << "[Stratège] Choisissez une carte Clan ou Tactique de votre côté sur une borne non revendiquée." << std::endl;

    // Récup les bornes non revendiquées
    std::vector<std::shared_ptr<StoneTiles>> unclaimedBorders;
    for (auto& tile : gameBoard.getSharedTiles()) {
        if (!tile->isAlreadyClaimed()) {
            unclaimedBorders.push_back(tile);
        }
    }

    if (unclaimedBorders.empty()) {
        std::cout << "Aucune borne non revendiquée disponible." << std::endl;
        return;
    }

    // Lister toutes les cartes du joueur courant sur les bornes non revendiquées
    std::vector<std::tuple<unsigned int, unsigned int>> playerCards; // (bornePos, indexCarte)
    unsigned int displayIndex = 0;

    for (auto& tile : unclaimedBorders) {
        unsigned int pos = tile->getPosition();

        // Accéder aux cartes du joueur
        Set& cardsSet = (currentPlayerId == 1) ? tile->getPlayerCards1() : tile->getPlayerCards2();

        for (unsigned int i = 0; i < cardsSet.getSize(); ++i) {
            std::cout << displayIndex << ") Borne " << pos << ", carte " << i << std::endl;
            playerCards.emplace_back(pos, i);
            ++displayIndex;
        }
    }

    if (playerCards.empty()) {
        std::cout << "Aucune carte disponible à déplacer ou défausser." << std::endl;
        return;
    }

    // Choix de la carte à déplacer ou défausser
    unsigned int choice;
    std::cout << "Choisissez la carte à déplacer ou défausser : ";
    std::cin >> choice;

    if (choice >= playerCards.size()) {
        std::cout << "Choix invalide." << std::endl;
        return;
    }

    auto [fromPos, cardIndex] = playerCards[choice];

    // Proposer déplacement ou défausse
    std::cout << "Tapez 1 pour déplacer la carte vers une autre borne, 2 pour la défausser : ";
    unsigned int action;
    std::cin >> action;

    if (action != 1 && action != 2) {
        std::cout << "Action invalide." << std::endl;
        return;
    }

    try {
        std::shared_ptr<StoneTiles> fromTile = gameBoard.findTileByPosition(fromPos);
        auto card = fromTile->removeCardFromPlayer(currentPlayerId, cardIndex);

        if (action == 1) {
            // Afficher bornes non revendiquées pour destination
            std::cout << "Bornes non revendiquées disponibles pour déplacer la carte :" << std::endl;
            for (unsigned int i = 0; i < unclaimedBorders.size(); ++i) {
                if (unclaimedBorders[i]->getPosition() != fromPos) { // éviter la même borne
                    std::cout << i << ") Borne " << unclaimedBorders[i]->getPosition() << std::endl;
                }
            }

            unsigned int destChoice;
            std::cout << "Choisissez la borne de destination : ";
            std::cin >> destChoice;

            if (destChoice >= unclaimedBorders.size() || unclaimedBorders[destChoice]->getPosition() == fromPos) {
                std::cout << "Choix invalide." << std::endl;
                // Remettre la carte dans la borne d'origine
                fromTile->addCardToPlayer(currentPlayerId, std::move(card));
                return;
            }

            unsigned int toPos = unclaimedBorders[destChoice]->getPosition();
            std::shared_ptr<StoneTiles> toTile = gameBoard.findTileByPosition(toPos);
            toTile->addCardToPlayer(currentPlayerId, std::move(card));
            std::cout << "Carte déplacée avec succès." << std::endl;

        } else {
            // Défausse
            gameBoard.getDiscardedCards().addCard(std::move(card));
            std::cout << "Carte défaussée avec succès." << std::endl;
        }
    } catch (const std::exception& e) {
        std::cout << "Erreur : " << e.what() << std::endl;
    }
}*/

#include "Stratege.h"
#include<iostream>
using namespace std;

