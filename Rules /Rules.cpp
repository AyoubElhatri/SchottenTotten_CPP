#include "Rules.h"
using namespace std;
#include <memory>
#include <unordered_map>



Rules& Rules::getInstance() {
    if (!instance) {
        throw runtime_error("Rules has not been built yet. Call buildInstance() first.");
    }
    return *instance;
}


void Rules::buildInstance(const Builder& builder) {
    if (!instance) {
        instance = unique_ptr<Rules>(new Rules(builder));
    } else {
        throw runtime_error("Rules has already been built.");
    }
}

