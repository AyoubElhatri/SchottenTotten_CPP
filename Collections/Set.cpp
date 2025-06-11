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
    set<Colors> colors;

    for (const auto& card : SetOfCards) {
        const ClanCards* clanCard = dynamic_cast<const ClanCards*>(card.get());
        if (clanCard) {
        values.push_back(clanCard->getNumber()); //je ne sais pas comment faire ??
        //colors.insert(colorToString(clanCard->getColor())); // ..???
            colors.insert(clanCard->getColor());
        }
    }
    sort(values.begin(), values.end());

    bool isSequence = (values[1] == values[0] + 1) && (values[2] == values[1] + 1);
    bool isSameColor = (colors.size() == 1);
    bool isSet = (values[0] == values[1]) && (values[1] == values[2]);

    if (isSequence && isSameColor) return CombinationType::ColorRun;
    if (isSet) return CombinationType::nOfAKind;
    if (isSameColor) return CombinationType::Color;
    if (isSequence) return CombinationType::Run;

    return CombinationType::Sum;
}


