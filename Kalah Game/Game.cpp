#include <iostream>
#include <vector>

#include "Game.h"
#include "Board.h"
#include "Player.h"
#include "Side.h"

using namespace std;

class Board;
class Player;

Game::Game(const Board& b, Player* south, Player* north) {
	
	m_Board = new Board(b);
	m_Turn = SOUTH;
	failedMove = false;
	m_Players.push_back(north);
	m_Players.push_back(south);

}

void Game::display() const {

	vector<int> maxNumLength;
	int spacing = 0;
	for (int i = 1; i <= m_Board->holes(); i++) {
		int northBeanDigits = numDigits(m_Board->beans(NORTH, i));
		int southBeanDigits = numDigits(m_Board->beans(SOUTH, i));
		int maxBeanDigits = max(northBeanDigits, southBeanDigits);
		
		maxNumLength.push_back(maxBeanDigits);

		spacing += maxBeanDigits;
		if (i != m_Board->holes()) spacing += 2;
	}

	string northName = m_Players[NORTH]->name();
	string southName = m_Players[SOUTH]->name();
	string northPot = northName + "'s pot  " + to_string(m_Board->beans(NORTH, 0)) + "  ";
	string southPot = "  " + to_string(m_Board->beans(SOUTH, 0)) + "  " + southName + "'s pot";

	int indentation = northPot.size();
	int northHeader = indentation + (spacing - northName.size()) / 2;
	int southHeader = indentation + (spacing - southName.size()) / 2;

	for (int lines = 1; lines <= 5; lines++) {
		switch (lines) {
		case 1:
			for (int i = 0; i < northHeader; i++) std::cout << " ";
			std::cout << northName << endl;
			break;
		case 2:
			for (int i = 0; i < indentation; i++) std::cout << " ";
			for (int i = 1; i <= m_Board->holes(); i++) {
				int northBeanDigits = numDigits(m_Board->beans(NORTH, i));
				int maxBeanDigits = maxNumLength[i - 1];
				int x = maxBeanDigits - northBeanDigits;

				for (int j = 0; j < (x / 2); j++) std::cout << " ";
				if (x % 2 == 1) std::cout << " ";
				std::cout << m_Board->beans(NORTH, i);
				for (int j = 0; j < (x / 2); j++) std::cout << " ";

				std::cout << "  ";
			}
			std::cout << endl;
			break;
		case 3:
			std::cout << northPot;
			for (int i = 0; i < spacing; i++) std::cout << " ";
			std::cout << southPot << endl;

			break;
		case 4:
			for (int i = 0; i < indentation; i++) std::cout << " ";
			for (int i = 1; i <= m_Board->holes(); i++) {
				int southBeanDigits = numDigits(m_Board->beans(SOUTH, i));
				int maxBeanDigits = maxNumLength[i - 1];
				int x = maxBeanDigits - southBeanDigits;

				for (int j = 0; j < (x / 2); j++) std::cout << " ";
				if (x % 2 == 1) std::cout << " ";
				std::cout << m_Board->beans(SOUTH, i);
				for (int j = 0; j < (x / 2); j++) std::cout << " ";

				std::cout << "  ";
			}
			std::cout << endl;
			break;
		case 5:
			for (int i = 0; i < southHeader; i++) std::cout << " ";
			std::cout << southName << endl;
			break;
		}
	}


}

void Game::status(bool& over, bool& hasWinner, Side& winner) const {
	
	// if the current side has no beans on their side, the game is over.
	if (failedMove == true/*m_Board->beansInPlay(m_Turn) == 0*/) {
		over = true;
		
		// if the game has a winner (i.e. no tie), set hasWinner to true
		int southBeans = m_Board->beans(SOUTH, 0);
		int northBeans = m_Board->beans(NORTH, 0);
		if (southBeans != northBeans) {
			hasWinner = true;

			// set winner to the winning side
			if (southBeans > northBeans)
				winner = SOUTH;
			else
				winner = NORTH;
		}
		else
			hasWinner = false;
	}
	else
		over = false;
}

