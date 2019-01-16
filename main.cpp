/* Michael Zhang
ICS4U - Mr. Lauder
Hearts card game
conceived: 12.03.2018
final change:12.04.2018
*/

#include <iostream>
#include "Card.h"
#include "Pile.h"
#include "Player.h"

using namespace std;

//Function Prototypes =======================================================================

Pile deal(Player [], Pile); //deals cards from a pile
int clubFinder(Player [], int); //finds the 2 of clubs
bool compareCards(Player, Pile, int, bool); // checks if player's card is valid
int turnMenu(Player, Pile, bool&); //player's turn menu
int matchSetup(Player[], int, int, bool&, int []); //sets up the hand
int roundPlay(Player[], int, bool&, int []); // controls the actions during the trick or round
void pass3(Player [], int); //determines who to pass stuff too
int AIturn(Player, Pile, bool); //bot's turn logic
void scorefinder(int, Player [], int []); //determines who won

// Global Variable =========================================================================

int cardvalue[13]={13,1,2,3,4,5,6,7,8,9,10,11,12};

// Main ====================================================================================

int main()
{
    int displayRow = 13; // How many cards will be displayed in each row with the display function
    int play = 1; // determines if user still wants to play
    while(play == 1) // loop allows user to play another game after game is finished
    {
	    int NumMatch = 1; //states that it is the first match of Hearts
	    string pName; //holds player's name
	    int PlayerPoints[4]= {0,0,0,0};
	    Player group[4];
	    cout<<"What is your name? Do not enter spaces. Use '_' instead.\n";
	    cin>>pName;
	    group[0]=Player(pName); //Real player
	    group[1]=Player("AlexBot"); // generates ai player
	    group[2]=Player("AmyBot"); // generates ai player
	    group[3]=Player("AmandaBot"); // generates ai player
	    int loser = 4; //states if anyone has lost
	    bool heartsPlayed = false; // states if anyone has played points
	    while(loser == 4) //while no one has lost the game is played
	    {
	    	for(int i = 0; i<4; i++)
	    	{
	    		group[i].hand = Pile(); //used to reset the hands of each match
			}
	    	loser = matchSetup(group, displayRow, NumMatch, heartsPlayed, PlayerPoints); //starts up a match
	    	NumMatch++; //once match is over increase counter by one
		}
		scorefinder(loser, group, PlayerPoints); //outputs scores and winner
		cout<<"Would you like to play a new game?\n Enter 0 to exit and enter 1 to play again"; //allows user to play again or exit
		cin>>play;
	}
    return 0;
}

//Function Definitions =============================================================

// Function: deals cards ===========================================================
Pile deal(Player party[], Pile start)
{
    for (int a=0; a<4; a++)
    {
        for (int b=0; b<13; b++)
        {
            party[a].hand.addCard(start.removeCard(1));
        }
    }
    return start;
}

// Function: Finds who has the 2 of clubs ========================================
int clubFinder(Player party[],int handsize)
{
	for (int p=0; p<4;p++)
	{
		for (int h=0; h<handsize; h++)
		{
			if (party[p].hand.cards[h].suitName == "Clubs" && party[p].hand.cards[h].value == 1) //checks specific card in the hand is 2 of clubs
			{
				return p; //returns which player has the card
			}
		}
	}
	return 0;
}

//Function: The real player's menu
int turnMenu(Player current, Pile ctrPile, bool& HeartsPlay) //the menu that the player sees when it is their turn
{
	int tempChoice;
	cout<<"It is "<<current.name<<"'s turn.\n"; //Specifies it is the player's turn
	if (ctrPile.size == 0)
	{
		cout<<"You are starting.\n"; //if the player is starting the round or trick
	}
	else
	{
		cout<<"These are the current cards in play.\n";
		ctrPile.viewDeck(ctrPile.size); //displays card played this round or trick
		cout<<"The card on the very left is the first card put into play.\n"; //specifies which card was played first so the player knows the restrictions on what he can play
	}
	cout<<"This is your hand.\n";
	current.hand.viewDeck(current.hand.size); // shows player's hand
	do{
	cout<<"Counting from the left which card would you like to play. (First card from the left is card 1) Please input a number. \n";
	cin>>tempChoice;
	}while(compareCards(current, ctrPile, tempChoice-1, HeartsPlay) == false); // checks that the card chosen is legal to play
	return tempChoice;
}

