#ifndef RULES_H
#define RULES_H
#include <unordered_map>
#include <memory>

using namespace std;
class Rules{
      public :
            class Builder;
      private:
            static unique_ptr<Rules> instance ;
            unsigned int numberOfStoneTiles;
            unsigned int numberOfClanCardsPerColor;
            unsigned int numberOfAlignedTilesToWin;
            unsigned int numberOfUnalignedTilesToWin;
            unsigned int numberOfPlayer;
            unordered_map<string, unsigned int> clanCardsByColor;
            unordered_map<string, unsigned int> tacticalCards;
            //Constructor
            Rules() = default;
            Rules(const Builder& builder);
      public:

            static Rules& getInstance();
            static void buildInstance(const Builder& builder);
            unsigned int getNumberOfStoneTiles() const;
            unsigned int getNumberOfClanCardsPerColor() const;
            unsigned int getNumberOfAlignedTilesToWin() const;
            unsigned int getNumberOfUnalignedTilesToWin() const;
            unsigned int getNumberOfPlayer() const;

      class Builder {
      private:
            unique_ptr<Rules> rules;

      public:
            Builder& setNumberOfStoneTiles(unsigned int n);
            Builder& setNumberOfClanCardsPerColor(unsigned int n);
            Builder& setNumberOfAlignedTilesToWin(unsigned int n);
            Builder& setNumberOfUnalignedTilesToWin(unsigned int n);
            Builder& setNumberOfPlayers(unsigned int n);

            Builder& addClanCardColor(const std::string& color, unsigned int count);
            Builder& addTacticalCard(const std::string& name, unsigned int count);

            const Rules& getRules() const;
      };






};



#endif //RULES_H