bool Game::move(Side s) {

	// if no beans on Side s, sweep remaining beans to s's opponent's pot
	// and return false

	if (m_Board->beansInPlay(s) == 0) {
		std::cout << m_Players[m_Turn]->name() << " has no beans left to sow." << endl;
		for (int i = 1; i <= m_Board->holes(); i++) {
			m_Board->moveToPot(opponent(s), i, opponent(s));
		}

		failedMove = true;
		return false;
	}

	// Evidently, there are still beans on side s. So we prompt the player
	// to make a valid move and try to complete it.
	int chosenHole = m_Players[s]->chooseMove(*m_Board, s);
	Side endSide;
	int endHole;
	
	// If we can sow the beans, we should check the following...
	if (m_Board->sow(s, chosenHole, endSide, endHole) == true) {
		if (m_Players[m_Turn]->isInteractive() == false) {
			cout << m_Players[m_Turn]->name() << " chooses hole " << chosenHole << endl;
		}
			

		// The following special cases only occur when the hole/pot is on the s's side.
		if (endSide == s) {
			// If last bean was placed in own pot give the player an extra turn.
			if (endHole == 0) {
				/*if (m_Players[m_Turn]->isInteractive() == false) {
					cout << "Press ENTER to continue.";
					cin.clear();
					cin.ignore(10000, '\n');
				}*/
				display();
				std::cout << m_Players[s]->name() << " gets an extra turn!" << endl;
				//display();
				return move(s);
			}
			else {
				// If last bean placed in own hole that was empty just a moment before
				// (i.e. there is only 1 bean currently in the hole after sowing)
				// and the opponent hole directly opposite is not empty, then the last
				// bean and all beans opposite are moved to player's pot.
				if (m_Board->beans(endSide, endHole) == 1 && m_Board->beans(opponent(endSide), endHole) > 0) {
					m_Board->moveToPot(endSide, endHole, s);
					m_Board->moveToPot(opponent(endSide), endHole, s);
				}
			}
		}
		return true;
	}

	return false;
}

void Game::play() {
	bool over;
	bool hasWinner;
	Side winner;

	display();

	if (!move(m_Turn)) {
		status(over, hasWinner, winner);
		cout << "Press ENTER to continue.";
		cin.clear();
		cin.ignore(10000, '\n');
		display();
		std::cout << "The game is now over. " << endl;
		if (hasWinner == true) {
			std::cout << "The winner is " << m_Players[winner]->name() << "! Congratulations!" << endl;
		}
		else {
			std::cout << "There are no winners: it's a tie!" << endl;
		}
	}
	
	else {
		// prompt the user to press ENTER if the player isn't a human (i.e. is a computer)
		if (m_Players[m_Turn]->isInteractive() == false) {
			cout << "Press ENTER to continue.";
			cin.clear();
			cin.ignore(10000, '\n');
		}

		m_Turn = opponent(m_Turn);
		play();
	}

}

int Game::beans(Side s, int hole) const {
	int numBeans = m_Board->beans(s, hole);
	return numBeans;
	return -9999;
}

int Game::numDigits(int num) const
{
	int digitCount = 0;
	int number = num;
	if (number == 0) digitCount++;
	for (; number > 0; digitCount++) {
		number = number / 10;
	}

	return digitCount;
}

Game::~Game() {
	delete m_Board;
}

Game::Game(const Game& other) :m_Turn(other.m_Turn), failedMove(other.failedMove) {
	m_Board = new Board(*other.m_Board);
	
	m_Players.push_back(other.m_Players[NORTH]);
	m_Players.push_back(other.m_Players[SOUTH]);
}

Game& Game::operator=(const Game& rhs) {
	if (this != &rhs) {
		Game temp(rhs);
		swap(temp);
	}
	return *this;
}

void Game::swap(Game& other) {
	// swap Board pointers
	Board* tempBoard = m_Board;
	m_Board = other.m_Board;
	other.m_Board = tempBoard;

	// swap north Player pointers
	Player* tempPlayer = m_Players[NORTH];
	m_Players[NORTH] = other.m_Players[NORTH];
	other.m_Players[NORTH] = tempPlayer;

	// swap south Player pointers
	tempPlayer = m_Players[SOUTH];
	m_Players[SOUTH] = other.m_Players[SOUTH];
	other.m_Players[SOUTH] = tempPlayer;

	// swap turns
	Side tempTurn = m_Turn;
	m_Turn = other.m_Turn;
	other.m_Turn = tempTurn;

	// swap failedMove value
	bool tempFailedMove = failedMove;
	failedMove = other.failedMove;
	other.failedMove = tempFailedMove;
}
