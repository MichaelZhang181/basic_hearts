#ifndef PLAYER_H
#define PLAYER_H

#include <cstdlib>
#include <iostream>
#include "Pile.h"
using namespace std;

class Player {
	public:
		// Functions //
		void viewPlayer(int);
		int AIPass(int); //bot chooses to pass highest card
		int humanPass(int); //human chooses card to pass
		Player(string);
		Player();
		~Player();

		// Members //
		string name;
    	int turn;
    	Pile hand;
};

#endif