#include <cstdlib>
#include "Player.h"

// Function: viewPlayer ===================================================== //
void Player::viewPlayer(int r) {
    for (int i = 0; i < 80; i++) cout << '=';
    cout<< endl << name << "'s Hand" << endl;
    hand.viewDeck(r);
    for (int i = 0; i < 80; i++) cout << '=';
}

// Function: AI passing card selector ======================================= //
int Player::AIPass(int handSize)
{
	int tempPOS= 0;
	for(int b = 1; b<handSize; b++)
	{
		if (hand.cards[tempPOS].value<hand.cards[b].value) //looks for highest card in hand
		{
			tempPOS = b;
		}
	}
	return tempPOS + 1; //sends that card number offset by one due to the nature of the remove card function
}

// Function: Player selects card for passing ================================ //
int Player::humanPass(int cardnumber)
{
	int tempPOS = -1;
	hand.viewDeck(hand.size); //displays hand
	do
	{
		cout<<"Pick 3 Cards to pass to a player. Enter the position of card # "<<cardnumber+1<<" (Starting at 1 with the card on the very left)\n"; 
		cin>>tempPOS;
	}while (tempPOS <1 || tempPOS > hand.size); //ensures that the card selected exists in the player's hand
	return tempPOS;
}

// Constructor ============================================================== //
Player::Player(string n) {
    name = n;
    hand = Pile();
    turn = -1;
}

// Basic Constructor ======================================================== //
Player::Player()
{
    name = "";
    hand = Pile();
    turn = -1;
}

// Destructor =============================================================== //
Player::~Player() {}