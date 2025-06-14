#include "GameLogic.h"

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
    if (players.size() != 2) {
        cerr << "Error! You must provide two players." << endl;
        return;
    }
    cout << "**********************************  Starting game  *********************************** " << endl;
    initializePlayerDecks();
    turnNumber = 0;
    while (true) {
        Player* currentPlayer = players[turnNumber % 2].get();
        cout<<"" << endl;
    }

    cout << "**********************************  End Game  ********************************** " << endl;
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






