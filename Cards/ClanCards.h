#ifndef CLANCARDS_H
#define CLANCARDS_H

#include <iostream>
#include <memory>

#include "../Colors.h"
#include "Cards.h"

enum class Colors;

class ClanCards: public Cards {
private:
    unsigned int number;
    Colors color;
public:
    // Constructeur explicite prenant number et color
    ClanCards(): number(0), color(Colors::Red) {
        }

    ClanCards(unsigned int num, Colors col) : number(num), color(col) {
    cardName = std::to_string(getNumber()) + "-" + std::to_string(static_cast<int>(getColor()));
    }
    unsigned int getNumber() const  { return number; }
    Colors getColor() const  { return color; }
    void setNumber(unsigned int numbers) { number = numbers; }
    void setColor(Colors colors) { color = colors; }
    /*std::unique_ptr<Cards> clone() const override { return std::make_unique<ClanCards>(*this); }*/
    void getEvent(StoneTiles* stoneTiles)override { return ;};
};

#endif // CLANCARDS_H