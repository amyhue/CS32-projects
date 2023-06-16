#ifndef SIDE_H
#define SIDE_H

#include <iostream>
#include <random>
using namespace std;

class Timer;
class JumpyTimer;
unsigned long f(int n);
unsigned long f_helper(int n, double timeLimit, JumpyTimer& timer);


enum Side { NORTH, SOUTH };

const int NSIDES = 2;
const int POT = 0;

inline
Side opponent(Side s)
{
	return Side(NSIDES - 1 - s);
}


// from Project	1, as provided by Professor Smallberg
inline
int randInt(int lowest, int highest)
{
	if (highest < lowest)
		swap(highest, lowest);
	static random_device rd;
	static default_random_engine generator(rd());
	uniform_int_distribution<> distro(lowest, highest);
	return distro(generator);
}

#endif
