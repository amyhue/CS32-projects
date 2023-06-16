#ifndef HISTORY_H
#define HISTORY_H

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
#include <cctype>
using namespace std;

#include "globals.h"
//class Arena;

class History {
public:
	History(int nRows, int nCols);
	bool record(int r, int c);
	void display() const;

	/* maybe include:
	~History();*/
	

private:
	int     rows() const;
	int     cols() const;
	char	recordDecoder(int num) const; 

	int h_rows;
	int h_cols;
	int h_record[MAXROWS][MAXCOLS];

};

#endif
