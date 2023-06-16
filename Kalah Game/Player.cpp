#include <iostream>
#include <string>
#include <climits>
using namespace std;

#include "Player.h"
#include "Board.h"
#include "Side.h"

Player::Player(std::string name) {
	m_Name = name;
}

std::string Player::name() const {
	return m_Name;
}

bool Player::isInteractive() const {
	return false;
}

Player::~Player() {

}

HumanPlayer::HumanPlayer(std::string humanName)
	: Player(humanName) {

}

bool HumanPlayer::isInteractive() const {
	return true;
}

int HumanPlayer::chooseMove(const Board& b, Side s) const {

	// If no move is possible (i.e. all holes on Side s is empty)
	// return -1.
	if (b.beansInPlay(s) == 0) {
		cout << "There are no valid moves for this side." << endl;
		return -1;
	}

	// Assuming there are valid moves possible, prompt the player
	// to make a move.
	cout << name() << ", please select the hole whose beans you want to sow: ";
	string playerMove;
	getline(cin, playerMove);

	if (playerMove.size() == 0) {
		cout << "You did not select a hole. ";
		return chooseMove(b, s);
	}
	
	if (playerMove.size() == 1) {
		for (int i = 1; i <= b.holes(); i++) {
			int chosenMove = playerMove[0] - '0';
			if (chosenMove == i) {
				if (b.beans(s, chosenMove) <= 0) {
					cout << "That hole is empty! ";
					return chooseMove(b, s);
				}
				else return chosenMove;
			}
		}
	}

	
	cout << "That is an invalid hole! ";
	return chooseMove(b, s);

	return -99999;
}

HumanPlayer::~HumanPlayer() {

}

BadPlayer::BadPlayer(std::string badName)
	: Player(badName) {

}

bool BadPlayer::isInteractive() const {
	return false;
}

int BadPlayer::chooseMove(const Board& b, Side s) const {

	// If no move is possible (i.e. all holes on Side s is empty)
	// return -1.
	if (b.beansInPlay(s) == 0) {
		//cerr << "There are no valid moves for this side." << endl;
		return -1;
	}

	// Assuming there are valid moves possible, prompt the player
	// to make a move.

	int chosenMove = randInt(1, b.holes());
	if (b.beans(s, chosenMove) > 0){
		return chosenMove;
	}
	else {
		return chooseMove(b, s);
	}

	return -999;
}

BadPlayer::~BadPlayer() {

}

SmartPlayer::SmartPlayer(std::string smartName) 
	:Player(smartName) {

}

bool SmartPlayer::isInteractive() const {
	return false;
}

int SmartPlayer::chooseMove(const Board& b, Side s) const {
	int bestHole;
	int value;
	int depth = 6;
	chooseMove(s, b, bestHole, value, depth);

	//cerr << "final value: " << value << endl;
	return bestHole;

	return -999; 
}

SmartPlayer::~SmartPlayer() {

}

int SmartPlayer::evaluate(const Board& b) const{
	int northPot = b.beans(NORTH, 0);
	int southPot = b.beans(SOUTH, 0);
	int northBeans = b.beansInPlay(NORTH);
	int southBeans = b.beansInPlay(SOUTH);
	int playingBeans = northBeans + southBeans;

	//cerr << endl << "North pot: " << northPot << ", SouthPot: " << southPot << ", playingBeans" << playingBeans << endl;

	if ((northPot + playingBeans) < southPot) return INT_MAX;

	else if ((southPot + playingBeans) < northPot) return INT_MIN;
	else if (playingBeans == 0 && northPot == southPot) return 0;
	else {
		int howGood = southPot - northPot;
		return howGood;
	}

	return -999;
}


void SmartPlayer::chooseMove(Side s, const Board& b, int& bestHole, int& value, int depth) const{
	if (b.beansInPlay(s) == 0) {
		Board tempBoard = b;
		for(int i = 0; i < tempBoard.holes(); i++){
			tempBoard.moveToPot(opponent(s), i, opponent(s));
		}
		bestHole = -1;
		value = evaluate(tempBoard);

		//cerr << string(2 * depth, ' ') << value << endl;
		return;
	}

	if (depth <= 0) {
		bestHole = -1;
		value = evaluate(b);
		//cerr << string(2 * depth, ' ') << value << endl;
		return;
	}

	int nodeNum = 1;
	depth--;
	for (int h = 1; h <= b.holes(); h++) {
		if (b.beans(s, h) > 0) {
			// "make" the hole h
			Board tempBoard = b;
			Side endSide;
			int endHole;
			tempBoard.sow(s, h, endSide, endHole);
			if (endSide == s) {
				if (endHole == 0) {
					int h1, v1;
					//depth--;
					chooseMove(s, tempBoard, h1, v1, depth);
				}
				else {
					if (tempBoard.beans(endSide, endHole) == 1 && tempBoard.beans(opponent(endSide), endHole) > 0) {
						tempBoard.moveToPot(endSide, endHole, s);
						tempBoard.moveToPot(opponent(endSide), endHole, s);
					}
				}
			}

			int h2, v2;
			chooseMove(opponent(s), tempBoard, h2, v2, depth);

			if (nodeNum == 1 || (s == NORTH && v2 < value) || (s == SOUTH && v2 > value)) {
				bestHole = h;
				value = v2;
			}

			// cerr << string(2 * depth, ' ') << value << endl;
			nodeNum++;
		}
		
	}

	return;
}
