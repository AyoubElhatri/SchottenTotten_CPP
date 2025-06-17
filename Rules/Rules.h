#ifndef RULES_H
#define RULES_H

#include <unordered_map>
#include <memory>
#include <string>

#include "../Colors.h"

using namespace std;

class Rules {
private:


    unsigned int numberOfStoneTiles;
    unsigned int numberOfAlignedTilesToWin;
    unsigned int numberOfUnalignedTilesToWin;
    unsigned int numberMaxOfCardsPerTiles = 3;

    unordered_map<Colors, unsigned int> clanCardsByColor;
    unordered_map<string, unsigned int> tacticalCards;

    Rules();  // constructeur privé par défaut

public:
    static Rules* instance;
    static Rules* getInstance();
    class Builder {
    private:
        unsigned int numberOfStoneTiles = 9;
        unsigned int numberOfAlignedTilesToWin = 3;
        unsigned int numberOfUnalignedTilesToWin = 5;
        unsigned int numberMaxOfCardsPerTiles = 3;

        unordered_map<Colors, unsigned int> clanCardsByColor;
        unordered_map<string, unsigned int> tacticalCards;

    public:
        Builder() = default;

        Builder& setNumberOfStoneTiles(unsigned int n) { numberOfStoneTiles = n; return *this; }
        Builder& setNumberOfAlignedTilesToWin(unsigned int n) { numberOfAlignedTilesToWin = n; return *this; }
        Builder& setNumberOfUnalignedTilesToWin(unsigned int n) { numberOfUnalignedTilesToWin = n; return *this; }
        Builder& setNumberMaxOfCardsPerTiles(unsigned int n) { numberMaxOfCardsPerTiles = n; return *this; }
        Builder& addClanCardColor(const Colors& color, unsigned int count) {
            clanCardsByColor[color] = count;
            return *this;
        }

        Builder& addTacticalCard(const string& name, unsigned int count) {
            tacticalCards[name] = count;
            return *this;
        }

        void build();
        friend class Rules;
    };

    Rules(const Builder& builder);
    static void buildInstance(const Builder& builder);

    unsigned int getNumberOfStoneTiles() const { return numberOfStoneTiles; }
    unsigned int getNumberOfAlignedTilesToWin() const { return numberOfAlignedTilesToWin; }
    unsigned int getNumberOfUnalignedTilesToWin() const { return numberOfUnalignedTilesToWin; }
    unsigned int getNumberMaxOfCardsPerTiles() const { return numberMaxOfCardsPerTiles; }
    unordered_map<Colors, unsigned int> getClanCardsByColor() const { return clanCardsByColor; }
    unordered_map<string, unsigned int> getTacticalCards() const { return tacticalCards; }
};

#endif // RULES_H