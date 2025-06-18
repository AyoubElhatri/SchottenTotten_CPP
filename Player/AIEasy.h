#ifndef AIEASY_H
#define AIEASY_H

#include "AI.h"
#include "../Player/Player.h"

class AIEasy : public AI {
public:
    AIEasy(unsigned int playerId) : AI(playerId) {}
    void playCard() override;
    void playTurn() override;
};

#endif // AIEASY_H