/*
* File: pokerHand.cpp
* ----------------------------
* File containing the implementation of the pokerHand class
* Utilizes regex in parsing hands.
*/

#include <stdio.h>
#include <sstream>
#include <string>
#include <regex>
#include "pokerHand.h"

// Defines for specifc hands
// These values are places so that in the case of comparisons involving a card value
// the higher ranked hand will always win.
#define PAIR 20
#define TWOPAIR 35
#define THREEOFAKIND 45
#define STRAIGHT 60
#define FLUSH 70
#define FULLHOUSE 75
#define FOUROFAKIND 90
#define STRAIGHTFLUSH 120


// Value regexes; used to streamline the values of each card
std::regex ten ("T");
std::regex jack ("J");
std::regex queen ("Q");
std::regex king ("K");
std::regex ace ("A");

pokerHand::pokerHand() {
    /* Constructor */

    // Start both "rankings" at 0
    p1value = 0;
    p2value = 0;
}


std::string pokerHand::bestPokerHand(std::string p1, std::string p2) {
    std::string hand1 = handConversion(p1, p1Cards);
    std::string hand2 = handConversion(p2, p2Cards);

    p1value = rankHand(hand1, p1Cards);
    p2value = rankHand(hand2, p2Cards);

    // Initiate tiebreaker evaluation if both have the same value
    if (p1value == p2value) {
        int tie = p1value + p2value;
        //
        switch (tie)
        {
        case PAIR:
            // Variables for tiebreaker comparison
            int p1 = 0;
            int p1pos = 0;
            int p2 = 0;
            int p2pos = 0;
            // Find pair val and position
            for (int i = 0; i < 5; i++) {
                if (p1Cards[i] == p1Cards[i+1]) {
                    p1 = p1Cards[i];
                    p1pos = i;
                }
                if (p2Cards[i] == p2Cards[i+1]) {
                    p2 = p2Cards[i];
                    p2pos = i;
                }
            }

            if (p1 > p2) {
                return "Player 1 Wins.";
            }
            else if (p2 > p1) {
                return "Player 2 Wins.";
            }
            else {
                // Grab the highest card that isn't a pair
                if (p1pos > 2) { p1 = p1Cards[2]; }
                else { p1 = p1Cards[4]; }
                
                if (p2pos > 2) { p2 = p2Cards[2]; }
                else { p2 = p2Cards[4]; }

                if (p1 > p2) {
                    return "Player 1 Wins.";
                }
                else if (p2 > p1) {
                    return "Player 2 Wins.";
                }
                else { return "Tie."; }
            }
            break;
        case TWOPAIR:
            /* TODO */
            break;
        case THREEOFAKIND:
            // values of the duped cards
            int p1kind = 0;
            int p2kind = 0; 
            // Assign the duped card value
            for(int i = 0; i < 3; i++){
                if(p1Cards[i] == p1Cards[i+1] && p1Cards[i] == p1Cards[i+2]) {
                    p1kind = p1Cards[i];
                }
                if(p2Cards[i] == p2Cards[i+1] && p2Cards[i] == p2Cards[i+2]) {
                    p2kind = p2Cards[i];
                }
            }
            // Decision
            if (p1kind > p2kind) { return "Player 1 Wins."; }
            else if (p2kind > p1kind) { return "Player 2 Wins."; }
            else { return "Tie."; }
            break;
        case STRAIGHT:
            int p1High = p1Cards[4];
            int p2High = p1Cards[4];
            // decision
            if (p1High > p2High) { return "Player 1 Wins."; }
            else if (p2High > p1High) { return "Player 2 Wins."; }
            else { return "Tie."; }
            break;
        case FLUSH:
            // High Card Rules.
            // Keep Comparing in the sorted hands until one is larger than the other
            for (int i = 4; i > -1; i--) {
                if (p1Cards[i] > p2Cards[i]) { return "Player 1 Wins."; }

                if (p2Cards[i] > p1Cards[i]) { return "Player 2 Wins."; }
            }
            // If hands are the exact same, it's a tie.
            return "Tie.";
            break;
        case FULLHOUSE:
            // Works the same as Three of a Kind
            int p1house = 0;
            int p2house = 0; 

            for(int i = 0; i < 3; i++){
                if(p1Cards[i] == p1Cards[i+1] && p1Cards[i] == p1Cards[i+2]) {
                    p1house = p1Cards[i];
                }
                if(p2Cards[i] == p2Cards[i+1] && p2Cards[i] == p2Cards[i+2]) {
                    p2house = p2Cards[i];
                }
            }
            // Decision
            if (p1house > p2house) { return "Player 1 Wins."; }
            else if (p2house > p1house) { return "Player 2 Wins."; }
            else { return "Tie."; }
            break;
        case FOUROFAKIND:
            // values of the duped cards
            int p14kind = 0;
            int p24kind = 0; 
            // Assign the duped card value
            // Note: since only one card will be *not* the same, the check is
            // expedited.
            for(int i = 0; i < 3; i++){
                if(p1Cards[i] == p1Cards[i+1]) {
                    p14kind = p1Cards[i];
                }
                if(p2Cards[i] == p2Cards[i+1]) {
                    p24kind = p2Cards[i];
                }
            }
            // Decision
            if (p14kind > p24kind) { return "Player 1 Wins."; }
            else if (p24kind > p14kind) { return "Player 2 Wins."; }
            else { return "Tie."; }
            break;
        case STRAIGHTFLUSH:
            int p1SFHigh = p1Cards[4];
            int p2SFHigh = p1Cards[4];
            // decision
            if (p1SFHigh > p2SFHigh) { return "Player 1 Wins."; }
            else if (p2SFHigh > p1SFHigh) { return "Player 2 Wins."; }
            else { return "Tie."; }
            break;
        default:
        // High Card Rules.
            for (int i = 4; i > -1; i--) {
                if (p1Cards[i] > p2Cards[i]) { return "Player 1 Wins."; }

                if (p2Cards[i] > p1Cards[i]) { return "Player 2 Wins."; }
            }
            return "Tie.";
            break;
        }

    }
    else if (p1value > p2value) {
        return "Player 1 Wins.";
    }
    else {
        return "Player 2 Wins.";
    }
    
}


