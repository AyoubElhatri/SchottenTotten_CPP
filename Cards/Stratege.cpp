#include "Stratege.h"
#include "../GameBoard/GameBoard.h"
#include <iostream>
#include <vector>
#include <tuple>

#include "../Logic/GameLogic.h"
using namespace std;


void Stratege::getEvent(StoneTiles* stoneTiles) {
    GameBoard* board = &GameBoard::getInstance();
    Player* currentPlayer = GameLogic::getInstance().getCurrentPlayer();



 DisplayManager::getInstance()->output("\nChoisissez le numéro de la borne d'où prendre la carte (0-" +
                   std::to_string(board->getBoardSize() - 1) + ") :");

    int sourceStoneIndex;
    while (true) {
        try {
            sourceStoneIndex = std::stoi(DisplayManager::getInstance()->takeInput());
            if (sourceStoneIndex >= 0 && sourceStoneIndex < board->getBoardSize()) {
                auto& sourceTile = board->getSharedTiles()[sourceStoneIndex];
                if (!sourceTile->isAlreadyClaimed()) {
                    break;
                }
            }
            DisplayManager::getInstance()->output("Borne invalide ou déjà revendiquée. Réessayez :");
        } catch (...) {
            DisplayManager::getInstance()->output("Entrée invalide. Réessayez :");
        }
    }

    // 3. Afficher et choisir la carte à déplacer
    auto& sourceTile = board->getSharedTiles()[sourceStoneIndex];
    DisplayManager::getInstance()->output("\nCartes sur cette borne :");
    // Afficher les cartes du joueur sur cette borne
    // Note: Adapter selon votre méthode d'affichage des cartes sur une borne

    DisplayManager::getInstance()->output("\nChoisissez l'index de la carte à déplacer :");
    int cardIndex;
    while (true) {
        try {
            cardIndex = std::stoi(DisplayManager::getInstance()->takeInput());
            // Vérifier si l'index est valide selon votre structure
            if (cardIndex >= 0 /* && cardIndex < nombreDeCartesDisponibles */) {
                break;
            }
            DisplayManager::getInstance()->output("Index invalide. Réessayez :");
        } catch (...) {
            DisplayManager::getInstance()->output("Entrée invalide. Réessayez :");
        }
    }

    // 4. Choisir l'action
    DisplayManager::getInstance()->output("\n1. Déplacer vers une autre borne");
    DisplayManager::getInstance()->output("2. Défausser la carte");
        int choice = std::stoi(DisplayManager::getInstance()->takeInput());

    if (choice == 1) {
        // Déplacer vers une autre borne
        DisplayManager::getInstance()->output("\nChoisissez la borne de destination (0-" +
                       std::to_string(board->getBoardSize() - 1) + ") :");

        int destStoneIndex;
        while (true) {
            try {
                destStoneIndex = std::stoi(DisplayManager::getInstance()->takeInput());
                if (destStoneIndex >= 0 && destStoneIndex < board->getBoardSize() &&
                    destStoneIndex != sourceStoneIndex) {
                    auto& destTile = board->getSharedTiles()[destStoneIndex];
                    if (!destTile->isAlreadyClaimed()) {
                        // Effectuer le déplacement
                        // Note: Implémenter la logique de déplacement selon votre structure
                        // Par exemple :
                        destTile->addCardToPlayer(currentPlayer->getPlayerID(), cardToMove, sourceTile);
                        DisplayManager::getInstance()->output("Carte déplacée avec succès !");
                        break;
                    }
                }
                DisplayManager::getInstance()->output("Borne invalide. Réessayez :");
            } catch (...) {
                DisplayManager::getInstance()->output("Entrée invalide. Réessayez :");
            }
        }
    } else {
        // Défausser la carte
        // Note: Implémenter la logique de défausse selon votre structure
        // Par exemple : sourceTile->removeCard(cardIndex);
        DisplayManager::getInstance()->output("Carte défaussée avec succès !");
    }

    // Attendre que le joueur appuie sur Entrée
    DisplayManager::getInstance()->output("\nAppuyez sur Entrée pour continuer...");
    std::cin.get();
}
