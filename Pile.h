#ifndef PILE_H
#define PILE_H

#include "Card.h"
#include <cstdlib>
using namespace std;

class Pile {
	public:
		// Functions //
		void initializeDeck(int[13]); //creates deck
		void shuffle(); //shuffles deck
		void viewDeck(int); //views deck
		void addCard(Card);// adds card to hand
		Card removeCard(int); //removes card from hand
		void sort(int); //sorts hand
		bool pileSuit(char); //determines if hand contains a specific suit
		int roundWinner(); //determines who won the trick
		int pointCounter(); //counts the points in a pile
		Pile();
		~Pile();

		// Members //
		int size;
    	Card cards[52];
};

#endif