#include "Set.h"
unique_ptr<Cards> Set::getCardbyIndex(unsigned int IndexParam) {
    if (IndexParam>=getSize()) {
        cout<<"Cexception";
    }
    unique_ptr<Cards> IndexCard= move(SetOfCards[IndexParam]);
    SetOfCards.erase(SetOfCards.begin()+IndexParam);
    return move(IndexCard);
}
void Set::moveCard(unsigned int IndexOfCard, Set& IndexSet) {
    unique_ptr<Cards> NewCard=getCardbyIndex(IndexOfCard);
    IndexSet.addCard(NewCard);
}
