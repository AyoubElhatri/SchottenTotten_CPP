#include "TacticalCards.h"

TacticalCards::TacticalCards() {}

TacticalCards::~TacticalCards() {}

Colors TacticalCards::getColor() const {
    // Retourne une couleur neutre par défaut ou lève une exception
    return Colors::Red;
}