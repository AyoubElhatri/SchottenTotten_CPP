#include "Set.h"
#include <map>
#include <set>

Set::Set(Set&& IndexSet) {
    SetOfCards = std::move(IndexSet.SetOfCards);
}

unique_ptr<Cards> Set::getCardbyIndex(unsigned int IndexParam) {
    if (IndexParam >= getSize()) {
        std::cerr << "Exception: Index hors limite dans getCardbyIndex\n";
        return nullptr;
    }
    unique_ptr<Cards> IndexCard = std::move(SetOfCards[IndexParam]);
    SetOfCards.erase(SetOfCards.begin() + IndexParam);
    return std::move(IndexCard);
}

const Cards* Set::getCardAt(unsigned int IndexParam) const {
    if (IndexParam >= getSize()) {
        std::cerr << "Exception: Index hors limite dans getCardAt\n";
        return nullptr;
    }
    return SetOfCards[IndexParam].get();
}

void Set::moveCard(unsigned int IndexOfCard, Set& IndexSet) {
    unique_ptr<Cards> NewCard = getCardbyIndex(IndexOfCard);
    if (NewCard) {
        IndexSet.addCard(std::move(NewCard));
    }
}

CombinationType Set::evaluateCombination() const {
    if (!isComplete()) return CombinationType::None;

    vector<int> values;
    set<Colors> colors;

    for (const auto& card : SetOfCards) {
        const ClanCards* clanCard = dynamic_cast<const ClanCards*>(card.get());
        if (clanCard) {
            values.push_back(clanCard->getNumber());
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