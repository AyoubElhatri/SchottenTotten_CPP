//
// Created by P Utilisateur on 18/06/2025.
//

#include "GameLogic2.h"

#include "../Display/DisplayConsole.h"
#include "../GameBoard/GameBoard.h"
#include"../Cards/Recruiter.h"
#include"../Display/DisplayManager.h"
#include "../Player/Human.h"
#include"../Player/Player.h"
#include "../Player/AIEasy.h"


std::unique_ptr<CGameLogic> CGameLogic::instance = nullptr;

CGameLogic ::CGameLogic() {
    turnNumber= 0;
    Player* player1 = new Human(1);
    Player* player2 = new AIEasy(2);

    addPlayer(std::unique_ptr<Player>(player1));
    addPlayer(std::unique_ptr<Player>(player2));
}
void CGameLogic::deleteInstance() {
    instance=nullptr;
}
void CGameLogic::printBoardalpha2() {
    const std::string blue = "\033[1;34m";
    const std::string red = "\033[1;31m";
    const std::string reset = "\033[0m";

    printStars();
    getFreespace(5);

    vector<shared_ptr<StoneTiles>> sharedTiles=GameBoard::getInstance().getSharedTiles();
    const int tileCount = static_cast<int>(sharedTiles.size());
    const int cardWidth = 7;
    const std::string spacer = "   ";



    // --- Pour chaque joueur (1 et 2) ---
    for (unsigned int playerId = 1; playerId <= 2; ++playerId) {
        // Trouver le nombre maximum de cartes pour ce joueur
        int maxCards = 0;
        for (const auto& tile : sharedTiles) {
            const auto& playerCards = tile->getPlayerCardsOnTilesByPlayerId(playerId).getRawCards();
            maxCards = std::max(maxCards, static_cast<int>(playerCards.size()));
        }

        // Afficher les cartes pour ce joueur
        for (int row = 0; row < maxCards; ++row) {
            string line=" ";
            for (int i = 0; i < tileCount; ++i) {
                const auto& cards = sharedTiles[i]->getPlayerCardsOnTilesByPlayerId(playerId).getRawCards();
                if (row < static_cast<int>(cards.size())) {
                    line+="  "+GameBoard::getInstance().formatCard(cards[row])+"     ";
                } else {
                    line+="          ";
                }

            }
            printClean(line);
            line=" ";
        }

        // Après le joueur 1, afficher la ligne de séparation des tuiles
        if (playerId == 1) {
            std::string tileStr=" ";
            string combat="";
            int which=-1;
            for (int i = 0; i < tileCount; ++i) {

                if (sharedTiles[i]->isAlreadyClaimed()) {
                    tileStr += red + "[XXXX]" + reset+"    ";
                } else if (sharedTiles[i]->getCombatModeCards().getSize()!=0) {
                    if (sharedTiles[i]->getCombatModeCards().getSize()==1)
                    {
                        tileStr+=sharedTiles[i]->getCombatModeCards().getCardAt(0)->getName()+"  ";
                    }
                    else if (sharedTiles[i]->getCombatModeCards().getSize()>1)
                    {
                        combat=string(getClean(tileStr).size(),' ')+sharedTiles[i]->getCombatModeCards().getCardAt(0)->getName()+"  ";
                        printClean(combat+string(80,' '));
                        which=i;
                        tileStr+="          ";
                    }
                }
                else{
                    tileStr+="--ST"+to_string(i)+"--   ";
                }
            }

            printClean(tileStr);
            if (which!=-1)
            {
                combat=combat.substr(0,combat.size()-10);
                combat+=sharedTiles[which]->getCombatModeCards().getCardAt(1)->getName()+" ";
                printClean(combat+string(80,' '));
            }
        }
    }
    string claimed="Claimed Tiles: ";
    string tilec="";
    for (size_t i = 0; i < sharedTiles.size(); ++i) {
        if (sharedTiles[i]->isAlreadyClaimed()) {
            tilec+=(" StoneTile " + std::to_string(i) +
                " : Player " + std::to_string(sharedTiles[i]->getClaimedBy()));
        }

    }
    if (tilec.size()>=98)
    {
        size_t pos=tilec.rfind('B',98);
        string tilec1=tilec.substr(0,pos);
        string tilec2=tilec.substr(pos);
        printOption(tilec1);
        printOption(tilec2);

    }
    else
    {
        printOption(tilec);
    }
    getFreespace();
    string dc="Discarded Cards: ";
    int iter=GameBoard::getInstance().getDiscardedCards().getSize();
    if (iter!=0)
    {
        for (int j=0;j<iter;j++)
        {
            dc +=GameBoard::getInstance().formatCard(GameBoard::getInstance().getDiscardedCards().getRawCards()[j])+" ";

        }
        if (dc.size()>=98)
        {
            size_t pos1=dc.rfind(' ',96);
            string dc1=dc.substr(0,pos1);
            string dc2=dc.substr(pos1);
            printClean(dc1);
            printClean(dc2);
        }
         else{   printClean(dc);
        }
    }
    getFreespace(4);
    string info="ST[*]: Stone Tile n=* ";
    printInLast(info);
    printStars();

}
/*
void CGameLogic::printBoardalpha() {
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
}*/
void CGameLogic::printInLast(string Text)
{
    int space=100-Text.size();
    string toprint="#"+string(space-2,' ')+Text+"#\n";
    DisplayManager::getInstance()->output(toprint);
}





