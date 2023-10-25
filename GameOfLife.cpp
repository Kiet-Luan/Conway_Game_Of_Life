#include <iostream>
#include <vector>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <string>

//Program for Game of Life
// Rules:
// 1. Randomly generated seed with 40% chance to live (size should be entered in by user) or read in a board from a bpm file (file specify by user).
// 2. Program should evolve over a 1000 iterations and at each iteration, the current board should be saved as a pbm file.
// 3. <=1 Neighbor, dies of lonliness.
// 4. 2 Neighbors, survives
// 5. 3 Neighbors will make a new occupied cell if unoccupied and if occupied, remain occupied.
// 6. >=4 Neighbors, dies by over crowding.

using namespace std;

void initializeBoard(vector<int> &board, int &nRows, int &nCols);
void writePBM(const string &filename, vector<int> *board, int nRows, int nCols);
vector<int>* advance(vector<int>* board, int nRows, int nCols);

int main () {
    int nRows, nCols;
    vector<int>* board = new vector<int> ();
    char ans;
	string bleh;
	int input;
	cout << "Welcome to the game of Life!" << endl;
	cout << "Would you like to use a starting file? (y/n)" << endl;
	cin >> ans;
	if (ans == 'Y' || ans == 'y') {
		string filename; //User input filename
		cout << "Enter the filename: " << endl;
		cin>>filename;
		ifstream fin;
		fin.open(filename.c_str());
			if (fin.is_open()) {
				fin >> bleh;
				fin >> nCols;
				fin >> nRows;
				while (fin >> input){
					board->push_back(input);
				}
				std::cout << "myvector stores " << int(board->size());
			} else {
				cout << "failed to open file !" << endl;
				exit (-1);
			}
		fin.close();
	} else {
	srand (time(0)); //Ensures Random Digits everytime
	cout << "How many Rows would you like?" << endl;
	cin >> nRows;
	cout << "How many Columns would you like?" << endl;
	cin >> nCols;
    	board = new vector<int> (nRows*nCols);
		for( int i=0; i<nRows; i++) {
			for( int j=0; j<nCols; j++) {
				double Spawn = double(rand())/double(RAND_MAX); // # between 0 and 1
					if (Spawn <= .4) {
						(*board)[(nCols)*i+j] = 1;
					} else {
						(*board)[(nCols)*i+j] = 0;
					}
			}
		}
}
		for (int generation=0; generation<1000; generation++) {
		char filename[15];
		sprintf(filename,"output%04d.pbm", generation);
		writePBM(string(filename), board, nRows, nCols);
		board = advance(board, nRows, nCols);
 		}
return 0;
}

void writePBM(const string &filename, vector<int> *board, int nRows, int nCols) {
    ofstream file;
    file.open(filename.c_str());
    file << "P1 " << endl;
    file << nCols << " " << nRows << endl;
    int lengthCounter = 0;
    for( int i=0; i<nRows; i++ ) {
        for( int j=0; j<nCols; j++ ) {
            file << " " << (*board)[nCols*i+j];
            // Limit the line length
	    // There can be no more than 70 characters per line
            lengthCounter++;
            if( lengthCounter == 30 ) {
                file << endl;
                lengthCounter = 0;
            }
        }
    }
    file << endl;
}


vector<int>* advance(vector<int> *board, int nRows, int nCols) {
	vector<int>* ret = new vector<int>(*board);
	for( int i=1; i<nRows-1; i++ ) {
		for( int j=1; j<nCols-1; j++ ) {
			int living_cell = 0;
			if ((*ret)[nCols*(i-1) + (j-1)] == 1)
				living_cell++;
			if ((*ret)[nCols*(i-1) + (j)] == 1)
				living_cell++;
			if ((*ret)[nCols*(i) + (j-1)] == 1)
				living_cell++;
			if ((*ret)[nCols*(i+1) + (j)] == 1)
				living_cell++;
			if ((*ret)[nCols*(i) + (j+1)] == 1)
				living_cell++;
			if ((*ret)[nCols*(i+1) + (j+1)] == 1)
				living_cell++;
			if ((*ret)[nCols*(i+1) + (j-1)] == 1)
				living_cell++;
			if ((*ret)[nCols*(i-1) + (j+1)] == 1)
				living_cell++;
			if ((*ret)[nCols*i+j] == 1 && living_cell < 2) { // Rule 3
				(*board)[nCols*i+j] = 0;
			}
			if ((*ret)[nCols*i+j] == 1 && (living_cell == 2 || living_cell == 3) ) { // Rule 4 & 5
				(*board)[nCols*i+j] = 1;
			}
			if ((*ret)[nCols*i+j] == 0 && living_cell == 2) { // Rule 4
				(*board)[nCols*i+j] = 0;
			}
			if ((*ret)[nCols*i+j] == 0 && living_cell == 3) { // Rule 5
				(*board)[nCols*i+j] = 1;
			}
			if (living_cell > 3) { // Rule 6
				(*board)[nCols*i+j] = 0;
			}
		}
	}
	return board;
}