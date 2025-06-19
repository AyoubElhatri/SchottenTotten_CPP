#include "Traitor.h"
#include "../GameBoard/GameBoard.h"
#include "../Logic/GameLogic.h"
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

    //Récupérer les tuiles non revendiquées avec cartes de l'adversaire
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
        DisplayManager::getInstance()->output("No opponent card is available to steal.\n");
        return;
    }


    DisplayManager::getInstance()->output("Unclaimed Tiles with opponent cards: \n");
    for (const auto& tile : eligibleTiles) {
        DisplayManager::getInstance()->output(" - StoneTile " + std::to_string(tile->getPosition()) + "\n");
    }


    DisplayManager::getInstance()->output("Enter the index of stone tile from where to steal the card: ");
    unsigned int fromTileIndex = std::stoi(DisplayManager::getInstance()->takeInput());
    auto fromTile = board.findTileByPosition(fromTileIndex);

    if (!fromTile || fromTile->isAlreadyClaimed()) {
        DisplayManager::getInstance()->output("Invalid stone tile or already claimed.\n");
        return;
    }

    Set& opponentSet = fromTile->getPlayerCardsOnTilesByPlayerId(opponentId);
    if (opponentSet.getSize() == 0) {
        DisplayManager::getInstance()->output("No cards to steal on this Stone tile.\n");
        return;
    }

    DisplayManager::getInstance()->output("Available cards to steal :\n");
    opponentSet.printSet();

    DisplayManager::getInstance()->output("Enter the index of the card to steal : ");
    unsigned int cardIndex = std::stoi(DisplayManager::getInstance()->takeInput());

    if (cardIndex >= opponentSet.getSize()) {
        DisplayManager::getInstance()->output("Invalid index.\n");
        return;
    }


    std::unique_ptr<Cards> stolenCard = opponentSet.getCardbyIndex(cardIndex);


    DisplayManager::getInstance()->output("Enter the index of the stone tile on which you wish to put the card : ");
    unsigned int toTileIndex = std::stoi(DisplayManager::getInstance()->takeInput());

    auto toTile = board.findTileByPosition(toTileIndex);
    if (!toTile || toTile->isAlreadyClaimed()) {
        DisplayManager::getInstance()->output("Invalid stone tile or already claimed.\n");
        return;
    }

    Set& playerSet = toTile->getPlayerCardsOnTilesByPlayerId(currentPlayerId);
    unsigned int maxCardsPerTile = Rules::getInstance()->getNumberMaxOfCardsPerTiles();

    if (playerSet.getSize() >= maxCardsPerTile) {
        DisplayManager::getInstance()->output("You already have the maximum number of cards on this stone tile.\n");
        return;
    }

    playerSet.addCard(std::move(stolenCard));
    DisplayManager::getInstance()->output("Card stolen and placed on the stole tile successfully of index: " + std::to_string(toTileIndex) + "\n");
}