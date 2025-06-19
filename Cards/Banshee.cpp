#include "Banshee.h"
#include "../GameBoard/GameBoard.h"
#include "../Player/Player.h"
#include "../Display/DisplayManager.h"
#include <memory>
#include "../Logic/GameLogic.h"
#include "../Cards/Cards.h"



void Banshee::getEvent(StoneTiles* stoneTiles) {
    GameBoard& board = GameBoard::getInstance();
    auto& players = CGameLogic::getInstance().getPlayers();
    Player* currentPlayer = players[CGameLogic::getInstance().getCurrentPlayerIndex()].get();
    unsigned int currentPlayerId = currentPlayer->getPlayerID();
    unsigned int opponentId = 3-currentPlayerId;

    // Trouver les tuiles avec des cartes adverses non revendiquées
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
        DisplayManager::getInstance()->output("No opposing cards available for discard.\n");
        return;
    }

    // Affichage des tuiles disponibles
    DisplayManager::getInstance()->output("Tiles with unclaimed opposing cards :\n");
    for (const auto& tile : eligibleTiles) {
        DisplayManager::getInstance()->output(" - Tuile " + std::to_string(tile->getPosition()) + "\n");
    }

    // Choix de la tuile
    DisplayManager::getInstance()->output("Enter the clue of the tile containing the card to be discarded : ");
    unsigned int tileIndex = std::stoi(DisplayManager::getInstance()->takeInput());
    auto selectedTile = board.findTileByPosition(tileIndex);

    if (!selectedTile || selectedTile->isAlreadyClaimed()) {
        DisplayManager::getInstance()->output("Already claimed tile.\n");
        return;
    }

    Set& opponentSet = selectedTile->getPlayerCardsOnTilesByPlayerId(opponentId);
    if (opponentSet.getSize() == 0) {
        DisplayManager::getInstance()->output("No card on this tile.\n");
        return;
    }

    // Affichage des cartes adverses
    DisplayManager::getInstance()->output("Opponent cards on this tile :\n");
    opponentSet.printSet();

    // Choix de la carte à défausser
    unsigned int cardIndex;
    do {
    DisplayManager::getInstance()->output("Enter the index of the card to be discarded : ");
    unsigned int cardIndex = std::stoi(DisplayManager::getInstance()->takeInput());

    if (cardIndex >= opponentSet.getSize()) {
        DisplayManager::getInstance()->output("Invalid index.\n");
        return;
    }

    }while (cardIndex >= opponentSet.getSize());


    try {
        std::unique_ptr<Cards> removedCard = opponentSet.getCardbyIndex(cardIndex);
        if (!removedCard) {
            DisplayManager::getInstance()->output("Error: The selected card is invalid.\n");
            return;
        }

        board.getDiscardedCards().addCard(std::move(removedCard));
        DisplayManager::getInstance()->output("Card successfully discarded.\n");

    } catch (const std::exception& e) {
        DisplayManager::getInstance()->output(std::string("Error deleting card : ") + e.what() + "\n");
    }
}
