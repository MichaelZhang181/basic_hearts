#ifndef CARD_H
#define CARD_H

#include <cstdlib>
#include <iostream>
using namespace std;

class Card {
	public:
		// Functions //
		void viewCard(int, bool);
		Card();
		~Card();

		// Members //
		string rank;
    	string rankName;
    	int value;
    	char suit;
    	string suitName;
};

#endif