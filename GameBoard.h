//
// Created by Utilisateur on 31/05/2025.
//

#ifndef GAMEBOARD_H
#define GAMEBOARD_H
using namespace std;
class GameBoard{
    private:
        vector<shared_ptr<StoneTiles>> sharedTiles;
        Set RemainingClanCards;
        Set RemainingTacticalCards;
        Set DiscardedCards;


};
#endif //GAMEBOARD_H
