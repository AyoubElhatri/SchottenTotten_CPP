

#ifndef TACTICALCARDS_H
#define TACTICALCARDS_H
#include <string>
#include "../Colors.h"
#include "Cards.h"
#include <iostream>

class StoneTiles;

class TacticalCards : public Cards {
    public:
    void getEvent(StoneTiles* stoneTiles) override{std::cout<<"";};

};




#endif
