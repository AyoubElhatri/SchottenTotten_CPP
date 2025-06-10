#ifndef GAMEBOARD_H
#define GAMEBOARD_H
using namespace std;
class GameBoard{
    private:
        vector<shared_ptr<StoneTiles>> sharedTiles;
        Set RemainingClanCards;
        Set RemainingTacticalCards;
        Set DiscardedCards;
        GameBoard() {};
        static GameBoard* instanceGameBoard;
        GameBoard(const GameBoard&) = delete;
        GameBoard& operator=(const GameBoard&) = delete;

    public:
        static GameBoard& getInstance() ;


};

Ga
#endif //GAMEBOARD_H
