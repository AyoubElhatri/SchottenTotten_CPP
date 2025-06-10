//
// Created by atouf on 6/2/25.
//

#ifndef STONETILES_H
#define STONETILES_H
#include <memory>
#include "../Collections/Set.h"
#include "../Player/Player.h"
using namespace std;
class StoneTiles {
       private:
unsigned int Position;
unsigned int NbOfPlayableCards;
Set PlayerCards1;
Set PlayerCards2;
Set CombatModeCards;
unique_ptr<Player> Player;
bool StoneTileIsClaimed;
public:
       StoneTiles(unsigned int Pos) {
              Position = Pos;
              PlayerCards1= Set();
              PlayerCards2=Set();
              CombatModeCards=Set();

       }
       unsigned int getPosition(){return Position};
       unsigned int getNbOfPlayableCards(){return NbOfPlayableCards;}
       void setNbOfPlayableCards(unsigned int nbOfPlayableCards){NbOfPlayableCards=nbOfPlayableCards;}
       void setPosition(unsigned int Pos){Position=Pos;}
};



#endif //STONETILES_H
