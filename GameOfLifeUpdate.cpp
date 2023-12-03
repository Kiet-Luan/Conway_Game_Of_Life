#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>
#include <cstdlib>

using namespace std;

// Function declarations
void initializeBoard(vector<int> &board, int nRows, int nCols);
void writePBM(const string &filename, const vector<int> &board, int nRows, int nCols);
vector<int> advance(const vector<int> &board, int nRows, int nCols);

int main() {
    // Variable declarations
    int nRows, nCols;
    vector<int> board;

    char ans;
    string bleh;
    int input;

    // User prompt
    cout << "Welcome to the Game of Life!" << endl;
    cout << "Would you like to use a starting file? (y/n)" << endl;
    cin >> ans;

    // File input or random initialization
    if (ans == 'Y' || ans == 'y') {
        // File input
        string filename;
        cout << "Enter the filename: " << endl;
        cin >> filename;

        ifstream fin(filename);

        // Reading from file
        if (fin.is_open()) {
            fin >> bleh >> nCols >> nRows;
            while (fin >> input) {
                board.push_back(input);
            }
            cout << "Read " << board.size() << " values from the file." << endl;
        } else {
            cout << "Failed to open file!" << endl;
            exit(-1);
        }

        fin.close();
    } else {
        // Random initialization based on user input of Rows and Columns
        srand(time(0));
        cout << "How many Rows would you like?" << endl;
        cin >> nRows;
        cout << "How many Columns would you like?" << endl;
        cin >> nCols;

        initializeBoard(board, nRows, nCols);
    }

    // Generating images for each generation
    for (int generation = 0; generation < 1000; generation++) {
        // Creating output filename
        char filename[15];
        sprintf(filename, "output%04d.pbm", generation);

        // Writing current board state to a PBM file
        writePBM(string(filename), board, nRows, nCols);

        // Advancing to the next generation
        board = advance(board, nRows, nCols);
    }

    return 0;
}

// Function to initialize the board with random values
void initializeBoard(vector<int> &board, int nRows, int nCols) {
    board.resize(nRows * nCols);
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            // Randomly set the cell to be alive (1) or dead (0)
            double Spawn = static_cast<double>(rand()) / RAND_MAX;
            board[nCols * i + j] = (Spawn <= 0.4) ? 1 : 0;
        }
    }
}

// Function to write the current board state to a PBM file
void writePBM(const string &filename, const vector<int> &board, int nRows, int nCols) {
    ofstream file(filename);

    // PBM file header
    file << "P1" << endl;
    file << nCols << " " << nRows << endl;

    // Writing board values to the file
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            file << " " << board[nCols * i + j];
        }
        file << endl;
    }
}

// Function to advance the board to the next generation based on Game of Life rules
vector<int> advance(const vector<int> &board, int nRows, int nCols) {
    vector<int> nextBoard(board);

    // Iterating over each cell in the board
    for (int i = 1; i < nRows - 1; i++) {
        for (int j = 1; j < nCols - 1; j++) {
            int living_cell = 0;

            // Counting neighbors
            for (int di = -1; di <= 1; di++) {
                for (int dj = -1; dj <= 1; dj++) {
                    living_cell += board[nCols * (i + di) + (j + dj)];
                }
            }

            living_cell -= board[nCols * i + j]; // Exclude the current cell

            // Applying rules
            if (board[nCols * i + j] == 1 && (living_cell < 2 || living_cell > 3)) {
                nextBoard[nCols * i + j] = 0; // Rule 3 and Rule 6
            } else if (board[nCols * i + j] == 0 && living_cell == 3) {
                nextBoard[nCols * i + j] = 1; // Rule 5
            }
        }
    }

    return nextBoard;
}
