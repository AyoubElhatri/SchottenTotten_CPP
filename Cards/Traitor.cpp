#include "Traitor.h"
#include "../GameBoard/GameBoard.h"
#include "../Logic/GameLogic.h"
#include "../Rules/Rules.h"
#include "../Player/Player.h"
#include "../Cards/ClanCards.h"
#include <iostream>
#include <memory>

/*void Traitor::getEvent(StoneTiles* ) {
    GameBoard& board = GameBoard::getInstance();
    Player* currentPlayer = GameLogic::getInstance().getCurrentPlayer();
    unsigned int currentPlayerId = currentPlayer->getPlayerID();
    unsigned int opponentId = (currentPlayerId == 1) ? 2 : 1;

    // Affichage des tuiles non revendiquées
    std::vector<std::shared_ptr<StoneTiles>> eligibleTiles;
    for (const auto& tile : board.getSharedTiles()) {
        if (!tile->isAlreadyClaimed() &&
            tile->getPlayerCards2().getSize() > 0 &&
            currentPlayerId == 1) {
            eligibleTiles.push_back(tile);
        } else if (!tile->isAlreadyClaimed() &&
                   tile->getPlayerCards1().getSize() > 0 &&
                   currentPlayerId == 2) {
            eligibleTiles.push_back(tile);
        }
    }

    if (eligibleTiles.empty()) {
        DisplayManager::getInstance()->output("Aucune carte adverse disponible à voler.\n");
        return;
    }

    DisplayManager::getInstance()->output("Voici les tuiles non revendiquées avec des cartes adverses :\n");
    for (const auto& tile : eligibleTiles) {
        DisplayManager::getInstance()->output("Tuile " + std::to_string(tile->getPosition()) + "\n");
    }

    // Choisir la tuile source
    DisplayManager::getInstance()->output("Entrez l'indice de la tuile dont vous voulez voler une carte : ");
    unsigned int fromTileIndex = std::stoi(DisplayManager::getInstance()->takeInput());
    auto fromTile = board.findTileByPosition(fromTileIndex);

    if (!fromTile || fromTile->isAlreadyClaimed()) {
        DisplayManager::getInstance()->output("Tuile invalide ou déjà revendiquée.\n");
        return;
    }

    Set& opponentSet = (currentPlayerId == 1) ? fromTile->getPlayerCards2() : fromTile->getPlayerCards1();
    if (opponentSet.getSize() == 0) {
        DisplayManager::getInstance()->output("Aucune carte à voler sur cette tuile.\n");
        return;
    }

    DisplayManager::getInstance()->output("Cartes adverses sur cette tuile :\n");
    opponentSet.printSet();

    DisplayManager::getInstance()->output("Entrez l'index de la carte que vous voulez voler : ");
    unsigned int cardIndex = std::stoi(DisplayManager::getInstance()->takeInput());

    if (cardIndex >= opponentSet.getSize()) {
        DisplayManager::getInstance()->output("Index invalide.\n");
        return;
    }

    std::unique_ptr<Cards> stolenCard = opponentSet.getCardbyIndex(cardIndex);

    // Choisir une tuile de destination
    DisplayManager::getInstance()->output("Entrez l'indice de la tuile sur laquelle placer la carte volée : ");
    unsigned int toTileIndex = std::stoi(DisplayManager::getInstance()->takeInput());

    auto toTile = board.findTileByPosition(toTileIndex);

    if (!toTile || toTile->isAlreadyClaimed()) {
        DisplayManager::getInstance()->output("Tuile invalide ou déjà revendiquée.\n");
        return;
    }

    Set& playerSet = (currentPlayerId == 1) ? toTile->getPlayerCards1() : toTile->getPlayerCards2();
    unsigned int maxPerTile = Rules::getInstance()->getNumberMaxOfCardsPerTiles();

    if (playerSet.getSize() >= maxPerTile) {
        DisplayManager::getInstance()->output("Vous avez déjà atteint le nombre maximum de cartes sur cette tuile.\n");
        return;
    }

    playerSet.addCard(std::move(stolenCard));
    DisplayManager::getInstance()->output("Carte volée avec succès et posée sur la tuile " + std::to_string(toTileIndex) + "\n");
}*/