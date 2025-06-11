#include "Traitor.h"
#include "../GameBoard.h"
#include"../Player/Player.h"
#include <iostream>

void Traitor::getEvent() {
    GameBoard& gameBoard = GameBoard::getInstance();
    unsigned int currentPlayerId = getPlayerID(); //
    unsigned int opponentId = (currentPlayerId == 1) ? 2 : 1;

    std::cout << "[Traitor] Activation de l'effet Traître." << std::endl;

    std::vector<std::shared_ptr<StoneTiles>> unclaimedBorders;

    // Récupérer toutes les bornes non revendiquées
    for (auto& tile : gameBoard.getSharedTiles()) {
        if (!tile->isAlreadyClaimed()) {
            unclaimedBorders.push_back(tile);
        }
    }

    if (unclaimedBorders.empty()) {
        std::cout << "Aucune borne non revendiquée disponible." << std::endl;
        return;
    }

    // Récupérer les cartes adverses posées sur bornes non revendiquées
    std::vector<std::tuple<unsigned int, unsigned int>> adversaryCards; // (bornePos, cardIndex)
    unsigned int index = 0;
    std::cout << "Cartes adverses disponibles :" << std::endl;
    for (auto& tile : unclaimedBorders) {
        unsigned int pos = tile->getPosition();
        unsigned int nb = (opponentId == 1) ? tile->getPlayerCards1().getSize() : tile->getPlayerCards2().getSize();
        for (unsigned int i = 0; i < nb; ++i) {
            std::cout << index << ") Borne " << pos << ", carte " << i << std::endl;
            adversaryCards.emplace_back(pos, i);
            ++index;
        }
    }

    if (adversaryCards.empty()) {
        std::cout << "Aucune carte adverse à déplacer." << std::endl;
        return;
    }

    // Choix utilisateur
    unsigned int choice;
    std::cout << "Choisissez la carte à voler : ";
    std::cin >> choice;
    if (choice >= adversaryCards.size()) {
        std::cout << "Choix invalide." << std::endl;
        return;
    }

    auto [fromPos, cardIndex] = adversaryCards[choice];

    // Afficher les bornes non revendiquées disponibles
    std::cout << "Bornes valides pour placer la carte : " << std::endl;
    for (unsigned int i = 0; i < unclaimedBorders.size(); ++i) {
        std::cout << i << ") Borne " << unclaimedBorders[i]->getPosition() << std::endl;
    }

    unsigned int toChoice;
    std::cout << "Choisissez la borne de destination : ";
    std::cin >> toChoice;

    if (toChoice >= unclaimedBorders.size()) {
        std::cout << "Choix invalide." << std::endl;
        return;
    }

    unsigned int toPos = unclaimedBorders[toChoice]->getPosition();

    // Retirer la carte et la réinsérer sur une borne
    try {
        std::shared_ptr<StoneTiles> fromTile = gameBoard.findTileByPosition(fromPos);
        std::shared_ptr<StoneTiles> toTile = gameBoard.findTileByPosition(toPos);

        auto card = fromTile->removeCardFromPlayer(opponentId, cardIndex);
        toTile->addCardToPlayer(currentPlayerId, std::move(card));

        std::cout << "Carte déplacée avec succès." << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Erreur : " << e.what() << std::endl;
    }
}