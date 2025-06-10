#include "Rules.h"
#include <memory>
#include <unordered_map>



Rules::Rules() : numberOfStoneTiles(9), numberOfAlignedTilesToWin(3), numberOfUnalignedTilesToWin(5) {}



Rules& Rules::getInstance() {
    if (!instance) {
        throw runtime_error("Rules has not been built yet. Call buildInstance() first.");
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
