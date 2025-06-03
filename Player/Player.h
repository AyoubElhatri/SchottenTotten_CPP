#ifndef PLAYER_H
#define PLAYER_H
#include "../StoneTiles/StoneTiles.h"
class Player{
    private:
          unsigned int playerID ;
          Set playerDeck ;
          vector<shared_ptr<StoneTiles>> stoneTiles ;
          unsigned int tacticalCardsCounter = 0;
    public:


      Player(unsigned int playerID, Set playerDeck);
      virtual void playCard() = 0;
      void revendicateStoneTiles();
      void drawClanCards();  //piocher
      void drawTacticalCards();



};
#endif //PLAYER_H
