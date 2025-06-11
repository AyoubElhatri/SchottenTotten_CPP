#ifndef HUMAN_H
#define HUMAN_H

#include "../Player/Player.h"
#include <memory>

class Human : public Player {
public:
    Human(unsigned int playerId, Set&& playerDecks)
    : Player(playerId, std::move(playerDecks)) {}
    void playCard(std::unique_ptr<Cards> card) override;
};

#endif // HUMAN_H