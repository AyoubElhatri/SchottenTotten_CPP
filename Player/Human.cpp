#include"Human.h"
#include "../GameBoard/GameBoard.h"
#include "../Cards/EliteTroopsCards.h"
#include "../Cards/CombatModeCards.h"
#include "../Cards/RusesCards.h"
#include "../Logic/GameLogic.h"

void Human::playCard() {
    GameBoard& board = GameBoard::getInstance();
    
    DisplayManager::getInstance()->output("\nIt's Player " + std::to_string(getPlayerID()) + "'s turn\n");
    getPlayerDeck().printSet();

    int cardIndex = -1;
    int tileIndex = -1;

    // Sélection de la carte
    DisplayManager::getInstance()->output("Choose a card index from your hand (0 to " +
                                          std::to_string(getPlayerDeck().getSize() - 1) + "): ");
    try {
        cardIndex = std::stoi(DisplayManager::getInstance()->takeInput());
    } catch (...) {
        throw std::runtime_error("Invalid card index input");
    }

    if (cardIndex < 0 || cardIndex >= (int)getPlayerDeck().getSize()) {
        throw std::runtime_error("Invalid card index range");
    }

    // Récupération de la carte sélectionnée
     Cards* selectedCard = getPlayerDeck().getCardAt(cardIndex);

    // Vérification du type de carte
    if (auto eliteTroop = dynamic_cast<EliteTroopsCards*>(selectedCard)) {
        // Traitement comme une ClanCards normale
        DisplayManager::getInstance()->output("Choose a tile index to play on (0 to " +
                                              std::to_string(board.getBoardSize() - 1) + "): ");
        try {
            tileIndex = std::stoi(DisplayManager::getInstance()->takeInput());
        } catch (...) {
            throw std::runtime_error("Invalid tile index input");
        }

        if (tileIndex < 0 || tileIndex >= board.getBoardSize()) {
            throw std::runtime_error("Invalid tile index range");
        }

        board.placeCardOnTileByIndexOfTheTile(tileIndex, *selectedCard, getPlayerID());
    }
    else if (auto combatMode = dynamic_cast<CombatModeCards*>(selectedCard)) {
        // Traitement des cartes de mode de combat
        DisplayManager::getInstance()->output("Choose a tile index to apply combat mode (0 to " +
                                              std::to_string(board.getBoardSize() - 1) + "): ");
        try {
            tileIndex = std::stoi(DisplayManager::getInstance()->takeInput());
        } catch (...) {
            throw std::runtime_error("Invalid tile index input");
        }

        if (tileIndex < 0 || tileIndex >= board.getBoardSize()) {
            throw std::runtime_error("Invalid tile index range");
        }

        auto& tile = board.getSharedTiles()[tileIndex];
        combatMode->getEvent(tile.get()); // Activation de l'effet sur la tuile
        getPlayerDeck().moveCard(cardIndex, tile->getCombatModeCards());
    }
    else if (auto ruse = dynamic_cast<RusesCards*>(selectedCard)) {
        // Traitement des cartes de ruse
        ruse->getEvent(nullptr); // Activation de l'effet
        getPlayerDeck().moveCard(cardIndex, board.getDiscardedCards());
    }
    else {
        // Cas d'une ClanCards normale
        DisplayManager::getInstance()->output("Choose a tile index to play on (0 to " +
                                              std::to_string(board.getBoardSize() - 1) + "): ");
        try {
            tileIndex = std::stoi(DisplayManager::getInstance()->takeInput());
        } catch (...) {
            throw std::runtime_error("Invalid tile index input");
        }

        if (tileIndex < 0 || tileIndex >= board.getBoardSize()) {
            throw std::runtime_error("Invalid tile index range");
        }

        board.placeCardOnTileByIndexOfTheTile(tileIndex, *selectedCard, getPlayerID());
    }
    if (board.getSharedTiles()[tileIndex]->getPlayerCardsOnTilesByPlayerId(getPlayerID()).getSize()==board.getSharedTiles()[tileIndex]->getNbOfPlayableCards() && board.getSharedTiles()[tileIndex]->getFirstPlayerToFillTheStoneTile()==nullptr) {
        board.getSharedTiles()[tileIndex]->setFirstPlayerToFillTheStoneTile(this);
    }
    board.printBoard();

    // Piocher une carte si possible
    bool canDrawClan = board.getRemainingClanCards().getSize() > 0;
    bool canDrawTactical = board.getRemainingTacticalCards().getSize() > 0;

    if (canDrawClan || canDrawTactical) {
        DisplayManager::getInstance()->output("\nChoisissez le type de carte à piocher :");
        if (canDrawClan) DisplayManager::getInstance()->output("1. Carte Clan");
        if (canDrawTactical) DisplayManager::getInstance()->output("2. Carte Tactique");
        
        string choice;
        do {
            DisplayManager::getInstance()->output("Votre choix (1 ou 2) : ");
            choice = DisplayManager::getInstance()->takeInput();
            
            if (choice == "1" && canDrawClan) {
                drawClanCards(1);
                break;
            }
            else if (choice == "2" && canDrawTactical) {
                drawTacticalCards(1);
                break;
            }
            else {
                DisplayManager::getInstance()->output("Choix invalide. Veuillez réessayer.");
            }
        } while (true);
    }

    else {
        DisplayManager::getInstance()->output("\nAucune carte disponible à piocher.");
    }
    DisplayManager::getInstance()->output("\nVotre main actuelle :");
    getPlayerDeck().printSet();




}

void Human::playTurn() {
    try {
        DisplayManager::getInstance()->output("\nC'est le tour du Joueur " + std::to_string(getPlayerID()));
        DisplayManager::getInstance()->output("\nQue souhaitez-vous faire ?");
        DisplayManager::getInstance()->output("1. Jouer une carte");
        DisplayManager::getInstance()->output("2. Réclamer une balise");
        
        string choice;
        do {
            DisplayManager::getInstance()->output("\nVotre choix (1 ou 2) : ");
            choice = DisplayManager::getInstance()->takeInput();
            
            if (choice == "1") {
                playCard();
                break;
            }
            else if (choice == "2") {
                GameBoard& board = GameBoard::getInstance();
                DisplayManager::getInstance()->output("Choisissez l'index de la balise à réclamer (0 à " + 
                    std::to_string(board.getBoardSize() - 1) + ") : ");
                
                try {
                    int tileIndex = std::stoi(DisplayManager::getInstance()->takeInput());
                    if (tileIndex >= 0 && tileIndex < board.getBoardSize()) {

                        board.getSharedTiles()[tileIndex]->claim(getPlayerID());

                        break;
                    }
                    else {
                        DisplayManager::getInstance()->output("Index de balise invalide.");
                    }
                } catch (...) {
                    throw std::runtime_error("Index de balise invalide");
                }
            }
            else {
                DisplayManager::getInstance()->output("Choix invalide. Veuillez réessayer.");
            }
        } while (true);
        
    } catch (const std::exception& e) {
        DisplayManager::getInstance()->output("Erreur : " + std::string(e.what()));
    }
}