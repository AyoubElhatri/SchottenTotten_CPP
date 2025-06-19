#include "GameBoard.h"
#include <stdexcept>
#include <utility> // pour std::move
#include "../Rules/Rules.h"
#include "../Factory/TacticalCardsFactory.h"
#include "../Display/DisplayManager.h"
#include <regex>
#include <iomanip>
#include <string>
#include <algorithm>
#include "../Logic/GameLogic.h"
std::unique_ptr<GameBoard> GameBoard::instance = nullptr;

void GameBoard::deleteInstance()
{   if (instance!=nullptr)
        instance.reset();
}

GameBoard::GameBoard() {

    for (int i = 0; i < Rules::getInstance()->getNumberOfStoneTiles(); ++i) {
        sharedTiles.push_back(std::make_shared<StoneTiles>(i));
    }
    unordered_map<Colors, unsigned int> ClanCardsByColor = Rules::getInstance()->getClanCardsByColor();
    for (const auto &[color, count]: ClanCardsByColor) {
        for (unsigned int i = 1; i <= count; ++i) {
            RemainingClanCards.addCard(std::move(std::make_unique<ClanCards>(i, color)));
        }
    }
    unordered_map<string, unsigned int> TacticalCards = Rules::getInstance()->getTacticalCards();
    for (const auto &[name, count]: TacticalCards) {
        for (unsigned int i = 0; i < count; ++i) {
            RemainingTacticalCards.addCard(TacticalCardsFactory::createTacticalCard(name));
        }
    }
    RemainingClanCards.mixSet();
    RemainingTacticalCards.mixSet();
}


GameBoard& GameBoard::getInstance() {
    if (!instance) {
        instance = std::unique_ptr<GameBoard>(new GameBoard());
    }
    return *instance;
}


std::shared_ptr<StoneTiles> GameBoard::findTileByPosition(unsigned int position) {
    for (auto& tile : sharedTiles) {
        if (tile->getPosition() == position) {
            return tile;
        }
    }
    return nullptr;
}


const std::vector<std::shared_ptr<StoneTiles>>& GameBoard::getSharedTiles() const {
    return sharedTiles;
}


Set& GameBoard::getRemainingClanCards() {
    return RemainingClanCards;
}

Set& GameBoard::getRemainingTacticalCards() {
    return RemainingTacticalCards;
}

Set& GameBoard::getDiscardedCards() {
    return DiscardedCards;
}
void GameBoard::placeCardOnTileByIndexOfTheTile(int tileIndex, const Cards& card, int playerId) {
    if (tileIndex < 0 || tileIndex >= getBoardSize()) {
        throw std::invalid_argument("Tile index '"+to_string(tileIndex)+" is out of bounds. Please enter a correct tile index.");
    }

    auto& tile = getSharedTiles()[tileIndex];
    auto& playerDeck = CGameLogic::getInstance().getPlayerById(playerId)->getPlayerDeck();


    tile->addCardOnTilesOfPlayer(playerId, card.getName(), playerDeck);

    string message=" Joueur " + to_string(playerId) + " joue la carte : " + card.getName() + " sur la tuile " + to_string(tileIndex);
}

bool GameBoard::isTileFree(int tileIndex) const {
    return !getSharedTiles()[tileIndex]->isAlreadyClaimed();
}

int GameBoard::getControlledTilesCount(int playerId) const {
    int count = 0;
    for (const auto& tile : sharedTiles) {
        if (tile->isAlreadyClaimed() && tile->getClaimedBy() == playerId) {
            ++count;
        }
    }
    return count;
}

int GameBoard::getAlingnedControlledTilesCount(int playerId) const {
    int maxStreak = 0;
    int currentStreak = 0;
    for (const auto& tile : sharedTiles) {
        if (tile->isAlreadyClaimed() && tile->getClaimedBy() == playerId) {
            currentStreak++;
            maxStreak = std::max(maxStreak, currentStreak);
        }
        else {
            currentStreak = 0;
        }
    }
    return maxStreak;
}



string GameBoard::formatCard(const Cards *card) {
    if (auto tacticalCard = dynamic_cast<const TacticalCards*>(card)) {
        return "[" + tacticalCard->getName() + "]";
    }

    if (auto clanCard = dynamic_cast<const ClanCards*>(card)) {
        std::string colorCode;
        switch (clanCard->getColor()) {
            case Colors::Red:     colorCode = RED; break;
            case Colors::Green:   colorCode = GREEN; break;
            case Colors::Blue:    colorCode = BLUE; break;
            case Colors::Yellow:  colorCode = YELLOW; break;
            case Colors::Magenta: colorCode = MAGENTA; break;
            case Colors::Cyan:    colorCode = CYAN; break;
            default:              colorCode = RESET;
        }
        return colorCode + "[" + to_string(clanCard->getNumber()) + "]" + RESET;
    }

    return "[?]";
}




