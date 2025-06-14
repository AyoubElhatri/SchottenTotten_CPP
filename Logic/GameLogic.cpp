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






