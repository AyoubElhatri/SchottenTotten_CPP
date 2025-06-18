#include"Human.h"
#include "../GameBoard/GameBoard.h"
#include "../Cards/EliteTroopsCards.h"
#include "../Cards/CombatModeCards.h"
#include "../Cards/RusesCards.h"
#include "../Logic/GameLogic.h"

void Human::playCard() {
    GameBoard& board = GameBoard::getInstance();
    
    DisplayManager::getInstance()->output("\n");
    getPlayerDeck().printSet();

    int cardIndex = -1;
    int tileIndex = -1;

    // Sélection de la carte
    DisplayManager::getInstance()->output("Choose a card index from your hand (0 to " +
                                          std::to_string(getPlayerDeck().getSize() - 1) + "): \n>> ");
    string strCardind=DisplayManager::getInstance()->takeInput();
    try {
        cardIndex = stoi(strCardind);
    } catch (...) {
        throw std::invalid_argument("Invalid input'"+strCardind+"', please choose a correct card index.");
    }

    if (cardIndex < 0 || cardIndex >= (int)getPlayerDeck().getSize()) {
        throw std::invalid_argument("Invalid card index '"+strCardind+"' out of range.");
    }

    // Récupération de la carte sélectionnée
     Cards* selectedCard = getPlayerDeck().getCardAt(cardIndex);

    // Vérification du type de carte
    if (auto eliteTroop = dynamic_cast<EliteTroopsCards*>(selectedCard)) {
        // Traitement comme une ClanCards normale
        DisplayManager::getInstance()->output("Choose a tile index to play on (0 to " +
                                              std::to_string(board.getBoardSize() - 1) + "): \n>> ");
        string strtile=DisplayManager::getInstance()->takeInput();
        try {
            tileIndex = std::stoi(strtile);
        } catch (...) {
            throw std::invalid_argument("Invalid input '"+strtile+"', please enter a valid tile index");
        }

        if (tileIndex < 0 || tileIndex >= board.getBoardSize()) {
            throw std::invalid_argument("Invalid tile index '"+strtile+"' our of bounds, please enter a correct tile index.");
        }
        if (GameBoard::getInstance().getSharedTiles()[tileIndex]->isAlreadyClaimed())
        {
            throw std::invalid_argument("Tile number '"+strtile+"' is already claimed, cannot play the card on this tile.");
        }

        board.placeCardOnTileByIndexOfTheTile(tileIndex, *selectedCard, getPlayerID());
    }
    else if (auto combatMode = dynamic_cast<CombatModeCards*>(selectedCard)) {
        // Traitement des cartes de mode de combat
        DisplayManager::getInstance()->output("Choose a tile index to apply combat mode (0 to " +
                                              std::to_string(board.getBoardSize() - 1) + "): ");
        string strtile2=DisplayManager::getInstance()->takeInput();
        try {
            tileIndex = std::stoi(strtile2);
        } catch (...) {
            throw std::invalid_argument("Invalid input '"+strtile2+"', please enter a valid tile index.");
        }

        if (tileIndex < 0 || tileIndex >= board.getBoardSize()) {
            throw std::invalid_argument("Tile index '"+strtile2+"' is out of bounds, please enter a correct tile index.");
        }

        auto& tile = board.getSharedTiles()[tileIndex];
        if (tile->isAlreadyClaimed()) {
            throw std::invalid_argument("Tile index'"+strtile2+"' is already claimed, cannot apply combat mode");
        }
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
        string strtile3=DisplayManager::getInstance()->takeInput();
        try {
            tileIndex = std::stoi(strtile3);
        } catch (...) {
            throw std::invalid_argument("Invalid input '"+strtile3+"', please enter a valid tile index.");
        }

        if (tileIndex < 0 || tileIndex >= board.getBoardSize()) {
            throw std::invalid_argument("Tile index '"+strtile3+"' is out of bounds, please choose a correct tile index.");
        }
        if (GameBoard::getInstance().getSharedTiles()[tileIndex]->isAlreadyClaimed())
        {
            throw std::invalid_argument("Tile number '"+strtile3+"' is already claimed, cannot play the card on this tile.");

        }
        board.placeCardOnTileByIndexOfTheTile(tileIndex, *selectedCard, getPlayerID());
    }
    if (board.getSharedTiles()[tileIndex]->getPlayerCardsOnTilesByPlayerId(getPlayerID()).getSize()==board.getSharedTiles()[tileIndex]->getNbOfPlayableCards() && board.getSharedTiles()[tileIndex]->getFirstPlayerToFillTheStoneTile()==nullptr) {
        board.getSharedTiles()[tileIndex]->setFirstPlayerToFillTheStoneTile(this);
    }

    // Piocher une carte si possible
    bool canDrawClan = board.getRemainingClanCards().getSize() > 0;
    bool canDrawTactical = board.getRemainingTacticalCards().getSize() > 0;

    if (canDrawClan || canDrawTactical) {
        string ask="\nChoose the type of card you wanna draw: ";
        DisplayManager::getInstance()->output(ask);
        if (canDrawClan) DisplayManager::getInstance()->output("1. Clan Card\n");
        if (canDrawTactical) DisplayManager::getInstance()->output(string(ask.size()-1,' ')+"2. Tactical Card");
        
        string choice="";
        do {
            DisplayManager::getInstance()->output("\nYour choice (1 or 2): >> ");
            choice = DisplayManager::getInstance()->takeInput();
            
            if (choice == "1" && canDrawClan) {
                drawClanCards(1);
                break;
            }
            else if (choice=="1" && !canDrawClan)
            {
                throw(std::invalid_argument("No more clan cards remain, please make another choice."));
            }
            else if (choice == "2" && canDrawTactical) {
                drawTacticalCards(1);
                break;
            }
            else if (choice=="2" && !canDrawTactical)
            {
                throw(std::invalid_argument("No more tactical cards remain, please make another choice."));
            }
            else {
                throw(invalid_argument("Invalid input '"+choice+"', please enter a valid choice."));
            }
        } while (true);
    }

    else {
        DisplayManager::getInstance()->output("\nNore more cards are available to draw from.");
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