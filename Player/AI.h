/*#ifndef AI_H
#define AI_H

#include "../GameBoard.h"
#include "../Cards/Cards.h"
#include <memory>
#include <vector>

class AI {
public:
    virtual ~AI() = default;
    virtual void playTurn(std::vector<std::unique_ptr<Cards>>& hand, GameBoard& gameBoard) = 0;
};

#endif // AI_H
*/