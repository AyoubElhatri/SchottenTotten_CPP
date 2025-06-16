#ifndef CARDS_H
#define CARDS_H
#include "../Colors.h"
#include <memory>
using namespace std;
#include "../DisplayManager.h"
#include "../CustomException/CustomException.h"
#include <string>
class StoneTiles;

class Cards {
protected:
    string cardName="aaaa";
    public:
    virtual ~Cards() = default;
    string getName() const {return cardName;}
    //virtual unsigned int getNumber() const = 0;
       // virtual Colors getColor() const = 0;
       // virtual std::unique_ptr<Cards> clone() const = 0;
        virtual void getEvent(StoneTiles* stoneTiles)=0;

};



#endif //CARDS_H
