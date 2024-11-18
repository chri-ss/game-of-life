/*
Author: CHRISTOPHER CRESSWELL, Ammar Chherawala, Austin Middleton
Student ID: 300400078, 300400622, 300407891
Purpose: Game of Life Project
Date: Nov 11, 2024
*/
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

const int GRID_SIZE = 30;

bool csvToArray(const string &, int[GRID_SIZE][GRID_SIZE]);
void printGrid(const int[GRID_SIZE][GRID_SIZE]);
void runGame(int[GRID_SIZE][GRID_SIZE]);
int testCell(bool, int, int, const int[GRID_SIZE][GRID_SIZE]);

int main() {
  int option = 0;
  int year;
  int gamesRun;
  bool gameOver = false;
  string filename = "startingGamestate.csv";
  int gameGrid[GRID_SIZE][GRID_SIZE];
  cout << "Hello! Welcome to the game of life in CMPT 1109." << endl;
  do {
    cout << "What would you like to do?" << endl
         << "To display the initial state for the game of life press 1" << endl
         << "To load a new initial state from a CSV file into memory press 2"
         << endl
         << "To play the game of life with the current initial state press 3"
         << endl
         << "To report summary statistics on all games played press 4" << endl
         << "To randomly play the game multiple times press 5" << endl
         << "To output the best initial board press 6" << endl
         << "To quit the program press 7" << endl;
    cin >> option;
    switch (option) {
    case 1:
      cout << "The current starting gamestate is: " << endl;
      csvToArray(filename, gameGrid);
      printGrid(gameGrid);
      // fileOutput(filename);
      break;
    case 2:
      cout << "Please enter the name of the file you would like to load: ";
      cin >> filename; // this, or we overwrite startingGamestate.csv with the
                       // chosen file? Might be easier to just overwrite when it
                       // comes to runGame() and best gamestate so far.

      year = 0;
      // if the file read is good
      if (csvToArray(filename, gameGrid)) {
        printGrid(gameGrid);
        cout << endl
             << "is this the game you would like to play? (y/n)" << endl;
        char confirmGame;
        do {
          cin >> confirmGame;
          if (confirmGame == 'y') {
            cout << "new game state loaded" << endl;

            cout << filename << endl;
          }
        } while (confirmGame != 'y' && confirmGame != 'n');
      } else {
        cout << "that file doesn't exist" << endl;
        cout << filename << endl;
      }
      break;
    case 3:
      // Call function, output file name to function. Do we want to try to call
      // funtion to convert csv to 2d array first and then throw the 2d array?
      csvToArray(filename, gameGrid);
      runGame(gameGrid);
      gamesRun++;
      break;
    case 4:
      // gameStats();
      break;
    case 5:
      // gamesRun += multipleGames();
      break;
    case 6:
      cout << "The best game start so far has been: " << endl;
      // fileOutput("bestGamestate.csv");
      break;
    case 7:
      gameOver = true;
      break;
    default:
      cout << "Sorry, that option doesn't exist. Please try again." << endl;
      break;
    }
  } while (!gameOver);
  return 0;
}

// output current gamestate to console, use in case 1, best gamestate, and
// rungame yearly
void fileOutput(string filename) {}

// output gamestats to console
void gameStats() {
  ifstream infile;
  infile.open("gameStats.csv");
}

// not sure if needed, could use in fileOutput() maybe?
bool csvToArray(const string &filename, int gameGrid[GRID_SIZE][GRID_SIZE]) {
  ifstream infile;
  infile.open(filename);
  if (infile.good()) {
    char current;
    for (int row = 0; row < GRID_SIZE; row++) {
      int col = 0;
      while (infile >> current) {
        if (current != ',') {
          gameGrid[row][col] = current - '0';
          col++;
        }
      }
    }
    return true;
  }
  return false;
}

