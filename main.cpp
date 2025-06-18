#include <iostream>
#include <memory>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "Display/DisplayManager.h"
#include "Display/Display.h"
#include "Display/DisplayConsole.h"
#include "GameBoard/GameBoard.h"
#include "Player/Human.h"
#include "Player/AIEasy.h"
#include "Cards/ClanCards.h"
#include "Collections/Set.h"
#include "Rules/Rules.h"
#include "Logic/GameLogic.h"
#include "Logic2/GameLogic2.h"

// Affiche le plateau et les cartes posées par chaque joueur sur chaque tuile
/*void printBoard(const GameBoard& board) {
    const auto& tiles = board.getSharedTiles();
    std::cout << "\n--- Plateau de jeu ---\n";
    for (size_t i = 0; i < tiles.size(); ++i) {
        auto& tile = tiles[i];
        std::cout << "Tuile " << i << " (pos: " << tile->getPosition() << "): ";

        auto& player1Cards = tile->getPlayerCards1();
        auto& player2Cards = tile->getPlayerCards2();

        std::cout << "J1[";
        for (unsigned int c = 0; c < player1Cards.getSize(); ++c) {
            const Cards* card = player1Cards.getCardAt(c);
            if (card) {
                std::cout << card->getNumber() << ",";
            }
        }
        std::cout << "] ";

        std::cout << "J2[";
        for (unsigned int c = 0; c < player2Cards.getSize(); ++c) {
            const Cards* card = player2Cards.getCardAt(c);
            if (card) {
                std::cout << card->getNumber() << ",";
            }
        }
        std::cout << "]\n";
    }
    std::cout << "---------------------\n";
}
*/
int main() {
    /*
    std::srand(std::time(nullptr));  // Initialiser le générateur aléatoire

    GameBoard& gameBoard = GameBoard::getInstance();

    // Préparer les cartes clan pour le joueur humain
    Set humanCards;
    humanCards.addCard(std::make_unique<ClanCards>(1, Colors::Red));
    humanCards.addCard(std::make_unique<ClanCards>(2, Colors::Red));
    humanCards.addCard(std::make_unique<ClanCards>(3, Colors::Red));
    humanCards.addCard(std::make_unique<ClanCards>(1, Colors::Blue));
    humanCards.addCard(std::make_unique<ClanCards>(2, Colors::Blue));
    humanCards.addCard(std::make_unique<ClanCards>(3, Colors::Blue));

    // Créer joueur humain
    Human humanPlayer(1, std::move(humanCards));

    // Préparer main IA (vecteur de cartes)
    std::vector<std::unique_ptr<Cards>> aiHand;
    aiHand.push_back(std::make_unique<ClanCards>(1, Colors::Green));
    aiHand.push_back(std::make_unique<ClanCards>(2, Colors::Green));
    aiHand.push_back(std::make_unique<ClanCards>(3, Colors::Green));

    AIEasy aiPlayer(2);

    bool gameOver = false;

    while (!gameOver) {
        // Tour du joueur humain
        std::cout << "Tour du joueur humain." << std::endl;
        humanPlayer.playCard(nullptr);

        printBoard(gameBoard);

        // Tour de l'IA
        std::cout << "Tour de l'IA." << std::endl;
        aiPlayer.playTurn(aiHand, gameBoard);

        printBoard(gameBoard);

        // Condition simple de fin : plus de cartes dans les mains
        if (humanPlayer.getPlayerDeck().getSize() == 0 && aiHand.empty()) {
            std::cout << "Fin de la partie." << std::endl;
            gameOver = true;
        }
    }
*/

    /*Set remainingClanCards;
    Set DiscardedCards;
    unique_ptr<ClanCards> cardssss=std::make_unique<ClanCards>(26, Colors::Red);


    //Rules(Rules::Builder());
    Rules::Builder builder;
    builder.setNumberOfStoneTiles(9)
           .setNumberOfAlignedTilesToWin(3)
           .setNumberOfUnalignedTilesToWin(5)
           .addClanCardColor(Colors::Red, 7)
           .addTacticalCard("Shield", 2);

    // Appel de buildInstance avec le builder
    Rules::buildInstance(builder);

    // Utilisation de Rules ensuite via getInstance()


    cout << Rules::getInstance()->getNumberOfStoneTiles() << endl;
    DisplayConsole console;
    console.output("zzz");
    DisplayManager::createInstance<DisplayConsole>();
    DisplayManager::getInstance()->output("Hello World!");

    GameBoard &game= GameBoard::getInstance();

    const Set& supraset = game.getRemainingClanCards();

    cout<< "Nombre de cartes restantes : " << supraset.getSize() << endl;

    supraset.printSet();*/




    Rules::Builder builder;
    builder.setNumberOfStoneTiles(9)
           .setNumberOfAlignedTilesToWin(3)
           .setNumberOfUnalignedTilesToWin(5)
           .addClanCardColor(Colors::Red, 9)
           .addClanCardColor(Colors::Yellow, 9)
           .addClanCardColor(Colors::Blue, 9)
           .addClanCardColor(Colors::Magenta, 9)
            //.addTacticalCard("Spy", 1)//Fonctionne
            //.addTacticalCard("Joker", 2)//Fonctionne
            // .addTacticalCard("MudFight", 1)//Fonctionne
        //.addTacticalCard("ShieldBear", 1)//Fonctionne
         //.addTacticalCard("BlindMan", 1) //Fonctionne
           //.addTacticalCard("Traitor", 1) //Fonctionne
            //.addTacticalCard("Banshee", 1) //Fonctionne
            //.addTacticalCard("Stratege",1)
           .addTacticalCard("Recruiter", 1)
           .setNumberMaxOfCardsPerPlayer(6)
           .setNumberMaxOfCardsPerTiles(3);




    // Appel de buildInstance avec le builder
    Rules::buildInstance(builder);
    DisplayManager::createInstance<DisplayConsole>();
    CGameLogic::getInstance().getMainConsole();


}
