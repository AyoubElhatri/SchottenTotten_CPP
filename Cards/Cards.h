#ifndef CARDS_H
#define CARDS_H
#include "../Colors.h"
#include <memory>
using namespace std;
#include "../Display/DisplayManager.h"
#include <string>
class StoneTiles;

class Cards {
protected:
    string cardName;

    public:
    virtual ~Cards() = default;
    string getName() const {return cardName;}
    virtual void getEvent(StoneTiles* stoneTiles)=0;

};



#endif //CARDS_H
