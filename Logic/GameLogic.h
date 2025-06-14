#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include <vector>
#include <memory>
#include "../Player/Player.h"

using namespace std;


class GameLogic {
    private:
        unsigned int turnNumber;
        vector<unique_ptr<Player>> players;
        static unique_ptr<GameLogic> instance ;
        GameLogic() = default;

    public :
        GameLogic(const GameLogic&) = delete;
        GameLogic(GameLogic&&) = delete;
        GameLogic& operator=(const GameLogic&) = delete;
        GameLogic& operator=(GameLogic&&) = delete;
        ~GameLogic() = default;
        static GameLogic& getInstance();

        void addPlayer(std::unique_ptr<Player> player);

        void startGame();
        void initializePlayerDecks();
        unsigned int getTurnNumber() const noexcept {return turnNumber;}
        void setTurnNumber(unsigned int turnNumber) noexcept {this->turnNumber = turnNumber;}
        const vector<unique_ptr<Player>>& getPlayers() const noexcept {return players;}



};












#endif //GAMELOGIC_H
