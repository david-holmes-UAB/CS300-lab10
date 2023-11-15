/*
* File: test.cpp
* --------------------------
* File containing Google tests for pokerHand functionality
*/

#include "pokerHand.h"
#include <gtest/gtest.h>
#include <string>

struct PokerTesting : public ::testing::Test {
    public:
    // Strings to hold poker hands
    std::string h1;
    std::string h2;
    std::string h3;
    std::string h4;
    std::string h5;
    std::string h6;
    // pokerhand obj for functs
    pokerHand p;

    // outcome strings
    std::string win1;
    std::string win2;
    std::string tie;

    virtual void SetUp() override {
        h1 = "2H 3D 5S 9C KD";
        h2 = "2C 3H 4S 8C AH";
        h3 = "5S 6S 9S 8S 7S";
        h4 = "2D 6D AD 9D KD";
        h5 = "3C 3S 3H 4H 4C";
        h6 = "5H 6H 9H 8H 7H";

        win1 = "Player 1 Wins.";
        win2 = "Player 2 Wins.";
        tie = "Tie.";
    }
};

// Test for the case provided in the assignment page
TEST_F(PokerTesting, sampleTest) {
    // Testing the sample input and output
    EXPECT_EQ(p.bestPokerHand(h1, h2), win2);
}

// Test to ensure that a Straight Flush is parsed and will win.
TEST_F(PokerTesting, testSFlush) {
    EXPECT_EQ(p.bestPokerHand(h3, h4), win1);
    EXPECT_EQ(p.bestPokerHand(h1, h3), win2);
}

// Tests for a win with a Full House, and a loss against a Straight Flush with the
// same hand.
TEST_F(PokerTesting, testFullHouse) {
    EXPECT_EQ(p.bestPokerHand(h5, h2), win1);
    EXPECT_EQ(p.bestPokerHand(h3, h5), win1);
}

// Test to ensure a Straight Flush is a tie regardless of suit difference
TEST_F(PokerTesting, testSFlushTie) {
    EXPECT_EQ(p.bestPokerHand(h3, h6), tie);
}
