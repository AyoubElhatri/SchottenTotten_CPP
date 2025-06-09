#include "Set.h"
#include <map>
#include <set>
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

CombinationType Set::evaluateCombination() const {
    if (!isComplete()) return CombinationType::None;

    vector<int> values;
    set<string> colors;

    for (const auto& card : SetOfCards) {
        values.push_back(card->getValue()); //je ne sais pas comment faire ??
        colors.insert(card->getColor()); // ..???
    }
    sort(values.begin(), values.end());

    bool isSequence = (values[1] == values[0] + 1) && (values[2] == values[1] + 1);
    bool isSameColor = (colors.size() == 1);
    bool isSet = (values[0] == values[1]) && (values[1] == values[2]);

    if (isSequence && isSameColor) return CombinationType::Suite_Couleur;
    if (isSet) return CombinationType::Brelan;
    if (isSameColor) return CombinationType::Couleur;
    if (isSequence) return CombinationType::Suite;

    return CombinationType::Somme;
}


