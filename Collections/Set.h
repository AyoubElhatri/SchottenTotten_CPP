#ifndef SET_H
#define SET_H
#include <vector>
#include <algorithm>
#include <memory>
#include "../Cards/Cards.h"
#include "../Player/Player.h"
#include "../CombinationType.h"
#include "../Cards/ClanCards.h"
#include "../Utils.h"
#include <iostream>
using namespace std;
#define maxOfCards 3;

class Set {
private:
    vector<unique_ptr<Cards>> SetOfCards;
    Player* owner;
public:
    unsigned int getSize()const {return SetOfCards.size();}
    Set(Set&& IndexSet) ;
    unique_ptr<Cards> getCardbyIndex(unsigned int IndexParam);
    void addCard(unique_ptr<Cards>& Card) {SetOfCards.push_back(move(Card));}
    void moveCard(unsigned int IndexOfCard, Set& IndexSet);
    bool isComplete() const{ return SetOfCards.size() == maxOfCards;}
    Set(Player* ownerParam) : owner(ownerParam){}
    Player* getOwner()const { return owner;}
    CombinationType evaluateCombination() const;




};



#endif //SET_H
