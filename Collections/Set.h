#ifndef SET_H
#define SET_H
#include <vector>
#include <algorithm>
#include <memory>
#include "../Cards/Cards.h"
#include <iostream>
using namespace std;

class Set {
private:
    vector<unique_ptr<Cards>> SetOfCards;
public:
    unsigned int getSize()const {return SetOfCards.size();}
    Set(Set&& IndexSet) ;
    unique_ptr<Cards> getCardbyIndex(unsigned int IndexParam);
    void addCard(unique_ptr<Cards>& Card) {SetOfCards.push_back(move(Card));}
    void moveCard(unsigned int IndexOfCard, Set& IndexSet);
};



#endif //SET_H
