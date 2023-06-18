#include <iostream>
#include <stack>
using namespace std;


class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};


bool pathExists(char maze[][10], int sr, int sc, int er, int ec);
// Return true if there is a path from (sr,sc) to (er,ec)
// through the maze; return false otherwise


///////////////
// Implementation
///////////////

bool pathExists(char maze[][10], int sr, int sc, int er, int ec) {
    stack<Coord> coordStack;

    // push the starting coords onto the stack mark that we've been at the starting location
    Coord start(sr, sc);
    coordStack.push(start);
    maze[sr][sc] = '@';

    /*int popCounter = 0;*/

    while (!coordStack.empty()) {
        // look and remove the coordinate at the top of the stack
        Coord currentCoord = coordStack.top();
        int r = currentCoord.r();
        int c = currentCoord.c();
        coordStack.pop();

        // get first 12 (r, c) coordinates popped off the stack by the algorithm
        /*if (popCounter < 12) {
            cout << "(" << r << ", " << c << ")" << endl;
            popCounter++;
        }*/
        

        // we've reached the ending coordinate, so return true
        if (r == er && c == ec)
            return true;

        // check places we can move to from the current coord:
        // 
        // SOUTH
        if (maze[r + 1][c] == '.') {
            coordStack.push(Coord(r + 1, c));
            maze[r + 1][c] = '@';
        }
        
        // EAST
        if (maze[r][c + 1] == '.') {
            coordStack.push(Coord(r, c + 1));
            maze[r][c + 1] = '@';
        }

        // NORTH
        if (maze[r - 1][c] == '.') {
            coordStack.push(Coord(r - 1, c));
            maze[r - 1][c] = '@';
        }

        // WEST
        if (maze[r][c - 1] == '.') {
            coordStack.push(Coord(r, c - 1));
            maze[r][c - 1] = '@';
        }

    }

    

    return false;
}


////////// main

int main()
{
    char maze[10][10] = {
                { 'X','X','X','X','X','X','X','X','X','X' },
                { 'X','.','.','.','X','.','.','.','.','X' },
                { 'X','.','.','X','X','.','X','X','.','X' },
                { 'X','.','X','.','.','.','.','X','X','X' },
                { 'X','X','X','X','.','X','X','X','.','X' },
                { 'X','.','.','X','.','.','.','X','.','X' },
                { 'X','.','.','X','.','X','.','.','.','X' },
                { 'X','X','.','X','.','X','X','X','X','X' },
                { 'X','.','.','.','.','.','.','.','.','X' },
                { 'X','X','X','X','X','X','X','X','X','X' }
    };
    if (pathExists(maze, 3, 4, 8, 1))
        cout << "Solvable!" << endl;
    else
        cout << "Out of luck!" << endl;
    return 0;


    //debugging
    /*for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            cerr << maze[i][j];
        }
        cerr << endl;
    }*/
}
