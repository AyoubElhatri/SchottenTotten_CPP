#include "Rules.h"
#include <memory>
#include <unordered_map>


Rules::Rules() : numberofStoneTiles(9), numberOfClanCardsPerColor(6), numberOfAlignedTilesToWin(3), numberOfUnalignedTilesToWin(5), numberOfPlayer(2) {}






/*Rules& Rules::getInstance() {
    if (!instance) {
        throw runtime_error("Rules has not been built yet. Call buildInstance() first.");
    }
    return *instance;
}*/