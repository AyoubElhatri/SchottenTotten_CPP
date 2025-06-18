

#ifndef TRAITOR_H
#define TRAITOR_H
#include "RusesCards.h"

class Traitor : public RusesCards {
public:
    Traitor(){cardName="Traitor";};
    void getEvent(StoneTiles* stoneTiles){std::cout<<"hello"<<endl;}

};

#endif
