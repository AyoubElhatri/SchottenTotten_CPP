//
// Created by Utilisateur on 31/05/2025.
//

#ifndef ELITETROOPSCARDS_H
#define ELITETROOPSCARDS_H
#include "ClanCards.h"
#include "TacticalCards.h"
using namespace std;
class EliteTroopsCards : public ClanCards, public TacticalCards{
    string Name;
    string getName(){return Name;}

};


#endif //ELITETROOPSCARDS_H
