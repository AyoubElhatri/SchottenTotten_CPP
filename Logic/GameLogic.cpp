#include "GameLogic.h"

#include "../Display/DisplayConsole.h"
#include "../GameBoard/GameBoard.h"
#include"../Cards/Recruiter.h"
#include "../Display/DisplayManager.h"
#include "../Player/Human.h"
#include"../Player/Player.h"


std::unique_ptr<GameLogic> GameLogic::instance = nullptr;

GameLogic ::GameLogic() {

    Player* player1 = new Human(1);
    Player* player2 = new Human(2);

    addPlayer(std::unique_ptr<Player>(player1));
    addPlayer(std::unique_ptr<Player>(player2));
    DisplayManager::createInstance<DisplayConsole>();
}
GameLogic &GameLogic::getInstance() {
    if (instance == nullptr) {
        instance = unique_ptr<GameLogic>(new GameLogic());
    }
    return *instance;
}

void GameLogic::addPlayer(std::unique_ptr<Player> player) {
    players.push_back(std::move(player));
}

void GameLogic::initializePlayerDecks() {
    GameBoard& board = GameBoard::getInstance();
    Set& deck = board.getRemainingClanCards();
    unsigned int nbCards = Rules::getInstance()->getNumberMaxOfCardsPerPlayer();
    cout << "Distributing " << nbCards << " clan cards to each player." << endl;
    for (unsigned int j=0; j < nbCards; ++j) {
        for (unsigned int i = 0; i < nbCards; ++i) {
            if (deck.getSize() < 2) {
                std::cout << "Not enough cards in the deck to distribute." << std::endl;
                return;
            }
        }
        for (unsigned int i = 0; i < players.size(); ++i) {
            players[i]->drawClanCards(1);

        }
    }

}

void GameLogic::startGame() {

    cout <<endl <<"-----------------clan Cards :------------------------"<<endl;
    GameBoard::getInstance().getRemainingClanCards().printSet();
    cout <<endl<<"------------------------------------------------------"<<endl;

    cout <<endl <<"-----------------Tactical Cards :------------------------"<<endl;
    GameBoard::getInstance().getRemainingTacticalCards().printSet();
    cout <<endl<<"------------------------------------------------------"<<endl;

    initializePlayerDecks();

    for (unsigned int i = 0; i < players.size(); ++i) {
        cout<<"Joueur "<<players[i]->getPlayerID()<< " :"; players[i]->getPlayerDeck().printSet(); cout <<endl;
    }
    cout <<"----------------Aprés la distribution --------------------"<<endl;
    GameBoard::getInstance().getRemainingClanCards().printSet();

    //fillTestCards(*board);
    runGameLoop();




}
void GameLogic::runGameLoop() {
    GameBoard& board = GameBoard::getInstance();

   // std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Nettoyage buffer au départ

    while (!checkWinner()) {
        Player* currentPlayer = players[getCurrentPlayerIndex()].get();

        board.printBoard();
        DisplayManager::getInstance()->output("\nIt's Player " + std::to_string(currentPlayer->getPlayerID()) + "'s turn\n");
        currentPlayer->getPlayerDeck().printSet();

        int cardIndex = -1;
        int tileIndex = -1;

        DisplayManager::getInstance()->output("Choose a card index from your hand (0 to " +
                                              std::to_string(currentPlayer->getPlayerDeck().getSize() - 1) + "): ");
        try {
            cardIndex = std::stoi(DisplayManager::getInstance()->takeInput());
        } catch (...) {
            DisplayManager::getInstance()->output("Invalid input. Try again.\n");
            continue;
        }

        if (cardIndex < 0 || cardIndex >= (int)currentPlayer->getPlayerDeck().getSize()) {
            DisplayManager::getInstance()->output("Invalid card index.\n");
            continue;
        }

        DisplayManager::getInstance()->output("Choose a tile index to play on (0 to " +
                                              std::to_string(board.getBoardSize() - 1) + "): ");
        try {
            tileIndex = std::stoi(DisplayManager::getInstance()->takeInput());
        } catch (...) {
            DisplayManager::getInstance()->output("Invalid input. Try again.\n");
            continue;
        }

        if (tileIndex < 0 || tileIndex >= board.getBoardSize()) {
            DisplayManager::getInstance()->output("Invalid tile index.\n");
            continue;
        }

        std::string cardName = currentPlayer->getPlayerDeck().getCardAt(cardIndex)->getName();
        std::cout << "[DEBUG] Joueur " << currentPlayer->getPlayerID() << " joue la carte : " << cardName << std::endl;

        Set& playerDeck = currentPlayer->getPlayerDeck();
        auto& tile = board.getSharedTiles()[tileIndex];

        try {
            tile->addCardOnTilesOfPlayer(currentPlayer->getPlayerID(), cardName, playerDeck);
        } catch (const std::exception& e) {
            DisplayManager::getInstance()->output(std::string("Erreur : ") + e.what() + "\n");
            continue;
        }

        // Tenter de revendiquer la tuile si possible
        if (!tile->isAlreadyClaimed()) {
            tile->claim();
        }

        // Piocher une seule carte si possible
        if (board.getRemainingClanCards().getSize() > 0) {
            currentPlayer->drawClanCards(1);
        }

        DisplayManager::getInstance()->output("\nAppuyez sur Entrée pour passer le clavier au joueur suivant...");
        //std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cin.get();

#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        turnNumber++;
    }
}
bool GameLogic::checkWinner() const {
    auto * rules = Rules::getInstance();
    const auto alignedToWin = rules->getNumberOfAlignedTilesToWin();
    const auto unalignedToWin = rules->getNumberOfUnalignedTilesToWin();

    GameBoard& board = GameBoard::getInstance();
    for (int playerId = 0; playerId < 2; playerId++) {
        int aligned = board.getAlingnedControlledTilesCount(playerId);
        int total = board.getControlledTilesCount(playerId);
        if (aligned >= alignedToWin || total >= unalignedToWin) {
            std::cout << " Le joueur " << playerId << " a gagné la partie !" << std::endl;
            return true;
        }
    }
    return false;
}






