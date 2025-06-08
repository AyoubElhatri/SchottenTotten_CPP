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
       unsigned int PlayableCards;
       Set PlayerCards1;
       Set PlayerCards2;
       Set CombatModeCards;
       unique_ptr<Player> Player;
       bool StoneTileIsClaimed;
};



#endif //STONETILES_H