// Private functions

/*
* Function: handConversion
* ------------------------------
* Converts the letters representing 10, Jack, Queen, King, and Ace
* into numerical values for the sake of comparisons.
* Also populates the arrays that only contain the numbers
*/
std::string pokerHand::handConversion(const std::string & hand, int (&handArr)[5]) {
    // Conversion of 10 + face cards to numbers
    std::string hcopy = hand;

    std::regex_replace(hcopy, ten, "10");
    std::regex_replace(hcopy, jack, "11");
    std::regex_replace(hcopy, queen, "12");
    std::regex_replace(hcopy, king, "13");
    std::regex_replace(hcopy, ace, "14");

    // Process of isolating numbers and tokenizing, then adding 
    // to an array. Also sorts the numbers by smallest to largest.
    std::string copy2 = hcopy;
    std::string temp = "";
    
    // In order: remove signifiers for (H)earts, (D)iamonds, (C)lubs, (S)pades
    copy2.erase(remove(copy2.begin(), copy2.end(), 'H'));
    copy2.erase(remove(copy2.begin(), copy2.end(), 'D'));
    copy2.erase(remove(copy2.begin(), copy2.end(), 'C'));
    copy2.erase(remove(copy2.begin(), copy2.end(), 'S'));

    // Prepare to tokenize input
    std::stringstream cnv(copy2);

    // tokenize input
    int i = 0;
    while(getline(cnv, temp, ' ')) {
        handArr[i] = std::stoi(temp);
        i++;
    }
    
    // sort array from smallest to largest
    std::sort(handArr[0], handArr[4]);

    return hcopy;
}

