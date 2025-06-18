//
// Created by P Utilisateur on 18/06/2025.
//

#include "GameLogic2.h"

#include "../DisplayConsole.h"
#include "../GameBoard.h"
#include"../Cards/Recruiter.h"
#include"../DisplayManager.h"
#include "../Player/Human.h"
#include"../Player/Player.h"


std::unique_ptr<GameLogic> GameLogic::instance = nullptr;

GameLogic ::GameLogic() {
    Player* player1 = new Human(1, Set());
    Player* player2 = new Human(2, Set());

    addPlayer(std::unique_ptr<Player>(player1));
    addPlayer(std::unique_ptr<Player>(player2));
}


void GameLogic::printBoardalpha() {
    printStars();
    getFreespace(5);
    const std::string blue = "\033[1;34m";   // bleu clair gras
    const std::string reset = "\033[0m";
        vector<shared_ptr<StoneTiles>> sharedTiles=GameBoard::getInstance().getSharedTiles();

    const int tileCount = static_cast<int>(sharedTiles.size());

    // Trouver la hauteur max de cartes pour chaque joueur
    int maxCardsP1 = 0, maxCardsP2 = 0;
    for (const auto& tile : sharedTiles) {
        maxCardsP1 = std::max(maxCardsP1, static_cast<int>(tile->getPlayerCards1().getRawCards().size()));
        maxCardsP2 = std::max(maxCardsP2, static_cast<int>(tile->getPlayerCards2().getRawCards().size()));
    }

    // Afficher les cartes du joueur 1 (en haut), ligne par ligne
    string cardss=" ";
    for (int row = 0; row < maxCardsP1; ++row) {
        for (const auto& tile : sharedTiles) {
            const auto& cards = tile->getPlayerCards1().getRawCards();
            if (row < static_cast<int>(cards.size())) {
                cardss+="  "+GameBoard::getInstance().formatCard(cards[row])+"     ";
            } else {
                cardss+="          ";
            }
        }
        printClean(cardss);
        cardss=" ";
    }

    string tilesToPrint=" ";
    // Afficher la séparation (ligne de tuiles)
    for (int i = 0; i < tileCount; ++i) {
        tilesToPrint+="--ST"+to_string(i)+"--   ";
    }
    printClean(tilesToPrint);

    // Afficher les cartes du joueur 2 (en bas), ligne par ligne
    string cardsss2=" ";
    for (int row = 0; row < maxCardsP2; ++row) {
        for (const auto& tile : sharedTiles) {
            const auto& cards = tile->getPlayerCards2().getRawCards();
            if (row < static_cast<int>(cards.size())) {
                cardsss2+="  "+GameBoard::getInstance().formatCard(cards[row])+"     ";
            } else {
                cardsss2+="          "; // Espace vide si pas de carte
            }
        }
        printClean(cardsss2);
        cardsss2=" ";
    }
    getFreespace(4);
    string info="ST[*]: Stone Tile n°* ";
    printInLast(info);
    printStars();
}
void GameLogic::printInLast(string Text)
{
    int space=100-Text.size();
    string toprint="#"+string(space-1,' ')+Text+"#\n";
    DisplayManager::getInstance()->output(toprint);
}





GameLogic &GameLogic::getInstance() {
    if (instance == nullptr) {
        instance = unique_ptr<GameLogic>(new GameLogic());
    }
    return *instance;
}
void GameLogic::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
unsigned int getUTF8size(string message){
    double size=0;
    for(char i: message){
        if(i!=' ')
            size+=(0.333333);
        else
            size+=1;

    }
    return (unsigned int)size;
}

void GameLogic::addPlayer(std::unique_ptr<Player> player) {
    players.push_back(std::move(player));
}

