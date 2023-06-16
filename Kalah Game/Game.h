#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
using namespace std;

#include "Side.h"
class Board;
class Player;

class Game {
public:
	Game(const Board& b, Player* south, Player* north);
	// Construct a Game to be played with the indicated players on a copy
	// of the board b. The player on the south side always moves first

	void display() const;
	// Display the game's board in a manner of your choosing, provided you
	// show the names of the players and a reasonable representation of the
	// state of the board

	void status(bool& over, bool& hasWinner, Side& winner) const;
	// If the game is over (i.e., the move member function has been called
	// and returned false), set over to true; otherwise, set over to false
	// and do not change anything else. If the game is over, set hasWinner
	// to true if the game has a winner, or false if it resulted in a tie.
	// If hasWinner is set to false, leave winner unchanged; otherwise, set
	// it to the winning side.

	bool move(Side s);
	// Attempt to make a complete move for the player playing side s.
	// "Complete" means that the player sows the seeds from a hole and takes
	// any additional turns required or completes a capture. Whenever the
	// player gets an additional turn, the board will be displayed so that
	// someone looking at the screen can follow what's happening. If the move
	// can be completed, return true; if not, because the move is not yet
	// completed by side s has no holes with beans to pick and sow, sweep any
	// beans in s's opponent's holes into the opponent's pot and return false.

	void play();
	// Play the game. Display the progress of the game so that someone looking
	// at the screen can follow what's happening. If neither player is interactive,
	// then to keep the display from quickly scrolling through the game, the viewer
	// will periodically be prompted to press ENTER to continue and not proceed
	// until ENTER is pressed. Announce the winner at the end of the game.

	int beans(Side s, int hole) const;
	// Return the number of beans in the indicated hole or pot of the game's
	// board, or -1 if the hole number is invalid. This function exists for
	// testing purposes.

	// Housekeeping
	~Game();
	Game(const Game& other);
	Game& operator=(const Game& rhs);

private:
	Board* m_Board;
	vector<Player*> m_Players;
	Side m_Turn;
	bool failedMove;

	// Helper functions
	int numDigits(int num) const;
	// counts how many digits in the number (doesn't accept leading zeroes)
	void swap(Game& other);


};

#endif
