#include "Rules.h"

Rules* Rules::instance = nullptr;

Rules::Rules()
    : numberOfStoneTiles(9),
      numberOfAlignedTilesToWin(3),
      numberOfUnalignedTilesToWin(5) {}

Rules::Rules(const Rules::Builder& builder)
    : numberOfStoneTiles(builder.numberOfStoneTiles),
      numberOfAlignedTilesToWin(builder.numberOfAlignedTilesToWin),
      numberOfUnalignedTilesToWin(builder.numberOfUnalignedTilesToWin),
      clanCardsByColor(builder.clanCardsByColor),
      tacticalCards(builder.tacticalCards) {}

Rules* Rules::getInstance() {
    if (!instance) {
        instance = new Rules();
    }
    return instance;
}

void Rules::buildInstance(const Rules::Builder& builder) {
    if (instance) {
        delete instance;
    }
    instance = new Rules(builder);
}