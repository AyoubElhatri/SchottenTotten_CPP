#include "GameBoard.h"
#include <stdexcept>
#include <utility> // pour std::move
#include "../Rules/Rules.h"
#include "../Factory/TacticalCardsFactory.h"
#include "../Logic/GameLogic.h"
#include "../Display/DisplayManager.h"
#include <regex>
#include <iomanip>
#include <string>
#include <algorithm>

std::unique_ptr<GameBoard> GameBoard::instance = nullptr;


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

// Récupération de l’instance singleton
GameBoard& GameBoard::getInstance() {
    if (!instance) {
        instance = std::unique_ptr<GameBoard>(new GameBoard());
    }
    return *instance;
}

// Récupérer une tuile par position
std::shared_ptr<StoneTiles> GameBoard::findTileByPosition(unsigned int position) {
    for (auto& tile : sharedTiles) {
        if (tile->getPosition() == position) {
            return tile;
        }
    }
    return nullptr;
}

// Accès aux tuiles partagées
const std::vector<std::shared_ptr<StoneTiles>>& GameBoard::getSharedTiles() const {
    return sharedTiles;
}

// Accès aux paquets restants / défausse
Set& GameBoard::getRemainingClanCards() {
    return RemainingClanCards;
}

Set& GameBoard::getRemainingTacticalCards() {
    return RemainingTacticalCards;
}

Set& GameBoard::getDiscardedCards() {
    return DiscardedCards;
}


// A MODIFIER SA GRAND MERE
void GameBoard::placeCardOnTileByIndexOfTheTile(int tileIndex, const Cards& card, int playerId) {
    if (tileIndex < 0 || tileIndex >= getBoardSize()) {
        throw std::out_of_range("Index de tuile invalide");
    }

    auto& tile = getSharedTiles()[tileIndex];
    auto& playerDeck = GameLogic::getInstance().getPlayerById(playerId)->getPlayerDeck();

    // Ajout de la carte sur la tuile
    tile->addCardOnTilesOfPlayer(playerId, card.getName(), playerDeck);

    string message="[DEBUG] Joueur " + to_string(playerId) + " joue la carte : " + card.getName() + " sur la tuile " + to_string(tileIndex);
}
// a enlever
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

#include <iomanip>  // Pour std::setw



