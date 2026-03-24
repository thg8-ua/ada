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





