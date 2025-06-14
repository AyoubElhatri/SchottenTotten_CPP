

#ifndef TACTICALCARDS_H
#define TACTICALCARDS_H
#include <string>
#include "../Colors.h"
#include "Cards.h"
#include <iostream>

class StoneTiles;

class TacticalCards : public Cards {
    public:
   // unsigned int getNumber() const override{return -1;}
   // Colors getColor() const override; // je sais pas
    void getEvent(StoneTiles* stoneTiles) override{std::cout<<"";};
    /*std::unique_ptr<Cards> clone() const override {
        return std::make_unique<TacticalCards>(*this);
    };*/
};




#endif
