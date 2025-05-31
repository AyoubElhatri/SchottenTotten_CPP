//
// Created by Utilisateur on 28/05/2025.
//

#ifndef CLANCARDS_H
#define CLANCARDS_H



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
