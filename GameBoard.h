#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include "Collections/Set.h"
#include "StoneTiles/StoneTiles.h"
#include <memory>
#include <vector>
using namespace std;

class GameBoard {
private:
    static unique_ptr<GameBoard> instance;
    vector<std::shared_ptr<StoneTiles>> sharedTiles;
    Set RemainingClanCards;
    Set RemainingTacticalCards;
    Set DiscardedCards;
    unsigned int currentPlayerId = 1;
    GameBoard();
    GameBoard(const GameBoard&) = delete;
    GameBoard& operator=(const GameBoard&) = delete;

public:
    static GameBoard& getInstance();
    unsigned int getCurrentPlayerId() const {return currentPlayerId;}
    void setCurrentPlayerId(unsigned int playerId) { currentPlayerId = playerId; }

    const vector<shared_ptr<StoneTiles>>& getSharedTiles() const;
    const Set& getRemainingClanCards() const;
    const Set& getRemainingTacticalCards() const;
    const Set& getDiscardedCards() const;
    Set& getDiscardedCards() {return DiscardedCards;}

    void discardCard(const Cards& card);

    bool placeCardOnTile(int tileIndex, const Cards &card, int playerId);
    std::unique_ptr<Cards> drawClanCard();
    int getBoardSize() const{return static_cast<int>(sharedTiles.size());}
    bool isTileFree(int index) const;

    const std::vector<std::shared_ptr<StoneTiles>>& getUnclaimedBorders() const;
    void moveCardBetweenBorders(unsigned int fromBorderPos, unsigned int toBorderPos, unsigned int playerId, unsigned int cardIndex);
    std::shared_ptr<StoneTiles> findTileByPosition(unsigned int position);
};

#endif // GAMEBOARD_H
