#ifndef SET_H
#define SET_H

#include <vector>
#include <algorithm>
#include <memory>
#include <iostream>
#include "../Cards/Cards.h"
#include "../CombinationType.h"
#include "../Cards/ClanCards.h"

using namespace std;

#define maxOfCards 3

class Set {
private:
    vector<unique_ptr<Cards>> SetOfCards;

public:
    Set() {
        SetOfCards.clear();
    }
    unsigned int getSize() const { return SetOfCards.size(); }

    // Constructeur de déplacement
    Set(Set&& IndexSet);

    // Retire et retourne une carte (transfert de propriété)
    unique_ptr<Cards> getCardbyIndex(unsigned int IndexParam);

    // Retourne un pointeur const vers la carte, sans la retirer
    const Cards* getCardAt(unsigned int IndexParam) const;

    // Ajoute une carte (transfert de propriété)
    void addCard(unique_ptr<Cards> Card) { SetOfCards.push_back(std::move(Card)); }

    void moveCard(unsigned int IndexOfCard, Set& IndexSet);

    bool isComplete() const { return SetOfCards.size() == maxOfCards; }

    CombinationType evaluateCombination() const;
};

#endif // SET_H