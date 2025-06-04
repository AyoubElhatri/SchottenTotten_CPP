//
// Created by Utilisateur on 31/05/2025.
//

#ifndef COMBATMODECARDS_H
#define COMBATMODECARDS_H
#include <memory>
#include "../StoneTiles/StoneTiles.h"
using namespace std;
class CombatModeCards : public TacticalCards{
   private:
    shared_ptr<StoneTiles> sharedTiles;
};

#endif //COMBATMODECARDS_H
