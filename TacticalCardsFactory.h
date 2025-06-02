//
// Created by Utilisateur on 02/06/2025.
//

#ifndef TACTICALCARDSFACTORY_H
#define TACTICALCARDSFACTORY_H
#include "Cards/Joker.h"
#include "Cards/Banshee.h"
#include "Cards/ShieldBear.h"


using namespace std;

class TacticalCardsFactory {
    static TacticalCardsFactory* createTacticalCard(const string& Card) {
        if (Card=='Joker') return new Joker();
        else if (Card=='Banshee') return new Banshee();
        else if (Card=='MudFight') return new MudFight();
        else if (Card=='Traitor') return new Traitor();
        else if (Card=='Spy') return new Spy();
        else if (Card=='ShieldBear') return new ShieldBear();


        else return nullptr;

    }

};



#endif //TACTICALCARDSFACTORY_H
