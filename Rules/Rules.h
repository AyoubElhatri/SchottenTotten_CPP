#ifndef RULES_H
#define RULES_H

#include <unordered_map>
#include <memory>
#include <string>
#include <stdexcept>

using namespace std;

class Builder;
class Rules {
private:


    static Rules* instance;

    unsigned int numberOfStoneTiles;
    unsigned int numberOfAlignedTilesToWin;
    unsigned int numberOfUnalignedTilesToWin;

    unordered_map<string, unsigned int> clanCardsByColor; // Quantité des cartes par couleur
    unordered_map<string, unsigned int> tacticalCards;

    Rules();
    Rules(const Builder& builder);

    static Rules* getInstance();
    static void buildInstance(const Builder& builder);

    unsigned int getNumberOfStoneTiles() const { return numberOfStoneTiles; }
    unsigned int getNumberOfAlignedTilesToWin() const { return numberOfAlignedTilesToWin; }
    unsigned int getNumberOfUnalignedTilesToWin() const { return numberOfUnalignedTilesToWin; }

    class Builder {
    private:
        unique_ptr<Rules> rules;

    public:
        Builder() : rules(make_unique<Rules>()) {}  // Initialise rules

        void setNumberOfStoneTiles(unsigned int n) { rules->numberOfStoneTiles = n; }
        void setNumberOfAlignedTilesToWin(unsigned int n) { rules->numberOfAlignedTilesToWin = n; }
        void setNumberOfUnalignedTilesToWin(unsigned int n) { rules->numberOfUnalignedTilesToWin = n; }

        Builder& addClanCardColor(const string& color, unsigned int count);
        Builder& addTacticalCard(const string& name, unsigned int count);

        friend class Rules;
    };
};

#endif // RULES_H