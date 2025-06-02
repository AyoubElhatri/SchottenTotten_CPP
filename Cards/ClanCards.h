#ifndef CLANCARDS_H
#define CLANCARDS_H

#include '../Colors.h'


enum class Colors;

class ClanCards: public Cards {
    private:
        unsigned int number;
		Colors color;
	public:
		unsigned int getNumber(){return number;};
		Colors getColor(){return color;};
		void setNumber(unsigned int numbers){number = numbers;};
		void setColor(Colors colors){color = colors;};

};



#endif //CLANCARDS_H
