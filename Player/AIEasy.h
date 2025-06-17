#ifndef AIEASY_H
#define AIEASY_H

#include <memory>

#include "AI.h"
#include "../GameBoard/GameBoard.h"
#include "../Player/Player.h"

class AIEasy : public AI {

private:
    int m_playerID;

    int chooseCardIndex(const std::vector<std::unique_ptr<Cards>>& cards);

    int chooseTileIndex(const GameBoard& gameBoard);
public:
    AIEasy(unsigned int playerId);
    void playTurn(std::vector<std::unique_ptr<Cards>>& playerCards, GameBoard& gameBoard);


};





#endif //AIEASY_H
