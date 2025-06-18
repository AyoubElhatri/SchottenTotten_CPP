#include"Human.h"
#include "../GameBoard/GameBoard.h"
#include "../Cards/EliteTroopsCards.h"
#include "../Cards/CombatModeCards.h"
#include "../Cards/RusesCards.h"
#include "../Logic2/GameLogic2.h"


void Human::playCard() {
    GameBoard& board = GameBoard::getInstance();

    DisplayManager::getInstance()->output("\n");
    getPlayerDeck().printSet();

    int cardIndex = -1;
    int tileIndex = -1;

    // Sélection de la carte
    DisplayManager::getInstance()->output("Choose a card index from your hand (0 to " +
                                          std::to_string(getPlayerDeck().getSize() - 1) + "): \n>> ");
    string strCardind = DisplayManager::getInstance()->takeInput();
    try {
        cardIndex = stoi(strCardind);
    } catch (...) {
        throw std::invalid_argument("Invalid input '" + strCardind + "', please choose a correct card index.");
    }

    if (cardIndex < 0 || cardIndex >= (int)getPlayerDeck().getSize()) {
        throw std::invalid_argument("Invalid card index '" + strCardind + "' out of range.");
    }

    // Récupération de la carte sélectionnée
    Cards* selectedCard = getPlayerDeck().getCardAt(cardIndex);

    // Gestion des différents types de cartes
    if (auto eliteTroop = dynamic_cast<EliteTroopsCards*>(selectedCard)) {
        DisplayManager::getInstance()->output("Choose a tile index to play on (0 to " +
                                              std::to_string(board.getBoardSize() - 1) + "): \n>> ");
        string strtile = DisplayManager::getInstance()->takeInput();
        try {
            tileIndex = std::stoi(strtile);
        } catch (...) {
            throw std::invalid_argument("Invalid input '" + strtile + "', please enter a valid tile index");
        }

        if (tileIndex < 0 || tileIndex >= board.getBoardSize()) {
            throw std::invalid_argument("Invalid tile index '" + strtile + "' out of bounds.");
        }

        if (board.getSharedTiles()[tileIndex]->isAlreadyClaimed()) {
            throw std::invalid_argument("Tile number '" + strtile + "' is already claimed.");
        }

        board.placeCardOnTileByIndexOfTheTile(tileIndex, *selectedCard, getPlayerID());
    }
    else if (auto combatMode = dynamic_cast<CombatModeCards*>(selectedCard)) {
        DisplayManager::getInstance()->output("Choose a tile index to apply combat mode (0 to " +
                                              std::to_string(board.getBoardSize() - 1) + "): ");
        string strtile2 = DisplayManager::getInstance()->takeInput();
        try {
            tileIndex = std::stoi(strtile2);
        } catch (...) {
            throw std::invalid_argument("Invalid input '" + strtile2 + "', please enter a valid tile index.");
        }

        if (tileIndex < 0 || tileIndex >= board.getBoardSize()) {
            throw std::invalid_argument("Tile index '" + strtile2 + "' is out of bounds.");
        }

        auto& tile = board.getSharedTiles()[tileIndex];
        if (tile->isAlreadyClaimed()) {
            throw std::invalid_argument("Tile index '" + strtile2 + "' is already claimed.");
        }

        combatMode->getEvent(tile.get());
        getPlayerDeck().moveCard(cardIndex, tile->getCombatModeCards());
    }
    else if (auto ruse = dynamic_cast<RusesCards*>(selectedCard)) {
        getPlayerDeck().moveCard(getPlayerDeck().getIndexOfCard(ruse->getName()), board.getDiscardedCards());
        ruse->getEvent(nullptr);  // Peut modifier la main !



    }
    else {
        DisplayManager::getInstance()->output("Choose a tile index to play on (0 to " +
                                              std::to_string(board.getBoardSize() - 1) + "): ");
        string strtile3 = DisplayManager::getInstance()->takeInput();
        try {
            tileIndex = std::stoi(strtile3);
        } catch (...) {
            throw std::invalid_argument("Invalid input '" + strtile3 + "', please enter a valid tile index.");
        }

        if (tileIndex < 0 || tileIndex >= board.getBoardSize()) {
            throw std::invalid_argument("Tile index '" + strtile3 + "' is out of bounds.");
        }

        if (board.getSharedTiles()[tileIndex]->isAlreadyClaimed()) {
            throw std::invalid_argument("Tile number '" + strtile3 + "' is already claimed.");
        }

        board.placeCardOnTileByIndexOfTheTile(tileIndex, *selectedCard, getPlayerID());
    }

    if (tileIndex != -1) {
        auto& tile = board.getSharedTiles()[tileIndex];
        if (tile->getPlayerCardsOnTilesByPlayerId(getPlayerID()).getSize() == tile->getNbOfPlayableCards()
            && tile->getFirstPlayerToFillTheStoneTile() == nullptr) {
            tile->setFirstPlayerToFillTheStoneTile(this);
        }
    }

    if ( CGameLogic::getInstance().getPlayerById(getPlayerID())->getPlayerDeck().getSize()<Rules::getInstance()->getNumberMaxOfCardsPerPlayer()) {
        // Piocher une carte si disponible
        bool canDrawClan = board.getRemainingClanCards().getSize() > 0;
        bool canDrawTactical = board.getRemainingTacticalCards().getSize() > 0;

        if (canDrawClan || canDrawTactical) {
            DisplayManager::getInstance()->output("\nChoose the type of card to draw:\n");
            if (canDrawClan) DisplayManager::getInstance()->output("1. Clan Card\n");
            if (canDrawTactical) DisplayManager::getInstance()->output("2. Tactical Card\n");

            string choice = DisplayManager::getInstance()->takeInput();
            if (choice == "1" && canDrawClan) drawClanCards(1);
            else if (choice == "2" && canDrawTactical) drawTacticalCards(1);
            else DisplayManager::getInstance()->output("Invalid choice or no cards available.\n");
        } else {
            DisplayManager::getInstance()->output("\nNo more cards to draw.\n");
        }
    }
    DisplayManager::getInstance()->output("\nYour current hand: ");
    getPlayerDeck().printSet();
}

