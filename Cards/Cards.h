#ifndef CARDS_H
#define CARDS_H
#include "../Colors.h"



class Cards {
    public:
    virtual ~Cards() = default;

    virtual unsigned int getNumber() const = 0;
        virtual Colors getColor() const = 0;
        virtual std::unique_ptr<Cards> clone() const = 0;
        virtual void getEvent()=0;
};



#endif //CARDS_H