void GameLogic::initializePlayerDecks() {
    GameBoard& board = GameBoard::getInstance();
    Set& deck = board.getRemainingClanCards();
    unsigned int nbCards = Rules::getInstance()->getNumberMaxOfCardsPerPlayer();
    string deckprint= "Distributing " + to_string(nbCards) +" clan cards to each player.";
    printOption(deckprint);
    for (unsigned int j=0; j < nbCards; ++j) {
        for (unsigned int i = 0; i < nbCards; ++i) {
            if (deck.getSize() < 2) {
                string info= "Not enough cards in the deck to distribute.";
                printOption(info);
                return;
            }
        }
        for (unsigned int i = 0; i < players.size(); ++i) {
            players[i]->drawClanCards(1);

        }
    }

}
void GameLogic::printLoading() {
    string loading="LOADING...";
    printWithColor(loading,"green");
}
string GameLogic::getClean(string text)
{
    static const std::regex ansiRegex("\x1B\\[[0-9;]*[A-Za-z]");
    return regex_replace(text, ansiRegex, "");
}
void GameLogic::printClean(string text)
{
    Display *d=DisplayManager::getInstance();
    string clean=getClean(text);
    int remainder=CONSOLE_WIDTH-clean.size();
    if(remainder%2==0){
        string out="#"+string(remainder/2-1,' ')+text+string(remainder/2-1,' ')+"#\n";
        d->output(out);
    }
    else if (remainder%2!=0){
        string out="#"+string(remainder/2,' ')+text+string(remainder/2-1,' ')+"#\n";
        d->output(out);
    }
}


void GameLogic::startGame() {
    printStars();
    string Cards="Clan cards:";
    fillWithDashes(Cards);
    string stringse=GameBoard::getInstance().getRemainingClanCards().getStringSet();
    size_t splitpos=stringse.rfind(' ',300);
    if (splitpos==string::npos)
    {
        splitpos=300;
    }
    string stringse1=stringse.substr(0,splitpos);
    string stringse2=stringse.substr(splitpos+1);
    printClean(stringse1);
    printClean(stringse2);
    fillWithDashes("-");
    string tactic="Tactical Cards:";
    fillWithDashes(tactic);
    printOption(GameBoard::getInstance().getRemainingTacticalCards().getStringSet());
    fillWithDashes("-");
    getFreespace();
    initializePlayerDecks();
    for (unsigned int i = 0; i < players.size(); ++i) {
        string playerCards="Player "+to_string(players[i]->getPlayerID())+ " :"+players[i]->getPlayerDeck().getStringSet();
        printClean(playerCards);
    }
    getFreespace();
    string Distribute="After the distribution:";
    printOption(Distribute);
    string stringsee=GameBoard::getInstance().getRemainingClanCards().getStringSet();
    size_t splitpos2=stringsee.rfind(' ',200);
    if (splitpos2==string::npos)
    {
        splitpos=200;
    }
    string stringse3=stringsee.substr(0,splitpos2);
    string stringse4=stringsee.substr(splitpos2+1);
    printClean(stringse3);
    printClean(stringse4);
    getFreespace();
    printLoading();
    printStars();
    getSleep(4);
    //fillTestCards(*board);
    runGameLoop();






}
void GameLogic::runGameLoop() {
    GameBoard& board = GameBoard::getInstance();

    while (!checkWinner()) {
        Player* currentPlayer = players[getCurrentPlayerIndex()].get();

        printBoardalpha();
        DisplayManager::getInstance()->output("\nIt's Player " + std::to_string(currentPlayer->getPlayerID()) + "'s turn\n");
        currentPlayer->getPlayerDeck().printSet();

        int cardIndex = -1;
        int tileIndex = -1;
        DisplayManager::getInstance()->output("Choose a card index from your hand (0 to " + std::to_string(currentPlayer->getPlayerDeck().getSize() - 1) + "): ");
        try {
            cardIndex = std::stoi(DisplayManager::getInstance()->takeInput());
        } catch (...) {
            DisplayManager::getInstance()->output("Invalid input. Try again.\n");
            continue;
        }

        if (cardIndex < 0 || cardIndex >= (int)currentPlayer->getPlayerDeck().getSize()) {
            DisplayManager::getInstance()->output("Invalid card index.\n");
            continue;
        }

        DisplayManager::getInstance()->output("Choose a tile index to play on (0 to " + std::to_string(board.getBoardSize() - 1) + "): ");
        try {
            tileIndex = std::stoi(DisplayManager::getInstance()->takeInput());
        } catch (...) {
            DisplayManager::getInstance()->output("Invalid input. Try again.\n");
            continue;
        }

        if (tileIndex < 0 || tileIndex >= board.getBoardSize()) {
            DisplayManager::getInstance()->output("Invalid tile index.\n");
            continue;
        }

        std::string cardName = currentPlayer->getPlayerDeck().getCardAt(cardIndex)->getName();
        std::cout << "[DEBUG] Joueur " << currentPlayer->getPlayerID() << " joue la carte : " << cardName << std::endl;

        Set& playerDeck = currentPlayer->getPlayerDeck();

        board.getSharedTiles()[tileIndex]->addCardToPlayer(currentPlayer->getPlayerID(), cardName, playerDeck);
        // Suppression de la carte se fait dans moveCard

        if (board.getRemainingClanCards().getSize() > 0) {
            currentPlayer->drawClanCards(1);
        }
        turnNumber++;
    }
}
void GameLogic::printStars()
{   Display *c=DisplayManager::getInstance();
    string stars=string(CONSOLE_WIDTH,'#')+"\n";
    c->output(stars);
}

