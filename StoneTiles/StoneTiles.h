#ifndef STONETILES_H
#define STONETILES_H
#include <memory>
#include "../Collections/Set.h"
using namespace std;
class StoneTiles {
private:
    unsigned int Position;
    unsigned int NbOfPlayableCards;
    Set PlayerCards1;
    Set PlayerCards2;
    Set CombatModeCards;
    unsigned int claimedBy;
    bool StoneTileIsClaimed;

public:
    StoneTiles(unsigned int Pos)
        : Position(Pos), NbOfPlayableCards(0), claimedBy(0), StoneTileIsClaimed(false) {}

    unsigned int getPosition() const { return Position; }
    bool isAlreadyClaimed() const { return StoneTileIsClaimed; }

    void claim(unsigned int uiParam);

    bool canPlaceCard() const;

    unsigned int getNbOfPlayableCards() const { return NbOfPlayableCards; }
    void setNbOfPlayableCards(unsigned int nbOfPlayableCards) { NbOfPlayableCards = nbOfPlayableCards; }
    void setPosition(unsigned int Pos) { Position = Pos; }

    void addCardToPlayer(unsigned int playerId, std::unique_ptr<Cards> cards);
    std::unique_ptr<Cards> removeCardFromPlayer(unsigned int playerId, unsigned int cardIndex);

    Set& getPlayerCards1() { return PlayerCards1; }
    Set& getPlayerCards2() { return PlayerCards2; }
};

#endif //STONETILES_H
