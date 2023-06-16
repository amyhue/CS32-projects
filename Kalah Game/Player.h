#ifndef PLAYER_H
#define PLAYER_H

#include <string>

#include "Side.h"

class Board;
//class Side;

class Player {
public:
	Player(std::string name);
	// Create a Player with the indicated name.

	std::string name() const;
	// Return the name of the player.
	
	virtual bool isInteractive() const;
	// Return false if the player is a computer player. Return true if
	// the player is human. Most kinds of players will be computer players

	virtual int chooseMove(const Board& b, Side s) const = 0;
	// Every concrete class derived from this class must implement this
	// function so that if the player were to be playing side s and had to
	// make a move given board b, the function returns the move the player
	// would choose. If no move is possible, return -1.

	virtual ~Player();
	// Since this class is designed as a base class, it should have a virtual
	// destructor

private:
	std::string m_Name;
};


class HumanPlayer : public Player{

public:
	HumanPlayer(std::string humanName);
	// Creates a HumanPlayer with the indicated name

	virtual bool isInteractive() const;
	// Return true, since the player is human.

	virtual int chooseMove(const Board& b, Side s) const;
	// Chooses its move by prompting a person running the program for a
	// move (reprompting if necessary until the person enters a valid hole
	// number) and returning that choice. If no move is possible, return -1.

	virtual ~HumanPlayer();
	// HumanPlayer destructor
};

class BadPlayer : public Player {

public:
	BadPlayer(std::string badName);
	// Creates a BadPlayer with the indicated name.

	virtual bool isInteractive() const;
	// Return false, since the player is a computer player, and, therefore,
	// is not human.

	virtual int chooseMove(const Board& b, Side s) const;
	// Chooses an arbitrary valid move and returns that choice. If no 
	// move is possible, return -1.

	virtual ~BadPlayer();
	// BadPlayer destructor

};

class SmartPlayer : public Player {

public:
	SmartPlayer(std::string smartName);
	// Creates a SmartPlayer with the indicated name.

	virtual bool isInteractive() const;
	// Return false, since the player is a computer player, and, therefore,
	// is not human.

	virtual int chooseMove(const Board& b, Side s) const;
	// Chooses the best valid move and returns that choice. If no move is
	// possible, return -1.

	virtual ~SmartPlayer();
	// SmartPlayer destructor
private:
	int evaluate(const Board& b) const;
	// Our heuristic function for determining how good a game state is for the current
	// side. How good a game state is for SOUTH is how good a game state is for NORTH,
	// and, conversely, how bad the game state is for SOUTH is how good a game state
	// is for NORTH. INT_MAX indicates a SOUTH win (NORTH loss), INT_MIN indicates
	// a SOUTH loss (NORTH win), and 0 indicates a tie (neither side wins). Numbers
	// larger than 0 indicate a SOUTH-favored board, and numbers less than 0 indicate
	// a NORTH-favored board.
	// 
	// Right now, the heuristic function simply compares how many beans are each
	// pot versus how many are on the board, and versus how many are on each side if
	// the difference in beans between the pots equals the number of beans on the
	// board.

	void chooseMove(Side s, const Board& b, int& bestHole, int& value, int depth) const;
	// Helper function that decides what move SmartPlayer should make based on
	// the current board state


};

#endif