void GameBoard::printBoard() {
    const std::string blue = "\033[1;34m";
    const std::string red = "\033[1;31m";
    const std::string reset = "\033[0m";

    // Affichage du titre ASCII art
    DisplayManager::getInstance()->output(
        "   ▄████████  ▄████████    ▄█    █▄     ▄██████▄      ███         ███        ▄████████ ███▄▄▄▄            ███      ▄██████▄      ███         ███        ▄████████ ███▄▄▄▄   \n"
        "  ███    ███ ███    ███   ███    ███   ███    ███ ▀█████████▄ ▀█████████▄   ███    ███ ███▀▀▀██▄      ▀█████████▄ ███    ███ ▀█████████▄ ▀█████████▄   ███    ███ ███▀▀▀██▄ \n"
        "  ███    █▀  ███    █▀    ███    ███   ███    ███    ▀███▀▀██    ▀███▀▀██   ███    █▀  ███   ███         ▀███▀▀██ ███    ███    ▀███▀▀██    ▀███▀▀██   ███    █▀  ███   ███ \n"
        "  ███        ███         ▄███▄▄▄▄███▄▄ ███    ███     ███   ▀     ███   ▀  ▄███▄▄▄     ███   ███          ███   ▀ ███    ███     ███   ▀     ███   ▀  ▄███▄▄▄     ███   ███ \n"
        "▀███████████ ███        ▀▀███▀▀▀▀███▀  ███    ███     ███         ███     ▀▀███▀▀▀     ███   ███          ███     ███    ███     ███         ███     ▀▀███▀▀▀     ███   ███ \n"
        "         ███ ███    █▄    ███    ███   ███    ███     ███         ███       ███    █▄  ███   ███          ███     ███    ███     ███         ███       ███    █▄  ███   ███ \n"
        "   ▄█    ███ ███    ███   ███    ███   ███    ███     ███         ███       ███    ███ ███   ███          ███     ███    ███     ███         ███       ███    ███ ███   ███ \n"
        " ▄████████▀  ████████▀    ███    █▀     ▀██████▀     ▄████▀      ▄████▀     ██████████  ▀█   █▀          ▄████▀    ▀██████▀     ▄████▀      ▄████▀     ██████████  ▀█   █▀  \n"
        "\n"
    );

    const int tileCount = static_cast<int>(sharedTiles.size());
    const int cardWidth = 7;
    const std::string spacer = "   ";

    auto stripAnsi = [](const std::string& s) {
        static const std::regex ansi_re("\033\\[[0-9;]*m");
        return std::regex_replace(s, ansi_re, "");
    };

    auto center = [&](const std::string& s) {
        std::string clean = stripAnsi(s);
        int padTotal = std::max(0, cardWidth - static_cast<int>(clean.size()));
        int padLeft = padTotal / 2;
        int padRight = padTotal - padLeft;
        return std::string(padLeft, ' ') + s + std::string(padRight, ' ');
    };

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
            std::string line;
            for (int i = 0; i < tileCount; ++i) {
                const auto& cards = sharedTiles[i]->getPlayerCardsOnTilesByPlayerId(playerId).getRawCards();
                if (row < static_cast<int>(cards.size())) {
                    line += center(formatCard(cards[row]));
                } else {
                    line += std::string(cardWidth, ' ');
                }
                if (i != tileCount - 1) line += spacer;
            }
            DisplayManager::getInstance()->output(line + "\n");
        }

        // Après le joueur 1, afficher la ligne de séparation des tuiles
        if (playerId == 1) {
            std::string tileLine;
            for (int i = 0; i < tileCount; ++i) {
                std::string tileStr;
                if (sharedTiles[i]->isAlreadyClaimed()) {
                    tileStr = red + "[XXXX]" + reset;
                } else {
                    tileStr = "-------";
                }
                tileLine += center(tileStr);
                if (i != tileCount - 1) tileLine += spacer;
            }
            DisplayManager::getInstance()->output(tileLine + "\n");
        }
    }

    // --- Index des tuiles ---
    std::string indexLine;
    for (int i = 0; i < tileCount; ++i) {
        indexLine += center(std::to_string(i));
        if (i != tileCount - 1) indexLine += spacer;
    }
    DisplayManager::getInstance()->output(indexLine + "\n\n");
}
/*
// Ajouter une carte à la défausse
void GameBoard::discardCard(unique_ptr<Cards> Card,) {
    DiscardedCards.addCard(std::move(copy));
}

// Poser une carte sur une tuile

void GameBoard::placeCardOnTile(int tileIndex, const Cards& card, int playerId) {
    if (tileIndex < 0 || tileIndex >= static_cast<int>(sharedTiles.size())) {
        throw std::out_of_range("Invalid tile index");
    }
    sharedTiles[tileIndex]->addCardToPlayer(playerId, card.clone());
}

// Piocher une carte clan
std::unique_ptr<Cards> GameBoard::drawClanCard() {
    if (RemainingClanCards.getSize() == 0)
        return nullptr;
    return RemainingClanCards.getCardbyIndex(0);
}

// Vérifier si une tuile est disponible
bool GameBoard::isTileFree(int index) const {
    if (index < 0 || index >= static_cast<int>(sharedTiles.size())) {
        return false;
    }
    return sharedTiles[index]->canPlaceCard();
}

// Récupérer les tuiles non encore revendiquées
const std::vector<std::shared_ptr<StoneTiles>>& GameBoard::getUnclaimedBorders() {
    unclaimedBorders.clear();
    for (auto& tile : sharedTiles) {
        if (!tile->isAlreadyClaimed()) {
            unclaimedBorders.push_back(tile);
        }
    }
    return unclaimedBorders;
}

// Déplacer une carte entre deux tuiles pour un joueur
*/

/*
void GameBoard::moveCardBetweenBorders(unsigned int fromBorderPos, unsigned int toBorderPos, unsigned int playerId, unsigned int cardIndex) {
    // Trouver les tuiles source et destination
    auto fromTile = findTileByPosition(fromBorderPos);
    auto toTile = findTileByPosition(toBorderPos);
    
    // Vérifier que les tuiles existent
    if (!fromTile || !toTile) {
        throw std::runtime_error("Position de tuile invalide");
    }

    // Vérifier que les tuiles ne sont pas revendiquées
    if (fromTile->isAlreadyClaimed() || toTile->isAlreadyClaimed()) {
        throw std::runtime_error("Une des tuiles est déjà revendiquée");
    }

    // Récupérer la carte à déplacer
    const Cards* cardToMove = fromTile->getPlayerCards(playerId).getCardAt(cardIndex);
    if (!cardToMove) {
        throw std::runtime_error("Carte introuvable sur la tuile source");
    }

    // Vérifier si la tuile de destination a de la place
    if (toTile->getPlayerCards(playerId).getSize() >= 3) {
        throw std::runtime_error("La tuile de destination est déjà pleine");
    }

    // Copier les informations de la carte
    std::string cardName = cardToMove->getName();
    
    // Retirer la carte de la tuile source
    fromTile->removeCardFromPlayer(playerId, cardIndex);

    // Ajouter la carte à la tuile de destination
    try {
        Set& playerDeck = getCurrentPlayer()->getPlayerDeck();
        toTile->addCardToPlayer(playerId, cardName, playerDeck);
    } catch (const std::exception& e) {
        // En cas d'erreur, annuler l'opération
        fromTile->addCardToPlayer(playerId, cardName, getCurrentPlayer()->getPlayerDeck());
        throw std::runtime_error("Échec du déplacement de la carte : " + std::string(e.what()));
    }
}
*/