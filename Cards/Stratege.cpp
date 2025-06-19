#include "Stratege.h"
#include "../GameBoard/GameBoard.h"
#include "../Logic/GameLogic.h"
#include "../Display/DisplayManager.h"
#include <iostream>

void Stratege::getEvent(StoneTiles* ) {
    GameBoard& board = GameBoard::getInstance();
    Player* currentPlayer = CGameLogic::getInstance().getCurrentPlayer();
    unsigned int currentPlayerId = currentPlayer->getPlayerID();

    // Lister les bornes non revendiquées où le joueur a au moins une carte
    std::vector<std::shared_ptr<StoneTiles>> eligibleTiles;
    for (const auto& tile : board.getSharedTiles()) {
        if (!tile->isAlreadyClaimed()) {
            auto& playerCards = tile->getPlayerCardsOnTilesByPlayerId(currentPlayerId);
            if (playerCards.getSize() > 0) {
                eligibleTiles.push_back(tile);
            }
        }
    }

    if (eligibleTiles.empty()) {
        DisplayManager::getInstance()->output("You have no cards on an unclaimed Stone tile.\n");
        return;
    }


    DisplayManager::getInstance()->output("Unclaimed Stone tile with your cards :\n");
    for (const auto& tile : eligibleTiles) {
        DisplayManager::getInstance()->output(" - Tuile " + std::to_string(tile->getPosition()) + "\n");
    }


    DisplayManager::getInstance()->output("Enter the index of the source Stone Tile : ");
    unsigned int fromTilePos = std::stoi(DisplayManager::getInstance()->takeInput());
    auto fromTileIt = std::find_if(eligibleTiles.begin(), eligibleTiles.end(),
                                   [fromTilePos](const std::shared_ptr<StoneTiles>& t) {
                                       return t->getPosition() == fromTilePos;
                                   });
    if (fromTileIt == eligibleTiles.end()) {
        DisplayManager::getInstance()->output("Invalid Stone tile.\n");
        return;
    }
    auto fromTile = *fromTileIt;


    auto& fromCards = fromTile->getPlayerCardsOnTilesByPlayerId(currentPlayerId);
    DisplayManager::getInstance()->output("Available cards on the stone tile " + std::to_string(fromTilePos) + " :\n");
    fromCards.printSet();

    // Choisir la carte à déplacer ou défausser
    DisplayManager::getInstance()->output("Enter the index of the card to move or to discard away.");
    unsigned int cardIndex = std::stoi(DisplayManager::getInstance()->takeInput());
    if (cardIndex >= fromCards.getSize()) {
        DisplayManager::getInstance()->output("Invalid card Index \n");
        return;
    }

    std::unique_ptr<Cards> chosenCard = fromCards.getCardbyIndex(cardIndex);

    // Choisir entre déplacer ou défausser
    DisplayManager::getInstance()->output("Do you want to move this card to another tile (1) or discard it away (2)?");
    std::string choice = DisplayManager::getInstance()->takeInput();

    if (choice == "1") {

        std::vector<std::shared_ptr<StoneTiles>> destTiles;
        for (const auto& tile : board.getSharedTiles()) {
            if (!tile->isAlreadyClaimed() && tile->getPosition() != fromTilePos) {
                destTiles.push_back(tile);
            }
        }

        if (destTiles.empty()) {
            DisplayManager::getInstance()->output("No valid stone tile to move the card.\n");
            fromCards.addCard(std::move(chosenCard));
            return;
        }

        DisplayManager::getInstance()->output("Possible stone tiles to move the card: \n");
        for (const auto& tile : destTiles) {
            DisplayManager::getInstance()->output(" - StoneTile " + std::to_string(tile->getPosition()) + "\n");
        }

        DisplayManager::getInstance()->output("Enter the index of the stone tile destination: ");
        unsigned int toTilePos = std::stoi(DisplayManager::getInstance()->takeInput());

        auto toTileIt = std::find_if(destTiles.begin(), destTiles.end(),
                                     [toTilePos](const std::shared_ptr<StoneTiles>& t) {
                                         return t->getPosition() == toTilePos;
                                     });
        if (toTileIt == destTiles.end()) {
            DisplayManager::getInstance()->output("Invalid StoneTile destination. \n");

            fromCards.addCard(std::move(chosenCard));
            return;
        }
        auto toTile = *toTileIt;


        auto& toCards = toTile->getPlayerCardsOnTilesByPlayerId(currentPlayerId);
        if (toCards.getSize() >= Rules::getInstance()->getNumberMaxOfCardsPerTiles()) {
            DisplayManager::getInstance()->output("Stone tile destination is already full. \n");
            fromCards.addCard(std::move(chosenCard));
            return;
        }

        toCards.addCard(std::move(chosenCard));
        DisplayManager::getInstance()->output("Card moved successfully\n");

    } else if (choice == "2") {

        board.getDiscardedCards().addCard(std::move(chosenCard));
        DisplayManager::getInstance()->output("Card discarded successfully.\n");
    } else {

        DisplayManager::getInstance()->output("Invalid Choice. \n");
        fromCards.addCard(std::move(chosenCard));
    }
}