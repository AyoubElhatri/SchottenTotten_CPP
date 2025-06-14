
#ifndef COMBATMODECARDS_H
#define COMBATMODECARDS_H
#include <memory>
#include "../StoneTiles/StoneTiles.h"
using namespace std;
class CombatModeCards : public TacticalCards{
   private:
    shared_ptr<StoneTiles> sharedTiles;
public:
        void getEvent(StoneTiles* stoneTiles) override{std::cout<<"";};
};

#endif //COMBATMODECARDS_H*/
