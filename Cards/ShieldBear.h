
#ifndef SHIELDBEAR_H
#define SHIELDBEAR_H
#include "EliteTroopsCards.h"
class StoneTiles;

class ShieldBear : public EliteTroopsCards {
    public:
    ShieldBear(){TacticalCards::cardName= "ShieldBear";};
    void getEvent(StoneTiles* stoneTiles);
};


#endif //SHIELDBEAR_H*/
