#include "Rules.h"

// Définit la variable statique
unique_ptr<Rules> Rules::instance = nullptr;

Rules::Rules()
    : numberOfStoneTiles(9), numberOfAlignedTilesToWin(3), numberOfUnalignedTilesToWin(5) {}

Rules::Rules(const Builder& builder)
    : numberOfStoneTiles(builder.rules->numberOfStoneTiles),
      numberOfAlignedTilesToWin(builder.rules->numberOfAlignedTilesToWin),
      numberOfUnalignedTilesToWin(builder.rules->numberOfUnalignedTilesToWin),
      clanCardsByColor(builder.rules->clanCardsByColor),
      tacticalCards(builder.rules->tacticalCards) {}

Rules& Rules::getInstance() {
    if (!instance) {
        instance=new Rules();
    }
    return *instance;
}

void Rules::buildInstance(const Builder& builder) {
    instance = make_unique<Rules>(builder);
}

Rules::Builder& Rules::Builder::addClanCardColor(const string& color, unsigned int count) {
    rules->clanCardsByColor[color] = count;
    return *this;
}

Rules::Builder& Rules::Builder::addTacticalCard(const string& name, unsigned int count) {
    rules->tacticalCards[name] = count;
    return *this;
}