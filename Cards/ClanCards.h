#ifndef CLANCARDS_H
#define CLANCARDS_H

#include "../Colors.h"
#include "Cards.h"


enum class Colors;

class ClanCards: public Cards {
    private:
        unsigned int number;
		Colors color;
	public:
		ClanCards(unsigned int Number, Colors Color){number=Number; color=Color;};
		unsigned int getNumber(){return number;};
		Colors getColor(){return color;};
		void setNumber(unsigned int numbers){number = numbers;};
		void setColor(Colors colors){color = colors;};

};



#endif //CLANCARDS_H
