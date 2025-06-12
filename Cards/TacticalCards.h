//
// Created by Utilisateur on 31/05/2025.
//

#ifndef TACTICALCARDS_H
#define TACTICALCARDS_H
#include <string>
#include "../Colors.h"

#include "Cards.h"
class TacticalCards : public Cards {
    public:
    unsigned int getNumber() const override{return -1;}
    Colors getColor() const override; // je sais pas
};




#endif //TACTICALCARDS_H
