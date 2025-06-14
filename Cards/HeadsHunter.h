
#ifndef HEADSHUNTER_H
#define HEADSHUNTER_H
#include "RusesCards.h"

class HeadsHunter : public RusesCards {
    public:
    HeadsHunter() { cardName = "Heads Hunter"; }
    void getEvent(StoneTiles* stoneTiles){};

};

#endif
