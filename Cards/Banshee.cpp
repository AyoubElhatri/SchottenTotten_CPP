#include "Banshee.h"
#include "../GameBoard/GameBoard.h"
#include "../Rules/Rules.h"
#include "../Player/Player.h"
#include "../Display/DisplayManager.h"
#include <iostream>
#include <memory>

/*void Banshee::getEvent() {
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


/*void Banshee::getEvent(StoneTiles* /* unused ) {
    GameBoard& board = GameBoard::getInstance();
    auto& players = GameLogic::getInstance().getPlayers();
    Player* currentPlayer = players[GameLogic::getInstance().getCurrentPlayerIndex()].get();
    unsigned int currentPlayerId = currentPlayer->getPlayerID();
    unsigned int opponentId = (currentPlayerId == 1) ? 2 : 1;

    // Étape 1 : Rechercher les tuiles non revendiquées contenant des cartes adverses
    std::vector<std::shared_ptr<StoneTiles>> eligibleTiles;
    for (const auto& tile : board.getSharedTiles()) {
        if (!tile->isAlreadyClaimed()) {
            Set& opponentSet = tile->getPlayerCardsOnTilesByPlayerId(opponentId);
            if (opponentSet.getSize() > 0) {
                eligibleTiles.push_back(tile);
            }
        }
    }

    if (eligibleTiles.empty()) {
        DisplayManager::getInstance()->output("Aucune carte adverse disponible à défausser.\n");
        return;
    }

    DisplayManager::getInstance()->output("Tuiles avec cartes adverses non revendiquées :\n");
    for (const auto& tile : eligibleTiles) {
        DisplayManager::getInstance()->output(" - Tuile " + std::to_string(tile->getPosition()) + "\n");
    }

    // Étape 2 : Choisir une tuile
    DisplayManager::getInstance()->output("Entrez l’indice de la tuile contenant la carte à défausser : ");
    unsigned int tileIndex = std::stoi(DisplayManager::getInstance()->takeInput());
    auto selectedTile = board.findTileByPosition(tileIndex);

    if (!selectedTile || selectedTile->isAlreadyClaimed()) {
        DisplayManager::getInstance()->output("Tuile invalide ou déjà revendiquée.\n");
        return;
    }

    Set& opponentSet = selectedTile->getPlayerCardsOnTilesByPlayerId(opponentId);
    if (opponentSet.getSize() == 0) {
        DisplayManager::getInstance()->output("Pas de carte sur cette tuile.\n");
        return;
    }

    DisplayManager::getInstance()->output("Cartes adverses sur cette tuile :\n");
    opponentSet.printSet();

    // Étape 3 : Choisir la carte à défausser
    DisplayManager::getInstance()->output("Entrez l’index de la carte à défausser : ");
    unsigned int cardIndex = std::stoi(DisplayManager::getInstance()->takeInput());

    if (cardIndex >= opponentSet.getSize()) {
        DisplayManager::getInstance()->output("Index invalide.\n");
        return;
    }

    // Défausse la carte
    std::unique_ptr<Cards> removedCard = opponentSet.getCardbyIndex(cardIndex);
    board.getDiscardedCards().addCard(std::move(removedCard));

    DisplayManager::getInstance()->output("Carte défaussée avec succès.\n");
}*/

#include "Banshee.h"
#include "../GameBoard/GameBoard.h"
#include "../Logic/GameLogic.h"
#include "../Display/DisplayManager.h"
#include "../Player/Player.h"
#include "../Cards/Cards.h"

#include <iostream>
#include <memory>

void Banshee::getEvent(StoneTiles* /* unused */) {
    GameBoard& board = GameBoard::getInstance();
    auto& players = CGameLogic::getInstance().getPlayers();
    Player* currentPlayer = players[CGameLogic::getInstance().getCurrentPlayerIndex()].get();
    unsigned int currentPlayerId = currentPlayer->getPlayerID();
    unsigned int opponentId = (currentPlayerId == 1) ? 2 : 1;

    // Étape 1 : Trouver les tuiles avec des cartes adverses non revendiquées
    std::vector<std::shared_ptr<StoneTiles>> eligibleTiles;
    for (const auto& tile : board.getSharedTiles()) {
        if (!tile->isAlreadyClaimed()) {
            Set& opponentSet = tile->getPlayerCardsOnTilesByPlayerId(opponentId);
            if (opponentSet.getSize() > 0) {
                eligibleTiles.push_back(tile);
            }
        }
    }

    if (eligibleTiles.empty()) {
        DisplayManager::getInstance()->output("Aucune carte adverse disponible à défausser.\n");
        return;
    }

    // Affichage des tuiles disponibles
    DisplayManager::getInstance()->output("Tuiles avec cartes adverses non revendiquées :\n");
    for (const auto& tile : eligibleTiles) {
        DisplayManager::getInstance()->output(" - Tuile " + std::to_string(tile->getPosition()) + "\n");
    }

    // Étape 2 : Choix de la tuile
    DisplayManager::getInstance()->output("Entrez l’indice de la tuile contenant la carte à défausser : ");
    unsigned int tileIndex = std::stoi(DisplayManager::getInstance()->takeInput());
    auto selectedTile = board.findTileByPosition(tileIndex);

    if (!selectedTile || selectedTile->isAlreadyClaimed()) {
        DisplayManager::getInstance()->output("Tuile invalide ou déjà revendiquée.\n");
        return;
    }

    Set& opponentSet = selectedTile->getPlayerCardsOnTilesByPlayerId(opponentId);
    if (opponentSet.getSize() == 0) {
        DisplayManager::getInstance()->output("Pas de carte sur cette tuile.\n");
        return;
    }

    // Affichage des cartes adverses
    DisplayManager::getInstance()->output("Cartes adverses sur cette tuile :\n");
    opponentSet.printSet();

    // Étape 3 : Choix de la carte à défausser
    DisplayManager::getInstance()->output("Entrez l’index de la carte à défausser : ");
    unsigned int cardIndex = std::stoi(DisplayManager::getInstance()->takeInput());

    if (cardIndex >= opponentSet.getSize()) {
        DisplayManager::getInstance()->output("Index invalide.\n");
        return;
    }

    // Étape 4 : Suppression sécurisée de la carte
    try {
        std::unique_ptr<Cards> removedCard = opponentSet.getCardbyIndex(cardIndex);
        if (!removedCard) {
            DisplayManager::getInstance()->output("Erreur : la carte sélectionnée est invalide.\n");
            return;
        }

        board.getDiscardedCards().addCard(std::move(removedCard));
        DisplayManager::getInstance()->output("Carte défaussée avec succès.\n");

    } catch (const std::exception& e) {
        DisplayManager::getInstance()->output(std::string("Erreur lors de la suppression de la carte : ") + e.what() + "\n");
    }
}



