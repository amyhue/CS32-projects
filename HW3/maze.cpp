//#include <iostream>
//#include <cassert>
//using namespace std;

// !*** delete everything above

//class Coord
//{
//public:
//    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
//    int r() const { return m_r; }
//    int c() const { return m_c; }
//private:
//    int m_r;
//    int m_c;
//};

bool pathExists(char maze[][10], int sr, int sc, int er, int ec) {

    // If the start location == end location, we've solved the maze. Return true.
    if (sr == er && sc == ec)
        return true;

    // Mark the start coord as visted
    maze[sr][sc] = '@';


    // SOUTH = 0; EAST = 1; NORTH = 2; WEST = 3
    for (int i = 0; i < 4; i++) {
        switch (i) {
        // SOUTH
        case 0:
            if (maze[sr + 1][sc] == '.')
                if (pathExists(maze, sr + 1, sc, er, ec))
                    return true;
            break;
        // EAST
        case 1:
            if (maze[sr][sc + 1] == '.')
                if (pathExists(maze, sr, sc + 1, er, ec))
                    return true;
            break;

        // NORTH 
        case 2:
            if (maze[sr - 1][sc] == '.')
                if (pathExists(maze, sr - 1, sc, er, ec))
                    return true;
            break;
        // WEST
        case 3:
            if (maze[sr][sc - 1] == '.')
                if (pathExists(maze, sr, sc - 1, er, ec))
                    return true;
            break;
        }
    }
    return false;
}

// !*** delete everything below

//int main() {
//	char maze1[10][10] = {
//  { 'X','X','X','X','X','X','X','X','X','X' },
//  { 'X','.','X','.','.','X','.','.','.','X' },
//  { 'X','.','X','X','.','X','.','X','X','X' },
//  { 'X','.','.','.','.','X','.','X','.','X' },
//  { 'X','X','.','X','.','X','.','.','.','X' },
//  { 'X','X','X','.','.','X','.','X','.','X' },
//  { 'X','.','.','.','X','.','.','.','X','X' },
//  { 'X','.','X','X','.','.','X','.','X','X' },
//  { 'X','.','.','.','.','X','.','.','.','X' },
//  { 'X','X','X','X','X','X','X','X','X','X' },
//	};
//
//	char maze2[10][10] = {
//	  { 'X','X','X','X','X','X','X','X','X','X' },
//	  { 'X','.','X','.','.','X','.','.','.','X' },
//	  { 'X','X','X','X','.','X','.','X','X','X' },
//	  { 'X','.','.','.','.','X','.','X','.','X' },
//	  { 'X','X','.','X','.','X','.','.','.','X' },
//	  { 'X','X','X','.','.','X','.','X','.','X' },
//	  { 'X','.','.','.','X','.','.','.','X','X' },
//	  { 'X','.','X','X','.','.','X','.','X','X' },
//	  { 'X','.','.','.','.','X','.','.','.','X' },
//	  { 'X','X','X','X','X','X','X','X','X','X' },
//	};
//
//	char maze3[10][10] = {
//	  { 'X','X','X','X','X','X','X','X','X','X' },
//	  { 'X','X','.','.','.','.','.','X','X','X' },
//	  { 'X','.','.','X','X','.','.','.','.','X' },
//	  { 'X','.','.','.','X','.','.','.','X','X' },
//	  { 'X','.','X','.','X','X','X','.','.','X' },
//	  { 'X','X','X','X','.','.','X','.','.','X' },
//	  { 'X','X','.','.','.','.','X','.','.','X' },
//	  { 'X','.','.','.','.','.','.','.','X','X' },
//	  { 'X','.','.','X','X','X','X','X','X','X' },
//	  { 'X','X','X','X','X','X','X','X','X','X' },
//	};
//
//	char maze4[10][10] = {
//	  { 'X','X','X','X','X','X','X','X','X','X' },
//	  { 'X','X','.','.','.','.','.','X','X','X' },
//	  { 'X','.','.','X','X','.','.','.','.','X' },
//	  { 'X','.','.','.','X','.','.','.','X','X' },
//	  { 'X','.','X','.','X','X','X','.','.','X' },
//	  { 'X','X','X','X','.','.','X','.','.','X' },
//	  { 'X','X','.','.','.','.','X','.','.','X' },
//	  { 'X','.','X','.','.','.','.','.','X','X' },
//	  { 'X','.','.','X','X','X','X','X','X','X' },
//	  { 'X','X','X','X','X','X','X','X','X','X' },
//	};
//
//	char maze5[10][10] = {
//	  { 'X','X','X','X','X','X','X','X','X','X' },
//	  { 'X','X','.','X','.','.','.','X','X','X' },
//	  { 'X','.','.','X','X','.','.','.','.','X' },
//	  { 'X','.','.','.','X','.','.','.','X','X' },
//	  { 'X','.','X','.','X','X','X','.','.','X' },
//	  { 'X','X','X','X','.','.','X','.','.','X' },
//	  { 'X','X','.','.','.','.','X','.','.','X' },
//	  { 'X','.','X','.','.','.','.','.','X','X' },
//	  { 'X','.','.','X','X','X','X','X','X','X' },
//	  { 'X','X','X','X','X','X','X','X','X','X' },
//	};
//
//	assert(pathExists(maze1, 8, 6, 1, 1));
//	assert(!pathExists(maze2, 8, 6, 1, 1));
//	assert(pathExists(maze3, 4, 3, 7, 1));
//	assert(!pathExists(maze4, 4, 3, 7, 1));
//	//assert(!pathExists(maze5, 2, 1, 9, 1));
//	assert(pathExists(maze5, 2, 1, 2, 2));
//
//}