void Human::playTurn() {
        DisplayManager::getInstance()->output("It's the turn of the player " + std::to_string(getPlayerID())+":");
        string choice1="\nWhat do you wish to do?  ";
        DisplayManager::getInstance()->output(choice1);
        DisplayManager::getInstance()->output("1. Play a card.\n");
        DisplayManager::getInstance()->output(string(choice1.size()-1,' ')+"2. Claim a Stone Tile.");
        
        string choice;
        do {
            DisplayManager::getInstance()->output("\n>> ");
            choice = DisplayManager::getInstance()->takeInput();
            
            if (choice == "1") {
                playCard();
                break;
            }
            else if (choice == "2") {
                GameBoard& board = GameBoard::getInstance();
                DisplayManager::getInstance()->output("Enter the index of The Stone Tile you wish to claim (0 à " +
                    std::to_string(board.getBoardSize() - 1) + ") : ");
                string tileIndex = DisplayManager::getInstance()->takeInput();
                int tileInd;
                try
                {
                    tileInd=stoi(tileIndex);
                }
                    catch (...) {
                        throw(invalid_argument("Invalid input'"+tileIndex+"'. Please enter a number."));;
                    }
                    if (tileInd >= 0 && tileInd < board.getBoardSize()) {
                        if (!(GameBoard::getInstance().getSharedTiles()[tileInd]->isAlreadyClaimed()))
                        {
                            board.getSharedTiles()[tileInd]->claim(getPlayerID());
                            if ((GameBoard::getInstance().getSharedTiles()[tileInd]->isAlreadyClaimed()))
                                throw(invalid_argument("This tile is now claimed, Congrats."));
                            else
                                throw(invalid_argument("This tile cannot be claimed at the moment, please continue playing."));
                        }
                        else{
                            throw(invalid_argument("This Tile is already claimed, please claim another one."));
                        }
                        break;
                    }
                    else {
                        throw(invalid_argument("Invalid Tile Index '"+tileIndex+"' is out of bounds."));
                    }

            }
            else {
                throw(invalid_argument("Invalid choice '"+choice+"', please enter a correct input."));
            }
        } while (true);
        


}