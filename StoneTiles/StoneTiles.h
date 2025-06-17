#ifndef STONETILES_H
#define STONETILES_H
#include <memory>
#include "../Collections/Set.h"
using namespace std;
#include "../Rules/Rules.h"
#include"../Player/Player.h"
class StoneTiles {
private:
    unsigned int Position;
    unsigned int NbOfPlayableCards ;
    Set PlayerCards1;
    Set PlayerCards2;
    Set CombatModeCards;
    unsigned int claimedBy;
    bool StoneTileIsClaimed;
    CombinationType comboType;
    Player* firstPlayerToFillTheStoneTile;
//Rules::getInstance()->getNumberMaxOfCardsPerTiles()
public:
    StoneTiles(unsigned int Pos)
        : Position(Pos), NbOfPlayableCards(Rules::getInstance()->getNumberMaxOfCardsPerTiles()), claimedBy(0), StoneTileIsClaimed(false), comboType(CombinationType::None) {}

    unsigned int getPosition() const { return Position; }
    unsigned int getClaimedBy() { return claimedBy; }
    void setClaimedBy(unsigned int claimedByParam){claimedBy = claimedByParam;}
    bool isAlreadyClaimed() const { return StoneTileIsClaimed; }
    CombinationType getComboType() const { return comboType; }
    void setComboType(CombinationType type) { comboType = type; }
    void claim();


    unsigned int getNbOfPlayableCards() const { return NbOfPlayableCards; }
    void setNbOfPlayableCards(unsigned int nbOfPlayableCards) { NbOfPlayableCards = nbOfPlayableCards; }
    void setPosition(unsigned int Pos) { Position = Pos; }

    void addCardToPlayer(unsigned int playerId,  const string& Cardname, Set& provenanceOfTheCard);
    std::unique_ptr<Cards> removeCardFromPlayer(unsigned int playerId, unsigned int cardIndex);

    Set& getPlayerCards1() { return PlayerCards1; }
    Set& getPlayerCards2() { return PlayerCards2; }
    Set& getCombatModeCards() { return CombatModeCards; }
    void printStoneTiles();


};

#endif //STONETILES_H
