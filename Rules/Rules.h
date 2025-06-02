#ifndef RULES_H
#define RULES_H
#include <unordered_map>
#include <memory>

using namespace std;
class Rules{
      public :
            class Builder;
      private:
            static unique_ptr<Rules> instance;
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
            unsigned int getNumberOfStoneTiles() const { return numberOfStoneTiles;}
            unsigned int getNumberOfClanCardsPerColor() const{return numberOfClanCardsPerColor;}
            unsigned int getNumberOfAlignedTilesToWin() const {return numberOfAlignedTilesToWin;}
            unsigned int getNumberOfUnalignedTilesToWin() const{return numberOfUnalignedTilesToWin;}
            unsigned int getNumberOfPlayer() const{return numberOfPlayer;}

     class Builder {
      private:
            unique_ptr<Rules> rules;

      public:
            Builder& setNumberOfStoneTiles(unsigned int n){rules->numberOfStoneTiles = n;}
            Builder& setNumberOfClanCardsPerColor(unsigned int n){rules->numberOfClanCardsPerColor = n;}
            Builder& setNumberOfAlignedTilesToWin(unsigned int n){rules->numberOfAlignedTilesToWin = n;}
            Builder& setNumberOfUnalignedTilesToWin(unsigned int n){rules->numberOfUnalignedTilesToWin = n;}
            Builder& setNumberOfPlayers(unsigned int n){rules->numberOfPlayer = n;

            //Builder& addClanCardColor(const std::string& color, unsigned int count);
            //Builder& addTacticalCard(const std::string& name, unsigned int count);


      };
};


#endif //RULES_H
