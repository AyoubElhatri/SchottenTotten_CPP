//
// Created by atouf on 6/2/25.
//

#ifndef STONETILES_H
#define STONETILES_H
#include ""


class StoneTiles {
       private:
unsigned int Position;
unsigned int PlayableCards;
Set PlayerCards1;
Set PlayerCards2;
Set CombatModeCards;
unique_ptr<Player> Player;

};



#endif //STONETILES_H
