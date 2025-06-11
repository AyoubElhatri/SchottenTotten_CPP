#ifndef CLANCARDS_H
#define CLANCARDS_H

#include <memory>

#include "../Colors.h"
#include "Cards.h"


enum class Colors;

class ClanCards: public Cards {
    private:
        unsigned int number;
		Colors color;
	public:
		unsigned int getNumber() const override {return number;};
		Colors getColor()const override {return color;};
		void setNumber(unsigned int numbers){number = numbers;};
		void setColor(Colors colors){color = colors;};
		std::unique_ptr<Cards> clone() const override{return std::make_unique<ClanCards>(*this);};

};



#endif //CLANCARDS_H
