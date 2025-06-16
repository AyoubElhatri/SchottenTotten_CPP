#include "GameLogic.h"
#include "../GameBoard.h"
#include"../Cards/Recruiter.h"
#include"../DisplayManager.h"


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
    GameBoard* board = &GameBoard::getInstance();

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






