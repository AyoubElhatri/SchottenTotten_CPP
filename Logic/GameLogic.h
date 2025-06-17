#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include <vector>
#include <memory>
#include "../Player/Player.h"
#include "../Logic/GameLogic.h"
#include"../Rules/Rules.h"
#include "../GameBoard/GameBoard.h"


using namespace std;


class GameLogic {
    private:
        unsigned int turnNumber;
        vector<unique_ptr<Player>> players;
        static unique_ptr<GameLogic> instance ;
        GameLogic();

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
        void runGameLoop();
        unsigned int getCurrentPlayerIndex() const noexcept {
            return turnNumber % players.size();
        }
        Player* getCurrentPlayer() noexcept {
            return players[getCurrentPlayerIndex()].get();
        }
        Player* getPlayerById(unsigned int playerId) noexcept {
            return players[playerId-1].get();
        }


        bool checkWinner() const  ;



};












#endif //GAMELOGIC_H
