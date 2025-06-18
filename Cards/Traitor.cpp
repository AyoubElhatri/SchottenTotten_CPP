#include "Traitor.h"
#include "../GameBoard/GameBoard.h"
#include "../Logic2/GameLogic2.h"
#include "../Rules/Rules.h"
#include "../Player/Player.h"
#include "../Cards/ClanCards.h"
#include "../Display/DisplayManager.h"
#include <iostream>
#include <memory>

void Traitor::getEvent(StoneTiles* ) {
    GameBoard& board = GameBoard::getInstance();
    Player* currentPlayer = CGameLogic::getInstance().getPlayers()[CGameLogic::getInstance().getCurrentPlayerIndex()].get();
    unsigned int currentPlayerId = currentPlayer->getPlayerID();
    unsigned int opponentId = 3-currentPlayerId;

    // Étape 1 : Récupérer les tuiles non revendiquées avec cartes de l'adversaire
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
        DisplayManager::getInstance()->output("Aucune carte adverse disponible à voler.\n");
        return;
    }

    // Afficher les tuiles admissibles
    DisplayManager::getInstance()->output("Tuiles non revendiquées avec des cartes adverses :\n");
    for (const auto& tile : eligibleTiles) {
        DisplayManager::getInstance()->output(" - Tuile " + std::to_string(tile->getPosition()) + "\n");
    }

    // Choix de la tuile source
    DisplayManager::getInstance()->output("Entrez l'indice de la tuile d'où voler une carte : ");
    unsigned int fromTileIndex = std::stoi(DisplayManager::getInstance()->takeInput());
    auto fromTile = board.findTileByPosition(fromTileIndex);

    if (!fromTile || fromTile->isAlreadyClaimed()) {
        DisplayManager::getInstance()->output("Tuile invalide ou déjà revendiquée.\n");
        return;
    }

    Set& opponentSet = fromTile->getPlayerCardsOnTilesByPlayerId(opponentId);
    if (opponentSet.getSize() == 0) {
        DisplayManager::getInstance()->output("Pas de carte à voler sur cette tuile.\n");
        return;
    }

    DisplayManager::getInstance()->output("Cartes disponibles à voler :\n");
    opponentSet.printSet();

    DisplayManager::getInstance()->output("Entrez l'index de la carte à voler : ");
    unsigned int cardIndex = std::stoi(DisplayManager::getInstance()->takeInput());

    if (cardIndex >= opponentSet.getSize()) {
        DisplayManager::getInstance()->output("Index invalide.\n");
        return;
    }

    // Récupération et suppression de la carte
    std::unique_ptr<Cards> stolenCard = opponentSet.getCardbyIndex(cardIndex);

    // Choix de la tuile destination
    DisplayManager::getInstance()->output("Entrez l'indice de la tuile où poser la carte volée : ");
    unsigned int toTileIndex = std::stoi(DisplayManager::getInstance()->takeInput());

    auto toTile = board.findTileByPosition(toTileIndex);
    if (!toTile || toTile->isAlreadyClaimed()) {
        DisplayManager::getInstance()->output("Tuile invalide ou déjà revendiquée.\n");
        return;
    }

    Set& playerSet = toTile->getPlayerCardsOnTilesByPlayerId(currentPlayerId);
    unsigned int maxCardsPerTile = Rules::getInstance()->getNumberMaxOfCardsPerTiles();

    if (playerSet.getSize() >= maxCardsPerTile) {
        DisplayManager::getInstance()->output("Vous avez déjà le nombre maximum de cartes sur cette tuile.\n");
        return;
    }

    playerSet.addCard(std::move(stolenCard));
    DisplayManager::getInstance()->output("Carte volée avec succès et placée sur la tuile " + std::to_string(toTileIndex) + "\n");
}