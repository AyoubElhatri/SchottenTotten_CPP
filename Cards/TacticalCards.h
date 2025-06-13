#ifndef TACTICALCARDS_H
#define TACTICALCARDS_H

#include <string>
#include "../Colors.h"
#include "Cards.h"
#include <iostream>

class TacticalCards : public Cards {
public:
    TacticalCards(); // constructeur par défaut
    virtual ~TacticalCards(); // destructeur virtuel

    unsigned int getNumber() const override { return -1; }
    Colors getColor() const override; // déclaration ok
    void getEvent() override { std::cout << ""; }

    /*
    std::unique_ptr<Cards> clone() const override {
        return std::make_unique<TacticalCards>(*this);
    }
    */
};

#endif