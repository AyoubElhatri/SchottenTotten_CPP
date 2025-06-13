

#ifndef ELITETROOPSCARDS_H
#define ELITETROOPSCARDS_H
#include "ClanCards.h"
#include "TacticalCards.h"
using namespace std;
class EliteTroopsCards : public ClanCards, public TacticalCards{
private:
    string Name;
public:
    string getName(){return Name;}
    EliteTroopsCards(): ClanCards() {
        Name = "Elite Troops";
    } ;




};


#endif
