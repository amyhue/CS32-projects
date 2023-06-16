#if defined(_MSC_VER)  &&  !defined(_DEBUG)
#include <iostream>
#include <windows.h>
#include <conio.h>

struct KeepWindowOpenUntilDismissed
{
	~KeepWindowOpenUntilDismissed()
	{
		DWORD pids[1];
		if (GetConsoleProcessList(pids, 1) == 1)
		{
			std::cout << "Press any key to close this window . . . ";
			_getch();
		}
	}
} keepWindowOpenUntilDismissed;
#endif


#include <iostream>
#include <string> 
#include <cassert>

#include "Side.h"
#include "Player.h"
#include "Board.h"
#include "Game.h"
using namespace std;

int main() {
	/*HumanPlayer bp1("Bart");
	HumanPlayer bp2("Homer");
	Board b(3, 0);
	b.setBeans(SOUTH, 1, 2);
	b.setBeans(SOUTH, 2, 2);
	b.setBeans(NORTH, 2, 1);
	b.setBeans(NORTH, 3, 2);
	Game g(b, &bp1, &bp2);*/

	/*HumanPlayer hp1("Human");
	SmartPlayer sp1("Smart Player");*/
	//Board b(6, 0);

	/*b.setBeans(NORTH, 0, 22);
	b.setBeans(NORTH, 1, 1);
	b.setBeans(NORTH, 5, 2);
	b.setBeans(SOUTH, 4, 1);
	b.setBeans(SOUTH, 5, 2);
	b.setBeans(SOUTH, 0, 20);*/

	//b.setBeans(SOUTH, 3, 2);
	//b.setBeans(SOUTH, 5, 1);
	//b.setBeans(SOUTH, 0, 20);
	//b.setBeans(NORTH, 0, 22);
	//b.setBeans(NORTH, 2, 1);
	//b.setBeans(NORTH, 5, 2);
	//Game g(b, &sp1, &hp1);

	//BadPlayer bp1("Bad Player 1");
	//SmartPlayer bp2("Bad Player 2");
	////SmartPlayer sp1("Smart Player");
	//Board b1(6, 4);
	////Game g(b, &bp1, &sp1);
	//Game g(b1, &bp1, &bp2);

	SmartPlayer sp1("SmartPlayer 1");
	SmartPlayer sp2("SmartPlayer 2");
	Board b(6, 4);
	//Game g(b, &hp1, &sp2);
	Game g(b, &sp1, &sp2);

	g.play();
	return 0;

	/*HumanPlayer hp1("Human");
	SmartPlayer sp1("Smart Player");
	Board b(6, 0);

	b.setBeans(SOUTH, 3, 2);
	b.setBeans(SOUTH, 5, 1);
	b.setBeans(SOUTH, 0, 20);
	b.setBeans(NORTH, 0, 22);
	b.setBeans(NORTH, 2, 1);
	b.setBeans(NORTH, 5, 2);

	Game g(b, &hp1, &sp1);

	g.play();
	return 0;*/

	//HumanPlayer bp11("Bart");
	//HumanPlayer bp12("Homer");
	//Board b1(3, 0);
	//b1.setBeans(SOUTH, 1, 2);
	////b.setBeans(SOUTH, 2, 2);
	//b1.setBeans(NORTH, 2, 1);
	//b1.setBeans(NORTH, 3, 2);
	//Game g1(b1, &bp11, &bp12);

	//HumanPlayer bp21("Marge");
	//BadPlayer bp22("Homer");
	//Board b2(3, 2);
	//Game g2(b2, &bp21, &bp22);

	//// testing copy constructor and assignment operator
	//g1.display();
	//g2.display();
	//Game g3(g1);
	//g3.display();
	//g3 = g2;
	//g3.display();


}
