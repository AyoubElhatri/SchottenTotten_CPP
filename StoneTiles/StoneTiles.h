#ifndef STONETILES_H
#define STONETILES_H
#include <memory>
#include "../Collections/Set.h"
#include "../Player/Player.h"
using namespace std;
class StoneTiles {
       private:
       unsigned int Position;
       unsigned int NbOfPlayableCards;//il faut verifier
       Set PlayerCards1;
       Set PlayerCards2;
       Set CombatModeCards;
       unique_ptr<Player> claimedBy;
       bool StoneTileIsClaimed;
       public:
       unsigned int getPosition() const{return Position;}
       bool isAlreadyClaimed() const {return StoneTileIsClaimed;}
       //bool isClaimable(Player* player) const ;
       void claim(Player* player);

       bool canPlaceCard();


       StoneTiles(unsigned int Pos) {
              Position = Pos;
              PlayerCards1= Set();
              PlayerCards2=Set();
              CombatModeCards=Set();

       }
       unsigned int getNbOfPlayableCards(){return NbOfPlayableCards;}
       void setNbOfPlayableCards(unsigned int nbOfPlayableCards){NbOfPlayableCards=nbOfPlayableCards;}
       void setPosition(unsigned int Pos){Position=Pos;}
       void addCardToPlayer(unsigned int playerId, std::unique_ptr<Cards> cards);
       bool canPlaceCard() const;
       std::unique_ptr<Cards> removeCardFromPlayer(unsigned int playerId, unsigned int cardIndex);

};



#endif //STONETILES_H
