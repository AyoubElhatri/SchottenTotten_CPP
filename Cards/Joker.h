
#ifndef JOKER_H
#define JOKER_H
#include "EliteTroopsCards.h"
#include "../Display/Display.h"
#include "Cards.h"
class Joker : public EliteTroopsCards {
public:
    Joker() {TacticalCards::cardName = "Joker";};
    void getEvent(StoneTiles* stoneTiles);
};


#endif //JOKER_H*/
