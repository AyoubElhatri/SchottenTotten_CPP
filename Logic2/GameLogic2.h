//
// Created by P Utilisateur on 18/06/2025.
//

#ifndef GAMELOGIC2_H
#define GAMELOGIC2_H
#include <vector>
#include <memory>
#include "../Player/Player.h"
#include"../Rules/Rules.h"
#include <sstream>
#include "../GameBoard/GameBoard.h"
#include <regex>

#define CONSOLE_WIDTH 100
#ifdef _WIN32
#include <thread>
#include<chrono>
#else
#include <unistd.h>
#endif


using namespace std;


class CGameLogic {
    private:
        unsigned int turnNumber;
        vector<unique_ptr<Player>> players;
        static unique_ptr<CGameLogic> instance ;
        CGameLogic();



        int Player1Wins=0;
    int Player2Wins=0;
    void printOption(string option);
    void printWithColor(string option, string color);
    void getFreespace(int i=1);
    void printStars();
    void clearScreen();
    void getReturn();
    void printLoading();
    void fillWithDashes(string text);
    int getRemainder(string msg1,string msg2){return msg1.size()-msg2.size();}
    int getRemainder(string msg1, unsigned int sizemsg2){return msg1.size()-sizemsg2;}
    string getClean(string text);
    void printClean(string text);
    void printBoardalpha();
    void printBoardalpha2();
    void printInLast(string Text);
    void PlayerVictory(int i);
    void PlayerRounds();

    public :
        CGameLogic(const CGameLogic&) = delete;
        CGameLogic(CGameLogic&&) = delete;
        CGameLogic& operator=(const CGameLogic&) = delete;
        CGameLogic& operator=(CGameLogic&&) = delete;
        ~CGameLogic() = default;
        static CGameLogic& getInstance();
        void addPlayer(std::unique_ptr<Player> player);
        void startGame();
        void initializePlayerDecks();
        unsigned int getTurnNumber() const noexcept {return turnNumber;}
        void setTurnNumber(unsigned int turnNumber) noexcept {this->turnNumber = turnNumber;}
        const vector<unique_ptr<Player>>& getPlayers() const noexcept {return players;}
        void runGameLoop();
        void mainDisplay();
        void getSleep(int timeToSleep=2);
    void getChoiceMain();
    void getChoiceStart();
    void getChoiceInfo();
    void getMainConsole();
    void getChoiceRoundLoading(int i);
        unsigned int getCurrentPlayerIndex() const noexcept {
            return turnNumber % players.size();
        }
    Player* getCurrentPlayer() noexcept {
            return players[getCurrentPlayerIndex()].get();
        }
    Player* getPlayerById(unsigned int playerId) noexcept {
            return players[playerId-1].get();
        }


        bool checkWinner();
    static void deleteInstance();



};











#endif //GAMELOGIC2_H