//Function: AI player's turn's thought process===========================================
int AIturn(Player current, Pile inPlay, bool heartsPlayed) //AI player turn
{
	int tempPOS = 0;
	if (current.turn ==0) // checks if it's the first turn of the match
	{
		if (inPlay.size == 0) // checks if they're leading the trick
		{
			for(int i = 0; i<current.hand.size;i++)
			{
				if (static_cast<int>(current.hand.cards[i].suit) == 5 && current.hand.cards[i].value == 1) //searches for two of clubs in their hand and plays it
				{
					return i;
				}
			}
		}
		else if (current.hand.pileSuit(inPlay.cards[0].suit) == true) //if first round but not starting and you have cards of the same suit as the leader
		{
			for(int i = 0; i<current.hand.size;i++) //plays lowest card of same suit
			{
				if (current.hand.cards[i].suit == inPlay.cards[0].suit)
				{
					return i;
				}
			}
		}
		else //if first round and you do not have a card of the same suit as the leader
		{
			for(int i = 0; i<current.hand.size;i++)
			{
				if (static_cast<int>(current.hand.cards[i].suit) != 3) //find first card that isn't hearts and copy location
				{
					tempPOS = i;
					i = 15;
				}
			}
			for(int i = tempPOS +1; i<current.hand.size;i++)
			{
				if (current.hand.cards[tempPOS].value > current.hand.cards[i].value)
				{
					if (current.hand.cards[i].value != 11 || static_cast<int>(current.hand.cards[i].suit) !=6)
					{
						tempPOS = i;
					}
				}
			}
			return tempPOS;
		}
	}
	else if ( inPlay.size == 0) //if not first round but you are starting
	{
		if (heartsPlayed == false) //points have not been played
		{
			for(int i = 0; i<current.hand.size;i++)
			{
				if (static_cast<int>(current.hand.cards[i].suit)!= 3) // finds first card that isn't hearts
				{
					tempPOS = i;
					i = 15;
				}
			}
			for(int i = tempPOS+1; i<current.hand.size;i++) //plays lowest non-hearts card
			{
				if (current.hand.cards[tempPOS].value > current.hand.cards[i].value)
				{
					tempPOS = i;
				}
			}
			return tempPOS;
		}
		else // if points have been played and you're starting
		{
			for(int i = 1; i<current.hand.size;i++) // automatically play the lowest value card in your hand
			{
				if (current.hand.cards[tempPOS].value>current.hand.cards[i].value)
				{
					tempPOS = i;
				}
			}
			return tempPOS;
		}
	}
	else if (current.hand.pileSuit(inPlay.cards[0].suit) == true) // if not starting or first round and you have cards of the same suit as the lead suit
	{
		for(int i = 0; i<current.hand.size;i++)
		{
			if (current.hand.cards[i].suit == inPlay.cards[0].suit) //play the lowest card of the suit. Hand is sorted such that first card from the left of that suit is lowest
			{
				return i;
			}
		}
	}
	else // you don't have cards of the same suit as the leader
	{
		for(int i = 1; i<current.hand.size;i++) // play lowest value card in hand
		{
			if (current.hand.cards[tempPOS].value>current.hand.cards[i].value)
			{
				tempPOS = i;
			}
		}
		return tempPOS;
	}
}

