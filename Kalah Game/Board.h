#ifndef BOARD_H
#define BOARD_H

#include <iostream>
#include <vector>
#include "Side.h"

using namespace std;

class Board {
public:
	Board(int nHoles, int nInitialBeansPerHole);
	// Construct a Board with the indicated number of holes per side
	// (not counting the pot) and initial number of beans per hole. If
	// nHoles is not positive, act as if it were 1; if nInitialBeansPerHole
	// is negative, act as if it were 0.
	
	// A pot is considered to be hole #0. In the given Kalah variation, the
	// North's hole #1 is next to North's pot. And South's hole #6 is next
	// to South's pot.

	int holes() const;
	// Return the number of holes on a side (not counting the pot).

	int beans(Side s, int hole) const;
	// Return the number of beans in the indicated hole or pot, or -1 if
	// the hole number is invalid.

	int beansInPlay(Side s) const;
	// Return the total number of beans in all the holes on the indicated
	// side, not counting the beans in the pot.

	int totalBeans() const;
	// Return the total number of beans in the game, including any in
	// the pots

	bool sow(Side s, int hole, Side& endSide, int& endHole);
	// If the hole indicated by (s, hole) is empty or invalid or a pot,
	// this function returns false without changing anything. Otherwise,
	// it will return true after sowing the beans: the beans are removed
	// from hole (s, hole) and sown counterclockwise, including s's pot
	// if encountered, but skipping s's opponent's pot. The function sets
	// the parameter endSide and endHole to the side and hole where the
	// last bean was placed. (This function does NOT make captures or
	// multiple turns)

	bool moveToPot(Side s, int hole, Side potOwner);
	// If the indicated hole is invalid or a pot, return false without
	// changing anything. Otherwise, move all the beans in hole (s, hole)
	// into the pot belonging to potOwner and return true

	bool setBeans(Side s, int hole, int beans);
	// If the indicated hole is invalid or beans is negative, this function
	// returns false without changing anything. Otherwise it will return true
	// after setting the number of beans in the indicated hole or pot to the
	// value of the third parameter. (This could change what beansInPlay
	// and totalBeans return if they are called later.) This function
	// exists solely to test this program more easily. None of the code that
	// implements the member functions of any class is allowed to call this
	// function directly or indirectly.

private:
	int m_Holes;

	vector<vector<int>> m_Board;
	
	// m_Board consists of all sides. Each side's vector is located according 
	// in the index accoording to their enum value. The side's pot is located
	// at index 0, followed by the corresponding hole.

};

#endif
