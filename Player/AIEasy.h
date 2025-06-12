#ifndef AIEASY_H
#define AIEASY_H

#include <memory>
#include "../GameBoard.h"
#include "../Player/Player.h"

class AIEasy {

private:
    int m_playerID;

    int chooseCardIndex(const std::vector<std::unique_ptr<Cards>>& cards);

    int chooseTileIndex(const GameBoard& gameBoard);
public:
    AIEasy(int playerID);
    void playTurn(std::vector<std::unique_ptr<Cards>>& playerCards, GameBoard& gameBoard);


};





#endif //AIEASY_H
