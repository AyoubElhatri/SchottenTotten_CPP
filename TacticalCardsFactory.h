
#ifndef TACTICALCARDSFACTORY_H
#define TACTICALCARDSFACTORY_H
#include "Cards/Joker.h"
#include "Cards/Banshee.h"
#include "Cards/BlindMan.h"
#include "Cards/HeadsHunter.h"
#include "Cards/MudFight.h"
#include "Cards/ShieldBear.h"
#include "Cards/Spy.h"
#include "Cards/Traitor.h"
#include <string>

using namespace std;

class TacticalCardsFactory {
public:
    static unique_ptr<TacticalCards> createTacticalCard(const string& Card) {
        if (Card=="Joker") return make_unique<Joker>();
        else if (Card=="Banshee") return make_unique<Banshee>();
        else if (Card=="MudFight") return make_unique<MudFight>();
        else if (Card=="Traitor") return make_unique<Traitor>();
        else if (Card=="Spy") return make_unique<Spy>();
        else if (Card=="ShieldBear") return make_unique<ShieldBear>();
        else if (Card=="HeadsHunter") return make_unique<HeadsHunter>();
        else if (Card=="BlindMan") return make_unique<Blindman>();
        else return nullptr;
};
};



#endif //TACTICALCARDSFACTORY_H*/
