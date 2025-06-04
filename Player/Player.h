#ifndef PLAYER_H
#define PLAYER_H
#include "../StoneTiles/StoneTiles.h"
#include "../Collections/Set.h"
class Player{
    private:
          unsigned int playerID ;
          Set playerDeck ;
          vector<shared_ptr<StoneTiles>> stoneTiles ;
          unsigned int tacticalCardsCounter = 0;
          /*__remove_reference_t(Set &) playerDecks;
          unsigned int playerId;*/

      public:


      Player(unsigned int playerId, Set playerDecks);
      virtual ~Player() = default;

      unsigned int getPlayerID() const {return playerID;}
      Set& getPlayerDeck() {return playerDeck;}
      vector<shared_ptr<StoneTiles>>& getStoneTiles();
      unsigned int getTacticalCardsCounter() const {return tacticalCardsCounter;}

      virtual void playCard(unique_ptr<Cards>) = 0;
      void claimStoneTiles();
      void drawClanCards();  //piocher
      void drawTacticalCards();
      void incrementTacticalCardCounter();






};
#endif //PLAYER_H
