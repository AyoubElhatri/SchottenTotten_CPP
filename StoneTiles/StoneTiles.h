#ifndef STONETILES_H
#define STONETILES_H
#include <memory>
#include "../Collections/Set.h"
using namespace std;
#include "../Rules/Rules.h"
#include"../Player/Player.h"
class GameLogic;
class StoneTiles {
private:
    unsigned int Position;
    unsigned int NbOfPlayableCards ;
    unordered_map<unsigned int,std::unique_ptr<Set>> PlayerCards;

    Set CombatModeCards;
    unsigned int claimedBy;
    bool StoneTileIsClaimed;
    CombinationType comboType;
    Player* firstPlayerToFillTheStoneTile;

public:
    StoneTiles(unsigned int pos)  ;


    unsigned int getPosition() const { return Position; }
    unsigned int getClaimedBy() { return claimedBy; }
    void setClaimedBy(unsigned int claimedByParam){claimedBy = claimedByParam;}
    bool isAlreadyClaimed() const { return StoneTileIsClaimed; }
    CombinationType getComboType() const { return comboType; }
    void setComboType(CombinationType type) { comboType = type; }
    void claim(unsigned int playerId);
    Player * getFirstPlayerToFillTheStoneTile() const { return firstPlayerToFillTheStoneTile; }
    unsigned int getNbOfPlayableCards() const { return NbOfPlayableCards; }
    void setNbOfPlayableCards(unsigned int nbOfPlayableCards) { NbOfPlayableCards = nbOfPlayableCards; }
    void setPosition(unsigned int Pos) { Position = Pos; }
    void setFirstPlayerToFillTheStoneTile(Player* player) { firstPlayerToFillTheStoneTile = player; }
    void addCardOnTilesOfPlayer(unsigned int playerId,  const string& Cardname, Set& provenanceOfTheCard);
    std::unique_ptr<Cards> removeCardFromPlayer(unsigned int playerId, unsigned int cardIndex);

    Set& getCombatModeCards() { return CombatModeCards; }
    unordered_map<unsigned int, std::unique_ptr<Set>>& getPlayerCards() { 
    return PlayerCards; 
}
    Set& getPlayerCardsOnTilesByPlayerId(unsigned int playerId) { 
    return *PlayerCards[playerId]; 
}

    void printStoneTiles();


};

#endif //STONETILES_H