CGameLogic &CGameLogic::getInstance() {
    if (instance == nullptr) {
        instance = unique_ptr<CGameLogic>(new CGameLogic());
    }
    return *instance;
}
void CGameLogic::clearScreen() {
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

void CGameLogic::addPlayer(std::unique_ptr<Player> player) {
    players.push_back(std::move(player));
}

void CGameLogic::initializePlayerDecks() {
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
void CGameLogic::PlayerVictory(int i){
    string p1="Player "+to_string(i)+" wins this round.";
    string p2;
    if(i==1) p2="Player 2 loses this round.";
    else p2="Player 1 loses this round.";
    printStars();
    getFreespace(7);
    printWithColor(p1,"green");
    getFreespace(4);
    printWithColor(p2,"red");
    getFreespace(4);
    printStars();
}
void CGameLogic::PlayerRounds(){
    if (Player1Wins>Player2Wins) {
        string p1="Player "+to_string(1)+" won "+to_string(Player1Wins)+" rounds.";
        string p2="Player "+to_string(2)+" won "+to_string(Player2Wins)+" rounds.";
        string p3="Player 1 is the final Winner!";
        printStars();
        getFreespace(3);
        printWithColor(p1,"green");
        getFreespace(4);
        printWithColor(p2,"red");
        getFreespace(4);
        printWithColor(p3,"green");
        getFreespace(4);
        printStars();
    }
    else if (Player1Wins<Player2Wins) {
        string p1="Player "+to_string(2)+" won "+to_string(Player2Wins)+" rounds.";
        string p2="Player "+to_string(1)+" won "+to_string(Player1Wins)+" rounds.";
        string p3="Player 2 is the final Winner!";
        printStars();
        getFreespace(3);
        printWithColor(p1,"green");
        getFreespace(4);
        printWithColor(p2,"red");
        getFreespace(4);
        printWithColor(p3,"green");
        getFreespace(4);
        printStars();
    }
    else if (Player1Wins=Player2Wins) {
        string p2="It's a tie! Both players won "+to_string(Player1Wins);
        string p3="Congratulations to both of the players!";
        printStars();
        getFreespace(7);
        printWithColor(p2,"green");
        getFreespace(4);
        printWithColor(p3,"green");
        getFreespace(4);
        printStars();
    }
}

void CGameLogic::printLoading() {
    string loading="LOADING...";
    printWithColor(loading,"green");
}
string CGameLogic::getClean(string text)
{
    static const std::regex ansiRegex("\x1B\\[[0-9;]*[A-Za-z]");
    return regex_replace(text, ansiRegex, "");
}
void CGameLogic::printClean(string text)
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


void CGameLogic::startGame() {
    clearScreen();
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
void CGameLogic::runGameLoop() {
    clearScreen();


    while (!checkWinner()) {
        Player* currentPlayer = players[getCurrentPlayerIndex()].get();

        printBoardalpha2();

        try {
            currentPlayer->playTurn();
        } catch (const std::exception& e) {
            clearScreen();
            DisplayManager::getInstance()->output(string(e.what()) + "\n");
            continue;
        }
        turnNumber++;

    }

}    //No stress c'est moi
/*void CGameLogic::runGameLoop() {
    clearScreen();

    while (true) {
        Player* currentPlayer = players[getCurrentPlayerIndex()].get();

        printBoardalpha2();

        try {
            currentPlayer->playTurn();
        } catch (const std::exception& e) {
            clearScreen();
            DisplayManager::getInstance()->output(string(e.what()) + "\n");
            continue;
        }


        if (checkWinner()) break;

        turnNumber++;
    }
}*/
void CGameLogic::printStars()
{   Display *c=DisplayManager::getInstance();
    string stars=string(CONSOLE_WIDTH,'#')+"\n";
    c->output(stars);
}

bool CGameLogic::checkWinner()
{
    auto * rules = Rules::getInstance();
    const auto alignedToWin = rules->getNumberOfAlignedTilesToWin();
    const auto unalignedToWin = rules->getNumberOfUnalignedTilesToWin();

    GameBoard& board = GameBoard::getInstance();
    for (int playerId = 1; playerId < 3; playerId++) {
        int aligned = board.getAlingnedControlledTilesCount(playerId);
        int total = board.getControlledTilesCount(playerId);
        if (aligned >= rules->getNumberOfAlignedTilesToWin() || total >= rules->getNumberOfStoneTiles()) {
            std::cout << " Player " << playerId << " won the game !" << std::endl;
            if (playerId==1)Player1Wins+=1;
            else Player2Wins+=1;
            PlayerVictory(playerId);
            getSleep(4);
            return true;
        }
    }
    return false;
}
void CGameLogic::printOption(string option){
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
void CGameLogic::printWithColor(string option, string color="red")
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
void CGameLogic::getFreespace(int i)
{
    Display* c=DisplayManager::getInstance();
    string stars=string(CONSOLE_WIDTH,'#')+"\n";
    string freespace="#"+string(getRemainder(stars,3),' ')+"#\n";
    for(int j=0;j<i;j++){
        c->output(freespace);
    }
}

void CGameLogic::mainDisplay(){
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
void CGameLogic::getChoiceRoundLoading(int i){
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
void CGameLogic::fillWithDashes(string text) {
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

void CGameLogic::getChoiceMain()
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
void CGameLogic::getReturn(){
    string returnback="Enter -1 to return to previous menu";
    printWithColor(returnback,"red");
}
void CGameLogic::getChoiceStart(){
    string rounds="How many rounds of Schotten Totten do you wish to play?";
    printStars();
    getFreespace(7);
    printOption(rounds);
    getFreespace(4);
    getReturn();
    getFreespace(4);
    printStars();
}
void CGameLogic::getChoiceInfo()
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
void CGameLogic::getSleep(int timeToSleep)
{
#ifdef _WIN32
    this_thread::sleep_for(chrono::seconds(timeToSleep));  // Convert to milliseconds
#else
    usleep(timeToSleep*1000000);         // Already in seconds
#endif
}
void CGameLogic::getMainConsole() {
    string inputString;
    int currentRound=0;
    int maxRounds=1;
    int iMenu=(-1);
    Player1Wins=0;
    Player2Wins=0;
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
                getSleep(3);
                clearScreen();
                startGame();
                currentRound+=1;
                CGameLogic::deleteInstance();
                GameBoard::deleteInstance();
            }
            PlayerRounds();
            getSleep(4);
            iMenu=1;
            sError.clear();
        }
        c->output(sError+"\n");
    }
}






