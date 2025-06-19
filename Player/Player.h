#ifndef PLAYER_H
#define PLAYER_H

#include <memory>
#include <vector>
#include "../Collections/Set.h"


using namespace std;

class Player {
private:
    unsigned int playerID;
    Set playerDeck;
    unsigned int tacticalCardsCounter = 0;

public:
    Player(unsigned int playerId);
    virtual ~Player() = default;
    unsigned int getPlayerID() const { return playerID; }
    Set& getPlayerDeck() { return playerDeck; }
    unsigned int getTacticalCardsCounter() const { return tacticalCardsCounter; }
    virtual void playTurn() =0;
    virtual void playCard() = 0;
    void drawClanCards(unsigned int count = 1);
    void drawTacticalCards(unsigned int count = 1);
    void incrementTacticalCardCounter() { tacticalCardsCounter++; }

};

#endif // PLAYER_H