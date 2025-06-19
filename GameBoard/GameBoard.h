#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "../Collections/Set.h"
#include "../StoneTiles/StoneTiles.h"
#include <memory>
#include <vector>
#include "../Colors.h"
#include "../Display/DisplayConsole.h"
#include "../Cards/ClanCards.h"
using namespace std;

class GameBoard {
private:
    mutable std::vector<std::shared_ptr<StoneTiles>> unclaimedBorders;
    static unique_ptr<GameBoard> instance;
    vector<std::shared_ptr<StoneTiles>> sharedTiles;
    Set RemainingClanCards;
    Set RemainingTacticalCards;
    Set DiscardedCards;


    GameBoard();
    GameBoard(const GameBoard&) = delete;
    GameBoard& operator=(const GameBoard&) = delete;

public:
    static GameBoard& getInstance();

    const vector<shared_ptr<StoneTiles>>& getSharedTiles() const;
      Set& getRemainingClanCards() ;
      Set& getRemainingTacticalCards() ;
      Set& getDiscardedCards() ;

    void discardCard(const Cards& card);

    void placeCardOnTileByIndexOfTheTile(int tileIndex, const Cards &card, int playerId);
    int getBoardSize() const{return static_cast<int>(sharedTiles.size());}
    bool isTileFree(int index) const;

    const std::vector<std::shared_ptr<StoneTiles>>& getUnclaimedTiles();
    void moveCardBetweenTiles(unsigned int fromBorderPos, unsigned int toBorderPos, unsigned int playerId, unsigned int cardIndex);
    std::shared_ptr<StoneTiles> findTileByPosition(unsigned int position);

    int getControlledTilesCount(int playerId) const;
    int getAlingnedControlledTilesCount(int playerId) const;

    string formatCard(const Cards* card) ;
    static void deleteInstance();

};

#endif // GAMEBOARD_H