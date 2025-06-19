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

int main() {




    Rules::Builder builder;
    builder.setNumberOfStoneTiles(9)
           .setNumberOfAlignedTilesToWin(3)
           .setNumberOfUnalignedTilesToWin(5)
           .addClanCardColor(Colors::Red, 9)
           .addClanCardColor(Colors::Yellow, 9)
           .addClanCardColor(Colors::Blue, 9)
           .addClanCardColor(Colors::Magenta, 9)
            .addTacticalCard("Spy", 1)//Fonctionne
            .addTacticalCard("Joker", 2)//Fonctionne
             .addTacticalCard("MudFight", 1)//Fonctionne
        .addTacticalCard("ShieldBear", 1)//Fonctionne
         .addTacticalCard("BlindMan", 1) //Fonctionne
           .addTacticalCard("Traitor", 1) //Fonctionne
            .addTacticalCard("Banshee", 1) //Fonctionne
            .addTacticalCard("Stratege",1)
           .addTacticalCard("Recruiter", 1)
           .setNumberMaxOfCardsPerPlayer(6)
           .setNumberMaxOfCardsPerTiles(3);




    // Appel de buildInstance avec le builder
    Rules::buildInstance(builder);
    DisplayManager::createInstance<DisplayConsole>();
    CGameLogic::getInstance().getMainConsole();


}
