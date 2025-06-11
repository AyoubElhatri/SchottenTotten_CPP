#include"Human.h"
#include"../GameBoard.h"

void Human::playCard(std::unique_ptr<Cards> /*unused*/) {
    if (getPlayerDeck().getSize() == 0) {
        std::cout << "You have no cards to play." << std::endl;
        return;
    }

    std::cout << "Your hand:" << std::endl;
    for (unsigned int i = 0; i < getPlayerDeck().getSize(); ++i) {
        std::cout << i << ": [Card]" << std::endl; // Remplace [Card] par une description réelle si tu veux
    }

    unsigned int cardIndex;
    std::cout << "Choose the index of the card to play: ";
    std::cin >> cardIndex;

    if (cardIndex >= getPlayerDeck().getSize()) {
        std::cout << "Invalid card index." << std::endl;
        return;
    }

    std::unique_ptr<Cards> selectedCard = getPlayerDeck().getCardbyIndex(cardIndex);

    int tileIndex;
    std::cout << "Enter the tile position to place your card: ";
    std::cin >> tileIndex;

    GameBoard& gameBoard = GameBoard::getInstance();

    try {
        gameBoard.placeCardOnTile(tileIndex, *selectedCard, getPlayerID());
        std::cout << "Card placed on tile " << tileIndex << "." << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Error placing card: " << e.what() << std::endl;
        // On remet la carte dans la main du joueur en déplaçant la possession
        getPlayerDeck().addCard(std::move(selectedCard));
    }
}