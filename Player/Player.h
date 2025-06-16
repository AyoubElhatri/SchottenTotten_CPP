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
    vector<shared_ptr<StoneTiles>> stoneTiles;
    unsigned int tacticalCardsCounter = 0;

public:
    Player(unsigned int playerId, Set&& playerDecks);
    virtual ~Player() = default;

    unsigned int getPlayerID() const { return playerID; }
    Set& getPlayerDeck() { return playerDeck; }
    //const Set& getPlayerDeck() const { return playerDeck; }
    const vector<shared_ptr<StoneTiles>>& getStoneTiles() const { return stoneTiles; }

    unsigned int getTacticalCardsCounter() const { return tacticalCardsCounter; }

    virtual void playCard(unique_ptr<Cards>) = 0;

    // Méthode facultative, à définir ou supprimer
    // bool claimStoneTiles(unsigned int position);

    void drawClanCards(unsigned int count = 1);
    void drawTacticalCards(unsigned int count = 1);  // définir si utilisée

    void incrementTacticalCardCounter() { tacticalCardsCounter++; }
};

#endif // PLAYER_H