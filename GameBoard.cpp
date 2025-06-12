#include "GameBoard.h"
#include <stdexcept>

unique_ptr<GameBoard> GameBoard::instance = nullptr;

std::shared_ptr<StoneTiles> GameBoard::findTileByPosition(unsigned int position) {
    for (auto& tile : sharedTiles) {
        if (tile->getPosition() == position) {
            return tile;
        }
    }
    return nullptr;
}

GameBoard& GameBoard::getInstance() {
    if (!instance) {
        instance = std::unique_ptr<GameBoard>(new GameBoard());
    }
    return *instance;
}

GameBoard::GameBoard() {
    // Initialize 9 shared stone tiles (or based on your game rules)
    for (int i = 0; i < 9; ++i) {
        sharedTiles.push_back(std::make_shared<StoneTiles>(i));
    }

}

const std::vector<std::shared_ptr<StoneTiles>>& GameBoard::getSharedTiles() const {
    return sharedTiles;
}

const Set& GameBoard::getRemainingClanCards() const {
    return RemainingClanCards;
}

const Set& GameBoard::getRemainingTacticalCards() const {
    return RemainingTacticalCards;
}

const Set& GameBoard::getDiscardedCards() const {
    return DiscardedCards;
}

void GameBoard::discardCard(const Cards& card) {
    auto copy = card.clone();
    DiscardedCards.addCard(copy);
}

bool GameBoard::placeCardOnTile(int tileIndex, const Cards &card, int playerId) {
    if (tileIndex < 0 || tileIndex >= static_cast<int>(sharedTiles.size())) {
        throw std::out_of_range("Invalid tile index");
    }
    sharedTiles[tileIndex]->addCardToPlayer(playerId,card.clone());
}

std::unique_ptr<Cards> GameBoard::drawClanCard() {
    if (RemainingClanCards.getSize() == 0)
        return nullptr;
    return RemainingClanCards.getCardbyIndex(0);
}

bool GameBoard::isTileFree(int index) const {
    if (index < 0 || index >= static_cast<int>(sharedTiles.size())) {
        return false; // index invalide
    }
    return sharedTiles[index]->canPlaceCard();
}

const std::vector<std::shared_ptr<StoneTiles>>& GameBoard::getUnclaimedBorders() const {
    std::vector<std::shared_ptr<StoneTiles>> unclaimed;
    for (auto& tile : sharedTiles) {
        if (!tile->isAlreadyClaimed()) {
            unclaimed.push_back(tile);
        }
    }
    return unclaimed;
}


void GameBoard::moveCardBetweenBorders(unsigned int fromBorderPos, unsigned int toBorderPos, unsigned int playerId, unsigned int cardIndex) {
    auto fromTile = findTileByPosition(fromBorderPos);
    auto toTile = findTileByPosition(toBorderPos);
    if (!fromTile || !toTile) {
        throw std::runtime_error("Position de tuile invalide");
    }

    // Supposons que StoneTiles a méthode pour retirer une carte du joueur
    auto card = fromTile->removeCardFromPlayer(playerId, cardIndex);

    if (!card) {
        throw std::runtime_error("Carte introuvable sur la tuile source");
    }

    toTile->addCardToPlayer(playerId, std::move(card));
}