/*
* Function: rankHand()
* ----------------------------------------
* Returns a numerical based "ranking" based on the highest
* found hand in the provided cards.
* Checks if any of the booleans are true and assigns that value. If no booleans are true, checks for any
* pairs. If there are no pairs, assigns the hand the value of its highest card.
*/
int pokerHand::rankHand(const std::string & hand, int (&handArr)[5]) {

    // Is there a better way of performing these checks?
    if (flush(hand) && straight(handArr)) { return STRAIGHTFLUSH; }
    if (fourKind(handArr)) { return FOUROFAKIND; }
    if (fullHouse(handArr)) { return FULLHOUSE; }
    if (flush(hand)) { return FLUSH; }
    if (straight(handArr)) { return STRAIGHT; }
    if (threeKind(handArr)) { return THREEOFAKIND; }

    // will only be reached if no special hands are found;
    // start checking for pairs.
    int count = 0;                  // Our variable to store number of pairs
    for (int i = 0; i < 5; i++) {
        if (handArr[i] == handArr[i+1]) {
            count++;
        }
    }
    if (count > 1) {
        return TWOPAIR;             // Two pairs are found
    }
    else if (count == 1) {
        return PAIR;                // only one pair
    }
    else {
        return handArr[4];          // as the array is sorted, this is the largest number
    }

}

/*
* Function: flush()
* -------------------------------
* Returns true if the hand contains a flush.
*/
bool pokerHand::flush(const std::string & hand) {
    // Regexes that match a hand of all of one suit
    // Regex was tested with regex101.com
    std::regex allHearts("(([1-9]|1[1-4])H ){4}([1-9]|1[1-4])H");
    std::regex allDiamonds("(([1-9]|1[1-4])D ){4}([1-9]|1[1-4])D");
    std::regex allClubs("(([1-9]|1[1-4])C ){4}([1-9]|1[1-4])C");
    std::regex allSpades("(([1-9]|1[1-4])S ){4}([1-9]|1[1-4])S");

    if (std::regex_match(hand, allHearts) || std::regex_match(hand, allDiamonds) || std::regex_match(hand, allClubs) || std::regex_match(hand, allSpades)) {
        return true;
    }
    else {
        return false;
    }
}

/*
* Function: straight()
* -------------------------------------
* Checks to see if the hand contains a straight
*/
bool pokerHand::straight(int (&handArr)[5]) const {
    for (int i = 0; i < 5; i++) {
        // if the following card is not 
        if (!(handArr[i] == handArr[i+1] - 1)) {
            return false;
        }
    }

    return true;
}

/*
* Function: fullHouse()
* -----------------------------------------
* Checks to see if the hand contains a full house.
* Breaks the passed in array twice; 3 and 2, and 2 and 3, to check if one is a pair
* and the other is a three of a kind.
*/
bool pokerHand::fullHouse(int (&handArr)[5]) const {
    // Check front for three of a kind and back for pair
    if (handArr[0] == handArr[1] && handArr[0] == handArr[2]) {
        if (handArr[3] == handArr[4]) {
            return true;
        }
    }
    // Check front for pair and back for three of a kind
    else if (handArr[0] == handArr[1]) {
        if (handArr[2] == handArr[3] && handArr[2] == handArr[4]) {
            return true;
        }
    }
    else {
        return false;
    }

}

/*
* Function: fourKind()
* ------------------------------------
* Checks to see if the hand contains a four of a Kind
*/
bool pokerHand::fourKind(int (&handArr)[5]) const {
    int kind = 0;               // Counter
    /*
    * If a sorted hand is a four of a kind, then either the first or 
    * second number will match the following three numbers.
    */
    for(int i = 0; i < 2; i++){
        if(handArr[i] == handArr[i+1] && handArr[i] == handArr[i+2] && handArr[i] == handArr[i+3]) {
            kind++;
        }
    }

    if (kind > 0) {
        return true;
    }
    else {
        return false;
    }
}

/*
* Function: threeKind()
* ---------------------------------------
* Checks to see if the hand contains a three of a Kind
*/
bool pokerHand::threeKind(int (&handArr)[5]) const {
    int kind = 0;               // Counter
    /*
    * If a sorted hand is a three of a kind, then the first, second, or
    * third number will match the following two numbers.
    */
    for(int i = 0; i < 3; i++){
        if(handArr[i] == handArr[i+1] && handArr[i] == handArr[i+2]) {
            kind++;
        }
    }

    if (kind > 0) {
        return true;
    }
    else {
        return false;
    }
}

