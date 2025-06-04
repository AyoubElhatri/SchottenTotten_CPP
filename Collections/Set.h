//
// Created by atoum on 03/06/2025.
//

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
    unsigned int getSize()const {
        return SetOfCards.size();
    }
    Set(Set&& IndexSet) {
        for (unsigned int IndexLoop=0; IndexLoop < IndexSet.getSize(); IndexLoop++) {

        }
    }
    unique_ptr<Cards> getCardbyIndex(unsigned int IndexParam){
        if (IndexParam>=getSize()) {
            cout<<"Cexception";
        }
        unique_ptr<Cards> IndexCard= move(SetOfCards[IndexParam]);
        SetOfCards.erase(SetOfCards.begin()+IndexParam);
        return move(IndexCard);
    }
    void addCard(unique_ptr<Cards> Card) {
        SetOfCards.push_back(move(Card));
    }
    void moveCard(unsigned int IndexOfCard){}
};



#endif //SET_H
