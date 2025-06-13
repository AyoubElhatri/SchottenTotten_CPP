

#ifndef MUDFIGHT_H
#define MUDFIGHT_H
#include "CombatModeCards.h"

class MudFight : public CombatModeCards {
    public:
    MudFight() : CombatModeCards() {};
        void getEvent(){cout << "MudFight" << endl;}


};

#endif
