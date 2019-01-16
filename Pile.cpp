#include <cstdlib>
#include "Card.h"
#include "Pile.h"
#include <time.h>

using namespace std;

// Function: initializeDeck ================================================= //
void Pile::initializeDeck(int valueOrder[13])
{
    string suitOrder[4] = {"Hearts", "Diamonds", "Clubs", "Spades"};
    string rankOrder[13] = {"A", "2", "3", "4", "5", "6", "7", "8",
                            "9", "10", "J", "Q", "K"};
    string rankNames[13] = {"Ace", "Two", "Three", "Four", "Five", "Six",
                            "Seven", "Eight", "Nine", "Ten",
                            "Jack", "Queen", "King"};
    //char suitChar[4] = {'H', 'D', 'C', 'S'};
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 13; j++) {
            cards[i * 13 + j].suit = char(3 + i);
            cards[i * 13 + j].suitName = suitOrder[i];
            cards[i * 13 + j].value = valueOrder[j];
            cards[i * 13 + j].rank = rankOrder[j];
            cards[i * 13 + j].rankName = rankNames[j];
        }
    }
    size = 52;
}

// Function: shuffle ======================================================== //
void Pile::shuffle() {
    for (int x = 0; x < 5000; x++) {
    	int tempPos = 0;
    	Card tempCard;
    	for (int i = 0; i < size; i++) {
            srand(time(NULL)); 
            tempPos = rand() % (size - i) + i; //choose a random card position
            tempCard = cards[i]; //copies a card
            cards[i] = cards[tempPos]; //swaps for loop value for randomly selected card
            cards[tempPos] = tempCard;
    	}
    }
}

// Function: viewDeck ======================================================= //
void Pile::viewDeck(int r) {
    bool last = 0;
    for (int i = 0; i < size / r + 1; i++) {
        for (int k = 0; k < 7; k++) {
            for (int j = 0; j < r; j++) {
                if (i * r + j < size) {
                    if (j == r - 1) last = 1;
                    else if (i * r + j == size - 1) last = 1;
                    else last = 0;
                    cards[i * r + j].viewCard(k, last);
                }
            }
        }
    }
}

// Function: addCard ======================================================== //
void Pile::addCard(Card addedCard) {
    cards[size] = addedCard;
    size++;
}

// Function: removeCard ===================================================== //
Card Pile::removeCard(int pos) {
    if (pos - 1 < size) {
        Card tempCard = cards[pos - 1];
        for (int i = pos - 1; i < size - 1; i++) {
	        cards[i] = cards[i + 1];
        }
        size--;
        return tempCard;
    }
}

// Function: sort (uses insertion sort)========================================================== //
void Pile::sort(int handsize)
{
    Card valueholder;
    for (int a = 1; a<handsize; a++)
    {
        if ((static_cast<int>(cards[a-1].suit)*13 + cards[a-1].value)>(static_cast<int>(cards[a].suit)*13 + cards[a].value)) //multiplies suit int value by 13 and adds card value then compares to the card to the right
        {
            for (int b = a; b>0 ; b--)
            {
                if ((static_cast<int>(cards[b].suit)*13 + cards[b].value)>(static_cast<int>(cards[b-1].suit)*13 + cards[b-1].value)) //compares to card on the left 
                {
                    break;
                }
                valueholder = cards[b];
                cards[b] = cards[b-1];
                cards[b-1] = valueholder;
            }
        }
    }
}

// Function: Checks for the given suit =======================================//
bool Pile::pileSuit(char chosen)
{
	for (int z = 0; z<size; z++)
	{
		if (cards[z].suit == chosen) // checks if card matches desired suit
		{
			return true;
		}
	}
	return false;
}

// Function: Determines who won the trick =================================== //
int Pile::roundWinner()
{
	int curWinner = 0;
	for (int b = 0; b<size; b++)
	{
		if ((cards[0].suit == cards[b].suit) && (cards[curWinner].value<cards[b].value)) // checks to see if suits match and the card selected has greater value than the lead card
		{
			curWinner = b;
		}
	}
	return curWinner;
}

// Function: Counts points of a player
int Pile::pointCounter()
{
	int total=0;
	for (int d = 0; d<size; d++)
	{
		if (static_cast<int>(cards[d].suit)== 3) //add one point for each hearts card
		{
			total++;
		}
		else if ((static_cast<int>(cards[d].suit)== 6)&& (cards[d].value== 11)) //add 13 points for queen of spades
		{
			total += 13;
		}
	}
	return total;
}


// Constructor ============================================================== //
Pile::Pile() {size = 0;}

// Destructor =============================================================== //
Pile::~Pile() {}