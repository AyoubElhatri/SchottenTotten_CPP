#include "GameLogic.h"

#include "../DisplayConsole.h"
#include "../GameBoard.h"
#include"../Cards/Recruiter.h"
#include"../DisplayManager.h"
#include "../Player/Human.h"
#include"../Player/Player.h"


std::unique_ptr<GameLogic> GameLogic::instance = nullptr;

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
    for (auto& player : players) {
        player->drawClanCards();
        // c'est pas que ça y faut ajouter meme le cas des cartes tactiques
    }
}

void GameLogic::startGame() {
    DisplayManager::createInstance<DisplayConsole>();
    DisplayManager::getInstance()->output("******************************** Start Game ********************************\n");
    GameBoard* board = &GameBoard::getInstance();
    generateAllClanCards();
    board->getRemainingClanCards().mixSet();
    Set emptySet1, emptySet2;
    Player* player1 = new Human(1, Set());
    Player* player2 = new Human(2, Set());
    cout <<"-----------------clan Cards :------------------------"<<endl;
    GameBoard::getInstance().getRemainingClanCards().printSet();
    cout <<"------------------------------------------------------"<<endl;
    distributeClanCardsToPlayers(*player1, *player2);

    player1->getPlayerDeck().printSet();
    player2->getPlayerDeck().printSet();
    cout <<"----------------Aprés la distribution --------------------"<<endl;
    GameBoard::getInstance().getRemainingClanCards().printSet();

    //fillTestCards(*board);
    runGameLoop(player1, player2);




}
void GameLogic::runGameLoop(Player* player1, Player* player2) {
    GameBoard& board = GameBoard::getInstance();
    Player* currentPlayer = player1;

    while (!checkWinner()) {
        board.printBoard();
        DisplayManager::getInstance()->output("\nIt's Player " + std::to_string(currentPlayer->getPlayerID()) + "'s turn\n");
        currentPlayer->getPlayerDeck().printSet();

        int cardIndex = -1;
        int tileIndex = -1;
        DisplayManager::getInstance()->output("Choose a card index from your hand (0 to " + std::to_string(currentPlayer->getPlayerDeck().getSize() - 1) + "): ");
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

        DisplayManager::getInstance()->output("Choose a tile index to play on (0 to " + std::to_string(board.getBoardSize() - 1) + "): ");
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

        board.getSharedTiles()[tileIndex]->addCardToPlayer(currentPlayer->getPlayerID(), cardName, playerDeck);
        // Suppression de la carte se fait dans moveCard

        if (board.getRemainingClanCards().getSize() > 0) {
            currentPlayer->getPlayerDeck().addCard(board.getRemainingClanCards().getCardbyIndex(0));
        }
        currentPlayer = (currentPlayer == player1) ? player2 : player1;
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
        if (aligned >= rules->getNumberOfAlignedTilesToWin() || total >= rules->getNumberOfStoneTiles()) {
            std::cout << " Le joueur " << playerId << " a gagné la partie !" << std::endl;
            return true;
        }
    }
    return false;
}






