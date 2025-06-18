#include "Stratege.h"
#include "../GameBoard/GameBoard.h"
#include "../Logic2/GameLogic2.h"
#include "../Display/DisplayManager.h"
#include <iostream>

void Stratege::getEvent(StoneTiles* /* unused */) {
    GameBoard& board = GameBoard::getInstance();
    Player* currentPlayer = CGameLogic::getInstance().getCurrentPlayer();
    unsigned int currentPlayerId = currentPlayer->getPlayerID();

    // Étape 1 : Lister les bornes non revendiquées où le joueur a au moins une carte
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
        DisplayManager::getInstance()->output("Vous n'avez aucune carte sur une borne non revendiquée.\n");
        return;
    }

    // Afficher les bornes admissibles
    DisplayManager::getInstance()->output("Bornes non revendiquées avec vos cartes :\n");
    for (const auto& tile : eligibleTiles) {
        DisplayManager::getInstance()->output(" - Tuile " + std::to_string(tile->getPosition()) + "\n");
    }

    // Choisir la borne source
    DisplayManager::getInstance()->output("Entrez l'indice de la tuile source : ");
    unsigned int fromTilePos = std::stoi(DisplayManager::getInstance()->takeInput());
    auto fromTileIt = std::find_if(eligibleTiles.begin(), eligibleTiles.end(),
                                   [fromTilePos](const std::shared_ptr<StoneTiles>& t) {
                                       return t->getPosition() == fromTilePos;
                                   });
    if (fromTileIt == eligibleTiles.end()) {
        DisplayManager::getInstance()->output("Tuile invalide.\n");
        return;
    }
    auto fromTile = *fromTileIt;

    // Afficher les cartes du joueur sur cette tuile
    auto& fromCards = fromTile->getPlayerCardsOnTilesByPlayerId(currentPlayerId);
    DisplayManager::getInstance()->output("Cartes disponibles sur la tuile " + std::to_string(fromTilePos) + " :\n");
    fromCards.printSet();

    // Choisir la carte à déplacer ou défausser
    DisplayManager::getInstance()->output("Entrez l'index de la carte à déplacer ou défausser : ");
    unsigned int cardIndex = std::stoi(DisplayManager::getInstance()->takeInput());
    if (cardIndex >= fromCards.getSize()) {
        DisplayManager::getInstance()->output("Index de carte invalide.\n");
        return;
    }

    std::unique_ptr<Cards> chosenCard = fromCards.getCardbyIndex(cardIndex);

    // Choisir entre déplacer ou défausser
    DisplayManager::getInstance()->output("Voulez-vous déplacer cette carte sur une autre tuile (1) ou la défausser (2) ? ");
    std::string choice = DisplayManager::getInstance()->takeInput();

    if (choice == "1") {
        // Lister les bornes non revendiquées (sauf celle source) pour déplacer la carte
        std::vector<std::shared_ptr<StoneTiles>> destTiles;
        for (const auto& tile : board.getSharedTiles()) {
            if (!tile->isAlreadyClaimed() && tile->getPosition() != fromTilePos) {
                destTiles.push_back(tile);
            }
        }

        if (destTiles.empty()) {
            DisplayManager::getInstance()->output("Aucune tuile valide pour déplacer la carte.\n");
            // Option : remettre la carte dans la tuile d'origine pour ne pas la perdre
            fromCards.addCard(std::move(chosenCard));
            return;
        }

        DisplayManager::getInstance()->output("Bornes possibles pour déplacer la carte :\n");
        for (const auto& tile : destTiles) {
            DisplayManager::getInstance()->output(" - Tuile " + std::to_string(tile->getPosition()) + "\n");
        }

        DisplayManager::getInstance()->output("Entrez l'indice de la tuile destination : ");
        unsigned int toTilePos = std::stoi(DisplayManager::getInstance()->takeInput());

        auto toTileIt = std::find_if(destTiles.begin(), destTiles.end(),
                                     [toTilePos](const std::shared_ptr<StoneTiles>& t) {
                                         return t->getPosition() == toTilePos;
                                     });
        if (toTileIt == destTiles.end()) {
            DisplayManager::getInstance()->output("Tuile destination invalide.\n");
            // Remettre la carte sur la tuile source
            fromCards.addCard(std::move(chosenCard));
            return;
        }
        auto toTile = *toTileIt;

        // Ajouter la carte sur la tuile destination
        auto& toCards = toTile->getPlayerCardsOnTilesByPlayerId(currentPlayerId);
        if (toCards.getSize() >= Rules::getInstance()->getNumberMaxOfCardsPerTiles()) {
            DisplayManager::getInstance()->output("La tuile destination est déjà pleine.\n");
            fromCards.addCard(std::move(chosenCard));
            return;
        }

        toCards.addCard(std::move(chosenCard));
        DisplayManager::getInstance()->output("Carte déplacée avec succès.\n");

    } else if (choice == "2") {
        // Défausser la carte face visible à côté de la pioche
        board.getDiscardedCards().addCard(std::move(chosenCard));
        DisplayManager::getInstance()->output("Carte défaussée avec succès.\n");
    } else {
        // Mauvais choix, remettre la carte dans la tuile d'origine
        DisplayManager::getInstance()->output("Choix invalide.\n");
        fromCards.addCard(std::move(chosenCard));
    }
}