

#ifndef SPY_H
#define SPY_H

#include "EliteTroopsCards.h"

class Spy : public EliteTroopsCards {
public:
    Spy(){TacticalCards::cardName= "Spy";};
    void getEvent(StoneTiles* stoneTiles){};
};



#endif //SPY_H*/
