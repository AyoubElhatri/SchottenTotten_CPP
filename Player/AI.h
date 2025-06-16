#ifndef AI_H
#define AI_H

#include "../GameBoard.h"
#include "../Cards/Cards.h"
#include <memory>
#include <vector>

using namespace std;

class AI : public Player {
public:
    AI(unsigned int playerId, Set&& deck)
      : Player(playerId, std::move(deck)) {}
    virtual ~AI() = default;
    virtual void playTurn(vector<unique_ptr<Cards>>& hand, GameBoard& gameBoard) = 0;
};

#endif // AI_H
