#include "GameBoard.h"
#include <stdexcept>
#include <utility> // pour std::move
#include "Rules/Rules.h"
#include "TacticalCardsFactory.h"
// Initialisation du singleton
std::unique_ptr<GameBoard> GameBoard::instance = nullptr;

// Constructeur privé
GameBoard::GameBoard() {
    // Initialisation de 9 tuiles partagée
    cout<<"Initialisation du plateau de jeu avec " << Rules::getInstance()->getNumberOfStoneTiles() << " tuiles." << endl;
    for (int i = 0; i < Rules::getInstance()->getNumberOfStoneTiles(); ++i) {
        sharedTiles.push_back(std::make_shared<StoneTiles>(i));
    }
    unordered_map<Colors, unsigned int> ClanCardsByColor = Rules::getInstance()->getClanCardsByColor();
    for (const auto& [color, count] : ClanCardsByColor) {
        for (unsigned int i = 1; i <= count; ++i) {
            RemainingClanCards.addCard(std::move(std::make_unique<ClanCards>(i, color)));
        }
    }

    unordered_map<string, unsigned int> TacticalCards = Rules::getInstance()->getTacticalCards();
    for (const auto& [name, count] : TacticalCards) {
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
const Set& GameBoard::getRemainingClanCards() const {
    return RemainingClanCards;
}

const Set& GameBoard::getRemainingTacticalCards() const {
    return RemainingTacticalCards;
}

const Set& GameBoard::getDiscardedCards() const {
    return DiscardedCards;
}


std::unique_ptr<Cards> GameBoard::drawClanCard() {
    return nullptr;  //exemple temporaire
}


void GameBoard::placeCardOnTile(int tileIndex, const Cards& card, int playerId) {
    //temporaire
}

bool GameBoard::isTileFree(int tileIndex) const {
    return true; // À adapter
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

/*
void GameBoard::moveCardBetweenBorders(unsigned int fromBorderPos, unsigned int toBorderPos, unsigned int playerId, unsigned int cardIndex) {
    auto fromTile = findTileByPosition(fromBorderPos);
    auto toTile = findTileByPosition(toBorderPos);
    if (!fromTile || !toTile) {
        throw std::runtime_error("Position de tuile invalide");
    }

    auto card = fromTile->removeCardFromPlayer(playerId, cardIndex);

    if (!card) {
        throw std::runtime_error("Carte introuvable sur la tuile source");
    }

    toTile->addCardToPlayer(playerId, std::move(card), fromTile->getPlayerCards1()); // Utiliser la provenance de la carte
}*/