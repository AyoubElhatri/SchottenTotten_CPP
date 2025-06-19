#include "Banshee.h"
#include "../GameBoard/GameBoard.h"
#include "../Player/Player.h"
#include "../Display/DisplayManager.h"
#include <memory>
#include "../Logic/GameLogic.h"
#include "../Cards/Cards.h"



void Banshee::getEvent(StoneTiles* /* unused */) {
    GameBoard& board = GameBoard::getInstance();
    auto& players = CGameLogic::getInstance().getPlayers();
    Player* currentPlayer = players[CGameLogic::getInstance().getCurrentPlayerIndex()].get();
    unsigned int currentPlayerId = currentPlayer->getPlayerID();
    unsigned int opponentId = 3-currentPlayerId;

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



