#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include <cctype>
using namespace std;

#include "globals.h"
#include "History.h"


//create history object corresponding to equivalent Arena
//Assumed: 1<= nRows < MAXROWS
// and	   1<= nCols < MAXCOLS
History::History(int nRows, int nCols) { 
	h_rows = nRows;
	h_cols = nCols;

	// no rabbits should be poisoned at the start
	// so the entire h_record grid consists of zeroes
	for (int r = 1; r <= h_rows; r++)
		for (int c = 1; c <= h_cols; c++)
			h_record[r - 1][c - 1] = 0;
}

//notifies that a rabbit has started its turn poisoned but alive at a grid point
bool History::record(int r, int c) {
	if (r < 1 || r > h_rows || c < 1 || c > h_cols)
		return false;
	h_record[r - 1][c - 1] = h_record[r - 1][c - 1] + 1;
	return true;
}

/* Fill displayHistGrid with the history of how many times 
	a rabbit had started its turn poisoned but alive on that grid point.
	A dot means 0, a letter character A through Y means 1 through 25
	(A means 1, B means 2, etc.) and Z means 26 or more */
void History::display() const {
	char displayHistGrid[MAXROWS][MAXCOLS];
	int r, c;

	// Fill displayHistGrid with dots (empty)
	/*for (r = 1; r <= rows(); r++)
		for (c = 1; r <= cols(); c++)
			displayHistGrid[r - 1][c - 1] = '.';*/

	// Indicate poisoned rabbit history
	for (r = 1; r <= h_rows; r++)
		for (c = 1; c <= h_cols; c++)
			displayHistGrid[r - 1][c - 1] = recordDecoder(h_record[r - 1][c - 1]);


	// Draw the history grid
	clearScreen();
	for (r = 1; r <= rows(); r++){
		for (c = 1; c <= cols(); c++)
			cout << displayHistGrid[r - 1][c - 1];
		cout << endl;
	}
	cout << endl;

}


int History::rows() const {
	return h_rows;
}

int History::cols() const {
	return h_cols;
}


// Converts the number to associated letter
// A dot means 0, a letter character A through Y means 1 through 25
// (A means 1, B means 2, etc.) and Z means 26 or more
char History::recordDecoder(int num) const {
	if (num <= 0) return '.';
	else if (num > 26) return 'Z';
	else {
		int charVal = int('A') + num - 1;
		return char(charVal);
	}
}
