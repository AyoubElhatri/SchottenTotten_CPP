//
// Created by Utilisateur on 31/05/2025.
//

#ifndef TACTICALCARDS_H
#define TACTICALCARDS_H
#include <string>

#include "Cards.h"
class TacticalCards : public Cards {
    public:
    unsigned int getNumber() const override{return -1;}
    std::string getColor() const override{return "";}
};




#endif //TACTICALCARDS_H