bool GameLogic::checkWinner() const {
    auto * rules = Rules::getInstance();
    const auto alignedToWin = rules->getNumberOfAlignedTilesToWin();
    const auto unalignedToWin = rules->getNumberOfUnalignedTilesToWin();

    GameBoard& board = GameBoard::getInstance();
    for (int playerId = 0; playerId < 2; playerId++) {
        int aligned = board.getAlingnedControlledTilesCount(playerId);
        int total = board.getControlledTilesCount(playerId);
        if (aligned >= rules->getNumberOfAlignedTilesToWin() || total >= rules->getNumberOfStoneTiles()) {
            std::cout << " Le joueur " << playerId << " a gagné la partie !" << std::endl;
            return true;
        }
    }
    return false;
}
void GameLogic::printOption(string option){
    Display* c=DisplayManager::getInstance();
    int remainder=CONSOLE_WIDTH-option.size();
    if(remainder%2==0){
        string out="#"+string(remainder/2-1,' ')+option+string(remainder/2-1,' ')+"#\n";
        c->output(out);
    }
    else if (remainder%2!=0){
        string out="#"+string(remainder/2,' ')+option+string(remainder/2-1,' ')+"#\n";
        c->output(out);
    }
}
void GameLogic::printWithColor(string option, string color="red")
{
    Display *c=DisplayManager::getInstance();
    string colorCode;

    if (color == "red")        colorCode = "\033[31m";
    else if (color == "green") colorCode = "\033[32m";
    else if (color == "yellow")colorCode = "\033[33m";
    else if (color == "blue")  colorCode = "\033[34m";
    else if (color == "magenta")colorCode = "\033[35m";
    else if (color == "cyan")  colorCode = "\033[36m";
    else if (color == "white") colorCode = "\033[37m";

    string colored = colorCode + option + "\033[0m";
    int remainder = CONSOLE_WIDTH - option.size();

    string line;
    if (remainder % 2 == 0) {
        line = "#" + string(remainder / 2 - 1, ' ') + colored + string(remainder / 2 - 1, ' ') + "#\n";
    } else {
        line = "#" + string(remainder / 2, ' ') + colored + string(remainder / 2 - 1, ' ') + "#\n";
    }

    c->output(line);
}
void GameLogic::getFreespace(int i)
{
    Display* c=DisplayManager::getInstance();
    string stars=string(CONSOLE_WIDTH,'#')+"\n";
    string freespace="#"+string(getRemainder(stars,3),' ')+"#\n";
    for(int j=0;j<i;j++){
        c->output(freespace);
    }
}

