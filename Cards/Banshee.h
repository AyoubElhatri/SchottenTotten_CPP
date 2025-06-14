

#ifndef BANSHEE_H
#define BANSHEE_H
#include "Joker.h"
#include "RusesCards.h"

class Banshee : public RusesCards {
    public:
    Banshee(){cardName = "Banshee";};
    void getEvent(StoneTiles* stoneTiles){};
};


#endif //BANSHEE_H