void printGrid(const int gameGrid[GRID_SIZE][GRID_SIZE]) {
  // top of grid
  cout << ' ';
  for (int cell = 0; cell < GRID_SIZE; cell++) {
    cout << "_ ";
  }

  // middle
  cout << endl;
  for (int row = 0; row < GRID_SIZE; row++) {
    for (int col = 0; col < GRID_SIZE; col++) {
      if (gameGrid[row][col]) {
        cout << "|#";
      } else {
        cout << "|_";
      }
    }
    cout << "|" << endl;
  }
}

// create a randomized 30x30 csv file at startingGamestate.csv based on the
// input probability 2 for loops of 30, gen random 1 or 0 and input to slot 900
// times?
void randomGamestate(float probability) {
  ofstream outfile;
  outfile.open("startingGamestate.csv");

  // Generate a grid based on the probability and save it to the file
  for (int row = 0; row < GRID_SIZE; row++) {
    for (int col = 0; col < GRID_SIZE; col++) {
      int cell = (rand() / (RAND_MAX + 1.0)) < probability ? 1 : 0;
      outfile << cell;
      if (col < GRID_SIZE - 1) {
        outfile << ",";
      }
    }
    outfile << endl;
  }

  outfile.close();
}

int multipleGames() {
  int numberOfGames;
  float probability;
  cout << "How many times would you like to play the game? ";
  cin >> numberOfGames;
  cout << "What probability would you like for each cell to be alive? (1 = all "
          "alive, 0.5 = half alive): ";
  cin >> probability;

  for (int i = 0; i < numberOfGames; i++) {
    randomGamestate(probability);
    cout << "Playing game " << i + 1 << "..." << endl;
    int gameGrid[GRID_SIZE][GRID_SIZE];
    csvToArray("startingGamestate.csv", gameGrid);
    runGame(gameGrid); 
  }
  
  return numberOfGames;
}

// copy startingGamestate.csv to activeGamestate.csv, run game, keep track of
// final year results (how many cells alive, dead, how many years played),
// record to gamestats, if best alive at end, copy startingGamestate.csv to
// bestGamestate.csv
void runGame(int gameGrid[GRID_SIZE][GRID_SIZE]) {
  // while not halting
  int tempGrid[GRID_SIZE][GRID_SIZE];
  for (int row = 0; row < GRID_SIZE; row++) {
    for (int col = 0; col < GRID_SIZE; col++) {
      tempGrid[row][col] = testCell(gameGrid[row][col], row, col, gameGrid);
    }
  }

  // copy back into original gameGrid
  for (int row = 0; row < GRID_SIZE; row++) {
    for (int col = 0; col < GRID_SIZE; col++) {
      gameGrid[row][col] = tempGrid[row][col];
    }
  }
  printGrid(gameGrid);
}

int testCell(bool isAlive, int row, int col,
             const int gameGrid[GRID_SIZE][GRID_SIZE]) {
  if (row != 0 && col != 0 && row != GRID_SIZE - 1 && col != GRID_SIZE - 1) {
    int aliveNeighbourCount = 0;
    if (gameGrid[row - 1][col - 1] || gameGrid[row - 1][col] ||
        gameGrid[row - 1][col + 1]) {
      aliveNeighbourCount++;
    }
    if (gameGrid[row][col - 1]) {
      aliveNeighbourCount++;
    }
    if (gameGrid[row][col + 1]) {
      aliveNeighbourCount++;
    }
    if (gameGrid[row + 1][col - 1] || gameGrid[row + 1][col] ||
        gameGrid[row + 1][col + 1]) {
      aliveNeighbourCount++;
    }
    if (isAlive && aliveNeighbourCount < 2) {
      return 0;
    } else if (isAlive && aliveNeighbourCount == 2 ||
               aliveNeighbourCount == 3) {
      return 1;
    } else if (isAlive && aliveNeighbourCount > 3) {
      return 0;
    } else if (!isAlive && aliveNeighbourCount > 3) {
      return 1;
    }
  }
  return 0;

}
