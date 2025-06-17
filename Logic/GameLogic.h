#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include <vector>
#include <memory>
#include "../Player/Player.h"
#include "../Logic/GameLogic.h"
#include"../Rules/Rules.h"
#include "../GameBoard.h"


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
        void runGameLoop(Player* player1, Player* player2);


    void generateAllClanCards() {
            GameBoard& board = GameBoard::getInstance();
            Set& deck = board.getRemainingClanCards();

            for (int value = 1; value <= 9; ++value) {
                for (int colorIndex = 0; colorIndex < 6; ++colorIndex) {
                    Colors color = static_cast<Colors>(colorIndex);
                    auto card = std::make_unique<ClanCards>(value, color);
                    deck.addCard(std::move(card));
                }
            }
        }
    void distributeClanCardsToPlayers(Player& player1, Player& player2, unsigned int nbCards = 6) {
            GameBoard& board = GameBoard::getInstance();
            Set& deck = board.getRemainingClanCards();

            for (unsigned int i = 0; i < nbCards; ++i) {
                if (deck.getSize() < 2) {
                    std::cout << "Not enough cards in the deck to distribute." << std::endl;
                    return;
                }

                player1.getPlayerDeck().addCard(deck.getCardbyIndex(0));
                player2.getPlayerDeck().addCard(deck.getCardbyIndex(0));
            }
        }


        bool checkWinner() const  ;



};












#endif //GAMELOGIC_H
