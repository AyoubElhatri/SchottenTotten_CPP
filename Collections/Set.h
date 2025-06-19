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


class Set {
private:
    vector<unique_ptr<Cards>> SetOfCards;

public:
    Set() {
        SetOfCards.clear();
    }
    unsigned int getSize() const { return SetOfCards.size(); }

    Set(Set&& IndexSet);


    unique_ptr<Cards> getCardbyIndex(unsigned int IndexParam);


     Cards* getCardAt(unsigned int IndexParam) ;

    void addCard(unique_ptr<Cards> Card) { SetOfCards.push_back(std::move(Card)); }

    string getStringSet();
    void moveCard(string Cardname, Set& toSet);
    void moveCard(unsigned int IndexCard, Set& toSet);

    unsigned int getIndexOfCard(string CardName) const;

    CombinationType evaluateCombination(StoneTiles& tiles)  ;
    void mixSet();

    void printSet() const;
    unsigned int getTotalValue() const ;
    vector<Cards*> getRawCards() const;

};

#endif // SET_H