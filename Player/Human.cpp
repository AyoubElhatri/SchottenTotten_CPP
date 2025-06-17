#include"Human.h"
#include "../GameBoard/GameBoard.h"

void Human::playCard(std::unique_ptr<Cards> unused) {
    if (getPlayerDeck().getSize() == 0) {
        cout << "You have no cards to play." << std::endl;
        return;
    }

    cout << "Your hand:" << std::endl;
    for (unsigned int i = 0; i < getPlayerDeck().getSize(); ++i) {
        // Supposons que Cards ait une méthode toString()
        // std::cout << i << ": " << getPlayerDeck().getCardbyIndex(i)->toString() << std::endl;
        cout << i << ": [Card]" << endl;
    }

    unsigned int cardIndex;
    cout << "Choose the index of the card to play: ";
    cin >> cardIndex;

    if (cardIndex >= getPlayerDeck().getSize()) {
        cout << "Invalid card index." << endl;
        return;
    }

    unique_ptr<Cards> selectedCard = getPlayerDeck().getCardbyIndex(cardIndex);

    int tileIndex;
    cout << "Enter the tile position to place your card: ";
    cin >> tileIndex;

    GameBoard& gameBoard = GameBoard::getInstance();

    // Vérification supplémentaire
    if (tileIndex < 0 || tileIndex >= gameBoard.getBoardSize()) {
        cout << "Invalid tile index." << endl;
        // Remet la carte dans la main du joueur
        getPlayerDeck().addCard(std::move(selectedCard));
        return;
    }

    try {
        gameBoard.placeCardOnTile(tileIndex, *selectedCard, getPlayerID());
        cout << "Card placed on tile " << tileIndex << "." << endl;
    } catch (const std::exception& e) {
        cout << "Error placing card: " << e.what() << endl;
        // Remet la carte dans la main du joueur
        getPlayerDeck().addCard(std::move(selectedCard));
    }
}