//Function: Setup for the match ========================================================
int matchSetup(Player people[], int IHsize, int matchNum, bool& heartsPlayed, int pointTotal[])
{
	int StartPoints[4];
	for (int i = 0; i<4; i++)
	{
		StartPoints[i]=pointTotal[i];
	}
    Pile deck = Pile();
	deck.initializeDeck(cardvalue); //creates a deck
    deck.shuffle(); //shuffles the deck
	deck = deal(people, deck); // deals the deck of cards
    for (int i =0; i<4; i++)
    {
		people[i].hand.sort(people[i].hand.size); //sorts the players' hands
		people[i].turn = 0; //sets the player turn counter to 0 to indicate the start of a match
	}
	pass3(people, matchNum); //determines who to pass 3 cards to
	for (int i =0; i<4; i++)
    {
		people[i].hand.sort(people[i].hand.size); //sorts hands after passing new cards
	}

	int starter = clubFinder(people, IHsize); //finds out who starts the match
	while(people[0].hand.size != 0)
	{
		starter = roundPlay(people, starter, heartsPlayed, pointTotal); // calls up the trick function to determine who starts next trick (a trick is a round)
		if (pointTotal[starter] >=100) //checks if the person who won the last trick has 100 points
		{
			return 5; //end game if there is someone who has lost
		}
		if (pointTotal[starter]-StartPoints[starter] == 26)
		{
			return starter;
		}
	}
	return 4;
}

//Function: Completes the actions of a round or a trick ====================================

int roundPlay(Player party[], int start, bool& heartsPlayed, int pointTotal [])
{
	Pile tempPile; //creates a temporary pile to store the cards played this round
	for(int a = 0; a<4; a++)
	{
		cout<<party[a].name<<" has "<<pointTotal[a]<<" points.\n";// outputs who has how many points from the last round/trick
	}
	for (int a = start; a<(start+4); a++) //determines who's turn it is
	{
		if (a%4 == 0)
		{
			tempPile.addCard(party[0].hand.removeCard(turnMenu(party[0], tempPile, heartsPlayed))); //calls up the real player's turn menu
		}
		else
		{
			cout<<party[(a%4)].name<<" has played a card.\n"; //tells the player who played which AI played which card;
			tempPile.addCard(party[(a%4)].hand.removeCard((AIturn(party[(a%4)], tempPile, heartsPlayed))+1)); //tells the ai to make a move
		}
		party[(a%4)].turn++;
	}
	cout<<"The cards played this round are displayed below.\n";
	tempPile.viewDeck(tempPile.size); //allows player to see the cards played that round again
	int winner = (start + tempPile.roundWinner()) %4; //determines who won
	if (tempPile.pointCounter() != 0) // adds points to the point Total;
	{
		pointTotal[winner] += tempPile.pointCounter();
		heartsPlayed = true;
	}
	system("PAUSE");//allows the player to keep looking before the screen is wiped;
	system("CLS"); //clears the screen for next round
	return winner;
}

