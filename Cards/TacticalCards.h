//
// Created by Utilisateur on 31/05/2025.
//

#ifndef TACTICALCARDS_H
#define TACTICALCARDS_H
#include <string>
#include "../Colors.h"
#include "Cards.h"
#include <iostream>

class TacticalCards : public Cards {
    public:
    unsigned int getNumber() const override{return -1;}
    Colors getColor() const override; // je sais pas
    void getEvent() override{std::cout<<"";};
    std::unique_ptr<Cards> clone() const override {
        return std::make_unique<TacticalCards>(*this);
    };
};




#endif //TACTICALCARDS_H