void GameLogic::mainDisplay(){
    Display *c=DisplayManager::getInstance();
    string stars=string(CONSOLE_WIDTH,'#')+"\n";
    string freespace="#"+string(getRemainder(stars,3),' ')+"#\n";
    c->output(stars);
    c->output(freespace);
    string logo1= R"(
  ███████╗ ██████╗██╗  ██╗ ██████╗ ████████╗████████╗███████╗███╗   ██╗
  ██╔════╝██╔════╝██║  ██║██╔═══██╗╚══██╔══╝╚══██╔══╝██╔════╝████╗  ██║
  ███████╗██║     ███████║██║   ██║   ██║      ██║   █████╗  ██╔██╗ ██║
  ╚════██║██║     ██╔══██║██║   ██║   ██║      ██║   ██╔══╝  ██║╚██╗██║
  ███████║╚██████╗██║  ██║╚██████╔╝   ██║      ██║   ███████╗██║ ╚████║
  ╚══════╝ ╚═════╝╚═╝  ╚═╝ ╚═════╝    ╚═╝      ╚═╝   ╚══════╝╚═╝  ╚═══╝
)";
  string logo2=R"(
  ████████╗ ██████╗ ████████╗████████╗███████╗███╗   ██╗
  ╚══██╔══╝██╔═══██╗╚══██╔══╝╚══██╔══╝██╔════╝████╗  ██║
     ██║   ██║   ██║   ██║      ██║   █████╗  ██╔██╗ ██║
     ██║   ██║   ██║   ██║      ██║   ██╔══╝  ██║╚██╗██║
     ██║   ╚██████╔╝   ██║      ██║   ███████╗██║ ╚████║
     ╚═╝    ╚═════╝    ╚═╝      ╚═╝   ╚══════╝╚═╝  ╚═══╝
)";
  istringstream iss(logo1.substr(1));
  string firstLinel1;
  while(getline(iss,firstLinel1)){;
  int spacel1=getRemainder(stars,getUTF8size(firstLinel1))-2;
  string printl1;
  if(spacel1%2!=0){
    printl1="#"+string((spacel1/2),' ')+firstLinel1+string((spacel1/2)-1,' ')+"#";}
    else{printl1="#"+string((spacel1/2),' ')+firstLinel1+string((spacel1/2)-2,' ')+"#";}
    c->output(printl1);
    c->output("\n");}
    istringstream iss2(logo2.substr(1));
    string firstlinel2;
    while(getline(iss2,firstlinel2)){;
  int spacel2=getRemainder(stars,getUTF8size(firstlinel2))-2;
    string printl2;
  if(spacel2%2!=0){
    printl2="#"+string((spacel2/2),' ')+firstlinel2+string((spacel2/2)-1,' ')+"#";}
    else{printl2="#"+string((spacel2/2),' ')+firstlinel2+string((spacel2/2)-2,' ')+"#";}
    c->output(printl2);
    c->output("\n");}
    c->output(freespace);
    c->output(freespace);
    printLoading();
    c->output(freespace);
    c->output(stars);


}
void GameLogic::getChoiceRoundLoading(int i){
    Display* d= DisplayManager::getInstance();
    string start="Starting round number "+to_string(i)+".";
    printStars();
    getFreespace(7);
    printOption(start);
    getFreespace(4);
    printLoading();
    getFreespace(4);
    printStars();
}
void GameLogic::fillWithDashes(string text) {
    Display* c=DisplayManager::getInstance();
    int spaceForDashes=CONSOLE_WIDTH-text.size();
    string Dashes="";
    if(spaceForDashes%2==0){
        Dashes="#  "+string(spaceForDashes/2-3,'-')+text+string(spaceForDashes/2-3,'-')+"  #\n";
    }
    else if(spaceForDashes%2!=0){
        Dashes="#  "+string(spaceForDashes/2-2,'-')+text+string(spaceForDashes/2-3,'-')+"  #\n";
    }
    c->output(Dashes);
}

