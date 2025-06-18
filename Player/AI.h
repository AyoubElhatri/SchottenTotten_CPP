#ifndef AI_H
#define AI_H

#include "../GameBoard/GameBoard.h"
#include "../Cards/Cards.h"
#include <memory>
#include <vector>

using namespace std;

class AI : public Player {
public:
    AI(unsigned int playerId)
      : Player(playerId) {}
    virtual ~AI() = default;
};

#endif // AI_H
