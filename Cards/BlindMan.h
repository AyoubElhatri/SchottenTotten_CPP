
#ifndef BLINDMAN_H
#define BLINDMAN_H
#include "CombatModeCards.h"

class Blindman : public CombatModeCards {
public:
    Blindman() {
        cardName = "Blindman";
    }
    void getEvent(StoneTiles* stoneTiles);


};

#endif //BLINDMAN_H*/
