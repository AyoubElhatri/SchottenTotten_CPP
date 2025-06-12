/*#include "Banshee.h"
#include "../GameBoard.h"
#include <iostream>

void Banshee::getEvent() {
    GameBoard& gameBoard = GameBoard::getInstance();
    unsigned int currentPlayerId = gameBoard.getCurrentPlayerId();
    unsigned int opponentId = (currentPlayerId == 1) ? 2 : 1;

    std::cout << "[Banshee] Choisissez une carte adverse à défausser sur une borne non revendiquée." << std::endl;

    // Récupérer les bornes non revendiquées
    std::vector<std::shared_ptr<StoneTiles>> unclaimedBorders;
    for (auto& tile : gameBoard.getSharedTiles()) {
        if (!tile->isAlreadyClaimed()) {
            unclaimedBorders.push_back(tile);
        }
    }

    // Collecte des cartes adverses à défausser
    std::vector<std::tuple<unsigned int, unsigned int>> targetableCards;
    unsigned int displayIndex = 0;

    for (auto& tile : unclaimedBorders) {
        unsigned int pos = tile->getPosition();
        unsigned int count = (opponentId == 1) ? tile->getPlayerCards1().getSize() : tile->getPlayerCards2().getSize();
        for (unsigned int i = 0; i < count; ++i) {
            std::cout << displayIndex << ") Borne " << pos << ", carte " << i << std::endl;
            targetableCards.emplace_back(pos, i);
            ++displayIndex;
        }
    }

    if (targetableCards.empty()) {
        std::cout << "Aucune carte adverse à défausser." << std::endl;
        return;
    }

    // Choix utilisateur
    unsigned int choice;
    std::cout << "Choisissez la carte à défausser : ";
    std::cin >> choice;

    if (choice >= targetableCards.size()) {
        std::cout << "Choix invalide." << std::endl;
        return;
    }

    auto [pos, index] = targetableCards[choice];

    try {
        std::shared_ptr<StoneTiles> tile = gameBoard.findTileByPosition(pos);
        auto card = tile->removeCardFromPlayer(opponentId, index);
        gameBoard.getDiscardedCards().addCard(std::move(card));
        std::cout << "Carte défaussée avec succès." << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Erreur : " << e.what() << std::endl;
    }
}*/