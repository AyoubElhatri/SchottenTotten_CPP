
#ifndef COMBATMODECARDS_H
#define COMBATMODECARDS_H
#include <memory>
#include "../StoneTiles/StoneTiles.h"
#include "TacticalCards.h"

using namespace std;
class CombatModeCards : public TacticalCards{
   private:
    shared_ptr<StoneTiles> sharedTiles;
public:
        virtual void getEvent(StoneTiles* stoneTiles) = 0;
};

#endif //COMBATMODECARDS_H*/
