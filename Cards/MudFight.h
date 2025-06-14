

#ifndef MUDFIGHT_H
#define MUDFIGHT_H
#include "CombatModeCards.h"

class MudFight : public CombatModeCards {
    public:
        MudFight(){cardName= "Mud Fight";};
    void getEvent(StoneTiles* stoneTiles){};

};

#endif
