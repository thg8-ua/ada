#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <climits>
#include <algorithm>
using namespace std;
void argParser(int argc, char* argv[], bool &t, bool &p2D, bool &ignoreNaive, fstream &fileName);
int maze_naive(const vector<vector<int>>& maze, int i, int j, int n, int m);
int maze_memo(const vector<vector<int>>& maze, int i, int j, int n, int m);
int maze_it_matrix(const vector<vector<int>>& maze, int n, int m);
int maze_it_vector(const vector<vector<int>>& maze, int n, int m);
bool maze_parser(const string &filename, int &n, int &m, vector<vector<int>> &maze);



int main(int argc, char* argv[])
{
    bool t = false;
    bool p2D = false;
    bool ignoreNaive = false;
    fstream fileName;
    argParser(argc,argv,t,p2D,ignoreNaive,fileName);
    

    return 0;
}


void argParser(int argc, char* argv[], bool &t, bool &p2D, bool &ignoreNaive, fstream &fileName) {
    int i = 1;
    while (i < argc) {
	string arg = argv[i];
	if (arg == "-t") t = true;
	else if (arg == "-p2D") p2D = true;
	else if (arg == "--ignore-naive") ignoreNaive = true;
	else if (arg == "-f") {
	    if (i+1<argc) {
	        fileName.open(argv[i+1]);
		if (!fileName.is_open()) {
	        cerr << "ERROR: can't open file: " << argv[i+1] << "." << endl << "Usage: " << endl << "maze [--p2D] [-t] [--ignore-naive] -f file" << endl;
		exit(1);
		}
	        i++;
	    } else {
	        cerr << "ERROR: Missing filename." << endl << "Usage: " << endl << "maze [--p2D] [-t] [--ignore-naive] -f file" << endl;

		exit(1);
            }
	} 
	else {
	    cerr << "ERROR: unknown option: " << arg << endl;
	    exit(1);
	}
	i++;
    }
}





bool maze_parser(const string &filename, int &n, int &m, vector<vector<int>> &maze) {
    ifstream file(filename);
    if (!file) return false;

    if (!(file >> n >> m)) return false;

    maze.assign(n, vector<int>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (!(file >> maze[i][j])) return false;

    return true;
}


// Naive recursive: find max-gold path from (i,j) to (n-1,m-1).
// Returns -1 if no path exists (out of bounds or blocked cell).
int maze_naive(const vector<vector<int>>& maze, int i, int j, int n, int m) {
    if (i >= n || j >= m) return -1;
    if (maze[i][j] == 0) return -1;
    if (i == n-1 && j == m-1) return maze[i][j];

    int down  = maze_naive(maze, i+1, j, n, m);
    int right = maze_naive(maze, i, j+1, n, m);

    if (down == -1 && right == -1) return -1;
    int best = (down == -1) ? right : (right == -1) ? down : max(down, right);
    return maze[i][j] + best;
}


// Memoized recursive: same semantics as maze_naive but caches results.
// Sentinel -2 means "not yet computed"; -1 means "no path".
// The memo table is reset whenever i==0 and j==0.
static vector<vector<int>> memo_table;

int maze_memo(const vector<vector<int>>& maze, int i, int j, int n, int m) {
    if ((int)memo_table.size() != n || (int)memo_table[0].size() != m || (i == 0 && j == 0))
        memo_table.assign(n, vector<int>(m, -2));

    if (i >= n || j >= m) return -1;
    if (maze[i][j] == 0) return -1;
    if (i == n-1 && j == m-1) return memo_table[i][j] = maze[i][j];
    if (memo_table[i][j] != -2) return memo_table[i][j];

    int down  = maze_memo(maze, i+1, j, n, m);
    int right = maze_memo(maze, i, j+1, n, m);

    int result;
    if (down == -1 && right == -1) result = -1;
    else if (down == -1) result = maze[i][j] + right;
    else if (right == -1) result = maze[i][j] + down;
    else result = maze[i][j] + max(down, right);

    return memo_table[i][j] = result;
}