//Function: Checks if the real player's card choice is acceptable ======================
bool compareCards(Player current, Pile inPlay, int toBeplayed, bool heartsPlayed)
{
	if (toBeplayed >= current.hand.size || toBeplayed < 0) // checks if the card chosen exists
	{
		cout<<"You must play a card in your hand.\n"; //outputs feedback and asks them to try again;
		return false;
	}
	char chosen = current.hand.cards[toBeplayed].suit;
	if (current.turn ==0) // if first turn of the match
	{
		if (inPlay.size == 0) //if leading
		{
			if (static_cast<int>(chosen) == 5 && current.hand.cards[toBeplayed].value ==1) // must play the 2 of clubs
			{
				return true;
			}
			else
			{
				cout<<"You must play the 2 of clubs."<<endl; //outputs feedback and asks them to try again;
				return false;
			}
		}
		else if (current.hand.pileSuit(static_cast<char>(5)) == true) //ensures player does not play points when they can match the suit of the leader
		{
			if (chosen == inPlay.cards[0].suit)
			{
				return true;
			}
			else
			{
				cout<<"You must follow the lead suit."<<endl;
				return false;
			}
		}
		else if (static_cast<int>(chosen) != 3 && (static_cast<int>(chosen) != 6 || current.hand.cards[toBeplayed].value != 11)) //ensures player does not play points in general
		{
			return true;
		}
		else
		{
			cout<<"You cannot play points on the first trick of the hand.\n";
			return false;
		}
	}
	else if ( inPlay.size == 0) //if they're starting
	{
		if (heartsPlayed == false) // if points have not been played
		{
			if(static_cast<int>(chosen) != 3) //cannot play points
			{
				return true;
			}
			else
			{
				cout<<"You cannot lead with hearts yet."<<endl; //outputs feedback and asks them to try again;
				return false;
			}
		}
		else // if points have been played
		{
			return true;
		}
	}
	else if (current.hand.pileSuit(inPlay.cards[0].suit) == true) //if they have stuff of the same suit as leader
	{
		if (chosen == inPlay.cards[0].suit) //checks if they played the same suit card
		{
			return true;
		}
		else
		{
			cout<<"You must match the lead suit."<<endl; //outputs feedback and asks them to try again;
			return false;
		}
	}
	else //otherwise the previous conditions are not met
	{
		return true; //play anything;
	}
}

//Function: Determines teh passing of 3 cards at the start of a hand (match)
void pass3(Player party[], int match)
{
	for (int i = 0 ; i<4; i++)
	{
		int passed = 0;
		switch (match %4) //determines which way to pass the cards depending on the round
		{
			case 0: break;//no passing
			case 1 : for (int a =0; a<3; a++) //pass to the left
					{
						if (i ==0)
						{
							passed= party[i].humanPass(a);
							party[i+1].hand.addCard(party[i].hand.removeCard(passed));
						}
						else
						{
							passed = party[i].AIPass(13-a);
							party[(i+1)%4].hand.addCard(party[i].hand.removeCard(passed));
						}
					}
					break;
			case 2: for (int a =0; a<3; a++) // pass to the right
					{
						if (i ==0)
						{
							passed= party[i].humanPass(a);
							party[i+3].hand.addCard(party[i].hand.removeCard(passed));
						}
						else
						{
							passed = party[i].AIPass(13-a);
							party[(i+3)%4].hand.addCard(party[i].hand.removeCard(passed));
						}
					}
					break;
			case 3: for (int a =0; a<3; a++) //pass across
					{
						if (i ==0)
						{
							passed= party[i].humanPass(a);
							party[i+2].hand.addCard(party[i].hand.removeCard(passed));
						}
						else
						{
							passed = party[i].AIPass(13-a);
							party[(i+2)%4].hand.addCard(party[i].hand.removeCard(passed));
						}
					}
					break;
		}
	}
	return;
}

//Funtion: Determines how many points each player has =============================================
void scorefinder(int winCondition, Player Party[], int TotalPoints[])
{
	int lowest = 0;
	if (winCondition ==5 ) //if the game ended by soemone obtaining 100 points
	{
		for (int i = 0; i <4; i++) //determines the winning score
		{
			cout<<Party[i].name<<" has "<<TotalPoints[i]<<" points.\n";
			if (TotalPoints[i] > TotalPoints[(i+1)%4])
			{
				lowest = (i+1)%4;
			}
		}
		for (int i = 0; i <4; i++) //outputs all the winners bsed on the winning score
		{
			if (TotalPoints[i]==lowest)
			{
				cout<<Party[i].name<<" is a winner.\n";
			}
		}
	}
	else if (winCondition < 4) //if a specific player shot the moon
	{
		for (int i = 0; i <4; i++)
		{
			cout<<Party[i].name<<" has "<<TotalPoints[i]<<" points.\n";
		}
		cout<<Party[winCondition].name<<" has won. THEY HAVE SHOT THE MOON.\n";
	}
	return;
}

