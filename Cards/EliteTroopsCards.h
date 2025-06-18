

#ifndef ELITETROOPSCARDS_H
#define ELITETROOPSCARDS_H
#include "ClanCards.h"
#include "TacticalCards.h"
using namespace std;
class EliteTroopsCards : public ClanCards, public TacticalCards{
public:
    virtual int getColor(string color);
};
inline int EliteTroopsCards::getColor(string color="red")
{
    if (color=="Yellow"||color=="yellow")
    {
        return 0;
    }
    if (color=="Red"||color=="red")
    {
        return 1;
    }
    if (color=="Blue"||color=="blue")
    {
        return 2;
    }
    if (color=="Green"||color=="green")
    {
        return 3;
    }
    if (color=="Cyan"||color=="cyan")
    {
        return 4;
    }
    if (color=="Magenta"||color=="magenta")
    {
        return 5;
    }
    else
    {
        return -1;
    }
}


#endif
