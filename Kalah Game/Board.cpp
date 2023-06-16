#include <iostream>
#include <vector>
#include "Board.h"
#include "Side.h"

using namespace std;

Board::Board(int nHoles, int nInitialBeansPerHole) {
	if (nHoles > 0)
		m_Holes = nHoles;
	else m_Holes = 1;

	if (nInitialBeansPerHole < 0)
		nInitialBeansPerHole = 0;

	for (int side = 0; side < NSIDES; side++) {
		vector<int> board_i;
		board_i.push_back(0); // for pot
		for (int i = 1; i <= holes(); i++)
			board_i.push_back(nInitialBeansPerHole);
		m_Board.push_back(board_i); // add this board side to the board
	}

}

int Board::holes() const {
	return m_Holes;
}

int Board::beans(Side s, int hole) const {
	// valid holes are: at position 0 to holes() (inclusive)

	if (hole < 0 || hole > holes()) {
		return -1; // hole number is invalid
	}
	else {
		return m_Board[s][hole];
	}
}

int Board::beansInPlay(Side s) const {
	int holeBeans = 0;

	for (int i = 1; i <= holes(); i++) {
		holeBeans += m_Board[s][i];
	}

	return holeBeans;
}

int Board::totalBeans() const {
	
	int totalBeans = 0;
	for (int side = 0; side < NSIDES; side++) {
		for (int i = 0; i <= holes(); i++) {
			totalBeans += m_Board[side][i];
		}
	}

	return totalBeans;
}

bool Board::sow(Side s, int hole, Side& endSide, int& endHole) {
	// if s is invalid, return false
	if (s < 0 || s >= NSIDES) {
		return false;
	}

	// if the hole is a pot or invalid or empty, return false
	if (hole == 0 || beans(s, hole) == -1 || beans(s, hole) == 0) {
		return false;
	}

	// set beans in hole (s, hole) to 0, since they are "removed"
	int sowingBeans = beans(s, hole);
	m_Board[s][hole] = 0;

	// Now, we sow the beans in all the holes and s's pot. We
	// skip s's opponent's pot.

	int startingHole = hole;
	for (Side side = s;; side = opponent(side)) {
		// this part of the code traversing is based on how
		// the NORTH-SOUTH pots are defined and located. May
		// need to be changed depending on the variation.
		

		if (side == SOUTH) {
			startingHole += 1;
			for (int i = startingHole; i <= holes(); i++) {
				if (sowingBeans > 0) {
					m_Board[side][i] += 1;
					sowingBeans--;
					endSide = SOUTH;
					endHole = i;
				}
			}
			startingHole = holes() + 1;
		}

		if (side == NORTH) {
			startingHole -= 1;
			for (int i = startingHole; i > 0; i--) {
				if (sowingBeans > 0) {
					m_Board[side][i] += 1;
					sowingBeans--;
					endSide = NORTH;
					endHole = i;
				}
			}
			startingHole = 0;
		}

		if (sowingBeans > 0 && side == s) {
			m_Board[side][0] += 1;
			sowingBeans--;
			endSide = side;
			endHole = 0;
		}

		if (sowingBeans == 0) return true;

	}

	return true;

}

bool Board::moveToPot(Side s, int hole, Side potOwner) {
	// if the indicated hole is invalid or a pot, return false
	if (beans(s, hole) == -1 || hole == 0)
		return false;
	
	// remove beans from hole
	int beansFromHole = m_Board[s][hole];
	m_Board[s][hole] = 0;

	// Add the beans to the pot belonging to potOwner and return true
	m_Board[potOwner][0] += beansFromHole;
	return true; // TODO: change
}

bool Board::setBeans(Side s, int hole, int beans) {
	// if indicated hole is invalid or beans is negative, return false
	if (hole < 0 || hole > holes() || beans < 0)
		return false;

	// now we change the number of beans in the indicated hole/pot to
	// the value of the third parameter
	m_Board[s][hole] = beans;
	return true;

}
