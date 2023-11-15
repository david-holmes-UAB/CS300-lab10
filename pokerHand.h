/*
* File: pokerHand.h
* -------------------------------
* Header file to define the pokerHand class.
* Takes two poker hands, compares them, and then outputs the
* winner.
*/
#ifndef _pokerHand_h
#define _pokerHand_h

#include <string>

class pokerHand {

/*
* Pair of ints to hold the "value" of each hand.
* Each hand is assigned a "value", and the higher value wins. In other cases, the higher pair or
* highest card's value is placed into this variable.
* For example, a straight flush is given the value of 120.
*/
int p1value;
int p2value;

/*
* Pair of arrays to hold only the numerical values of each of the five cards.
* This array is utilized to find the highest card in each hand if necessary.
*/
int p1Cards[5];
int p2Cards[5];

/*
* Function: handConversion
* Input: string hand ; where 'hand' is the "poker hand" to be parsed
        and handArr ; where 'handArr' is the array of only the numerical
        values of the cards in the hand
* Output: a new string with ten and/or face cards converted to numbers
*/
std::string handConversion(const std::string & hand, int (&handArr)[5]);

/*
* Function: rankHand()
* Input: string hand
* Output: an int value representing the "rank" of the provided hand
* Checks to see the highest value hand and assigns the appropriate rank.
*/
int rankHand(const std::string & hand, int (&handArr)[5]);

// Functions for various specific hands

// Booleans
// There is most likely a more consolodated way to do this check,
// but I didn't end up thinking of it
bool flush(const std::string & hand);               // contains a flush
bool straight(int (&handArr)[5]) const;             // contains a straight
bool fourKind(int (&handArr)[5]) const;             // contains four of a kind
bool threeKind(int (&handArr)[5]) const;            // contains three of a kind    
bool fullHouse(int (&handArr)[5]) const;            // contains a full house


public:
// Constructor
pokerHand();

/*
* Function: bestPokerHand
* Inputs: string p1, string p2 ; where both are "poker hands"
* Output: The winner between the two hands 
*/
std::string bestPokerHand(std::string p1, std::string p2);


};


#endif