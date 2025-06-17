#include "Set.h"
#include <map>
#include <random>
#include <set>
#include "../Display/DisplayManager.h"
#include "../StoneTiles/StoneTiles.h"
#include "../GameBoard/GameBoard.h"

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

void Set::moveCard(string Cardname, Set& IndexSet) {

    unsigned int IndexOfCard = getIndexOfCard(Cardname);

    unique_ptr<Cards> NewCard = getCardbyIndex(IndexOfCard);
    if (NewCard) {
        IndexSet.addCard(std::move(NewCard));
    }
}
void Set::moveCard(unsigned int IndexOfCard, Set& IndexSet) {
    unique_ptr<Cards> NewCard = getCardbyIndex(IndexOfCard);
    if (NewCard) {
        IndexSet.addCard(std::move(NewCard));
    }
}


unsigned int Set::getIndexOfCard(string CardName) const {
    for (unsigned int i = 0; i < SetOfCards.size(); ++i) {
        if (SetOfCards[i]->getName() == CardName) {
            return i;
        }
    }
    throw std::invalid_argument("Card not found");
}




// A REFAIRE IL FAUT PEUT ETRE UNE CLASSE CHECK COMBINATION
CombinationType Set::evaluateCombination(StoneTiles& tiles) const {
   // METTRE CETTE MECANIQUE AILLEUR
   // if (!isComplete()) return CombinationType::None;

    vector<int> values;
    set<Colors> colors;
    unsigned int nbrMaxOfCards= tiles.getNbOfPlayableCards();
    if (SetOfCards.size() < nbrMaxOfCards) {
        CustomException Exc01=CustomException(INCOMPLETESET);
        throw(Exc01);
    }

// a corriger doit prendre en compte le nbr max de cartes par joueurs
    for (const auto& card : SetOfCards) {
        const ClanCards* clanCard = dynamic_cast<const ClanCards*>(card.get());
        if (clanCard) {
            values.push_back(clanCard->getNumber());
            colors.insert(clanCard->getColor());
        }
    }
    sort(values.begin(), values.end());

    bool isSequence = true;
    bool isSet = true;

    for (unsigned int i = 1; i < values.size(); ++i) {
        if (values[i] != values[i-1] + 1) {
            isSequence = false;
        }
    }

    // Vérifie le set pour toutes les cartes
    for (size_t i = 1; i < nbrMaxOfCards; ++i) {
        if (values[i] != values[0]) {
            isSet = false;
        }
    }

    bool isSameColor = (colors.size() == 1);

    if (isSequence && isSameColor) return CombinationType::ColorRun;
    if (isSet) return CombinationType::nOfAKind;
    if (isSameColor) return CombinationType::Color;
    if (isSequence) return CombinationType::Run;

    return Sum;
}

void Set::mixSet() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(SetOfCards.begin(), SetOfCards.end(), gen);
}

/*
void Set::printSet() const {
    for (const auto& card : SetOfCards) {
        DisplayManager::getInstance()->output( card->getName()+"/");
    }
}
*/

void Set::printSet() const {

    for (const auto& card : SetOfCards) {
        DisplayManager::getInstance()->output(GameBoard::getInstance().formatCard(card.get()) + " ");
    }
    DisplayManager::getInstance()->output("\n");
}


unsigned int Set::getTotalValue() const {
    unsigned int total = 0;
    for (const auto& card : SetOfCards) {
        if (auto clanCard = dynamic_cast<const ClanCards*>(card.get())) {
            total += clanCard->getNumber();
        }
    }
    return total;
}

vector<Cards*> Set::getRawCards() const {
    std::vector<Cards*> rawPointers;
    for (const auto& card : SetOfCards) {
        rawPointers.push_back(card.get());
    }
    return rawPointers;
}
