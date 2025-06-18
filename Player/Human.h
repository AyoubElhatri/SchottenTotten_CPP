#ifndef HUMAN_H
#define HUMAN_H

#include "../Player/Player.h"
#include <memory>

using namespace std;

class Human : public Player {
public:
    Human(unsigned int playerId): Player(playerId) {}
    void playCard() override ;
    void playTurn() override ;
};

#endif // HUMAN_H