void GameLogic::getChoiceMain()
{
    Display* c=DisplayManager::getInstance();
    string Projet = "Welcome to the SchottenTotten game. (Console Edition)";
    string Projet2="Created by M. Hachelef, A. Elhatri, Y. Atouf";
    string Option1 = "Enter 0 to quit the game.";
    string Option2 = "Enter 1 to start the game.";
    string Option3 = "Enter 2 to get more information about this program.";
    printStars();
    getFreespace(3);
    printOption(Projet);
    printOption(Projet2);
    getFreespace(4);
    printOption(Option1);
    getFreespace(1);
    printOption(Option2);
    getFreespace(1);
    printOption(Option3);
    getFreespace(3);
    printStars();
}
void GameLogic::getReturn(){
    string returnback="Enter -1 to return to previous menu";
    printWithColor(returnback,"red");
}
void GameLogic::getChoiceStart(){
    string rounds="How many rounds of Schotten Totten do you wish to play?";
    printStars();
    getFreespace(7);
    printOption(rounds);
    getFreespace(4);
    getReturn();
    getFreespace(4);
    printStars();
}
void GameLogic::getChoiceInfo()
{
    string info="Schotten Totten game Project version 1.0. Created by M. Hachelef, A. Elhatri, Y. Atouf.";
    string license="Project available on https://github.com/ZTOUF/SchottenTotten_CPP under GNU license.";
    string supervision="Project supervised by Professors M. Tom Ray and M. Ronan Bocquillon.";
    string moreinfo="This console game is the digital version of the Schotten Totten game created by Reiner Knizia.";
    printStars();
    getFreespace(2);
    printOption(info);
    getFreespace(2);
    printOption(license);
    getFreespace(2);
    printOption(supervision);
    getFreespace(2);
    printOption(moreinfo);
    getFreespace(2);
    getReturn();
    getFreespace(2);
    printStars();
}
void GameLogic::getSleep(int timeToSleep)
{
#ifdef _WIN32
    Sleep(timeToSleep * 1000);  // Convert to milliseconds
#else
    usleep(timeToSleep*1000000);         // Already in seconds
#endif
}
void GameLogic::getMainConsole() {
    string inputString;
    int currentRound=0;
    int maxRounds=1;
    int iMenu=(-1);
    int Player1Wins=0;
    int Player2Wins=0;
    string sError;
    Display *c=DisplayManager::getInstance();
    while (iMenu!=0) {
        clearScreen();
        if (iMenu==(-1)) {
            mainDisplay();
            getSleep();
            iMenu=1;
            sError.clear();
        }
        if (iMenu==1) {
            getChoiceMain();
            c->output(">> ");
            cin>>inputString;
            if (inputString=="0") {
                iMenu=0;
                sError.clear();
            }
            else if (inputString=="1") {
                iMenu=2;
                sError.clear();
            }
            else if (inputString=="2") {
                iMenu=3;
                sError.clear();
            }
            else {
                sError="Error, option '"+inputString+"' does not exist. Please choose a valid option.";
            }
        }
        else if (iMenu==2) {
            getChoiceStart();
            c->output(">> ");
            cin>>inputString;
            if (inputString=="0") {
                iMenu=0;
                sError.clear();
            }
            else if (inputString=="-1") {
                iMenu=1;
                sError.clear();
            }
            else {
                try {
                    maxRounds=stoi(inputString);
                    if (maxRounds<=0) {
                        throw(invalid_argument("Invalid input"));
                    }
                    sError.clear();
                    iMenu=4;
                }
                catch (...) {
                    sError="Invalid, input '"+inputString+"'. Please enter a valid number of rounds.";
                }
            }
        }
        else if (iMenu==3) {
            getChoiceInfo();
            c->output(">> ");
            cin>>inputString;
            if (inputString=="0") {
                iMenu=0;
                sError.clear();
            }
            else if (inputString=="-1") {
                iMenu=1;
                sError.clear();
            }
            else {
                sError="Invalid input '"+inputString+"'. Please enter a valid option.";
            }
        }
        else if (iMenu==4) {
            while (currentRound<maxRounds) {
                getChoiceRoundLoading(currentRound);

            }
        }
        c->output(sError+"\n");
    }
}






