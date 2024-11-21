/*
Author: CHRISTOPHER CRESSWELL, Ammar Chherawala, Austin Middleton
Student ID: 300400078, 300400622, 300407891
Purpose: Game of Life Project
Date: Nov 11, 2024
*/
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <stdlib.h>
#include <string>
#include <thread>

using namespace std;

const int GRID_SIZE = 30;
const int YEAR_MAX = 50;
const float DEFAULT_PROBABILITY = 0.5;
const string bestGamestateFile = "bestGamestate.csv";
const string filename = "initialSetup.csv";

void csvToArray(const string &, int[GRID_SIZE][GRID_SIZE]);
void csvToArray(int[GRID_SIZE][GRID_SIZE]);
void printGrid(const int[GRID_SIZE][GRID_SIZE]);
void runGame(int &gamesRun);
int testCell(bool, int, int, const int[GRID_SIZE][GRID_SIZE]);
void saveGameStats(int, int, int);
int multipleGames(int &gamesRun);
double getRandomNumber();
bool fileVerify(string file);
void randomGamestate(float probability);
void loadNewFile(string newFileName, string oldFile);
void gameStats();
void printfile(const string file);

int main() {
  int option = 0;
  string loadFile;
  int gamesRun = 0;
  bool gameOver = false;

  cout << "Hello! Welcome to the game of life in CMPT 1109." << endl;
  do {
    cout << "What would you like to do?" << endl
         << "To generate or display the initial state for the game of life "
            "press 1"
         << endl
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
      fileVerify(filename);
      cout << "Would you like to randomly generate a new one? (1 = Yes, 2 = No)"
           << endl;
      do {
        cin >> option;
        if (option == 1) {
          randomGamestate(DEFAULT_PROBABILITY);
        }
      } while (option != 1 && option != 2);
      break;
    case 2:
      cout << "Please enter the name of the file you would like to load: ";
      cin >> loadFile;
      if (fileVerify(loadFile)) {
        cout << endl
             << "Is this the game you would like to play? (1 = Yes, 2 = No)"
             << endl;
        do {
          cin >> option;
          if (option == 1) {
            loadNewFile(loadFile, filename);
            cout << "New game state loaded:" << endl;
            cout << loadFile << endl;
          }
        } while (option != 1 && option != 2);
      }
      break;
    case 3:
      runGame(gamesRun);
      break;
    case 4:
      gameStats();
      break;
    case 5:
      multipleGames(gamesRun);
      break;
    case 6:
      cout << "The best game start so far has been: " << endl;
      // printfile(bestGamestateFile);
      fileVerify(bestGamestateFile);
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

// output gamestats to console
void gameStats() {
  ifstream infile("gameStats.csv");
  string line;

  if (infile.is_open()) {
    cout << "Game Statistics (All Games):" << endl;
    while (getline(infile, line)) {
      cout << line << endl;
    }
    infile.close();
  } else {
    cout << "Error: Unable to open gameStats.csv for reading." << endl;
  }
}

// not sure if needed, could use in fileOutput() maybe?
void csvToArray(const string &file, int gameGrid[GRID_SIZE][GRID_SIZE]) {
  ifstream infile;
  infile.open(file);
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
  }
}

void csvToArray(int gameGrid[GRID_SIZE][GRID_SIZE]) {
  csvToArray(filename, gameGrid);
}

bool fileVerify(string file) {
  ifstream infile;
  infile.open(file);
  if (infile.good()) {
    cout << "Verified starting gamestate: " << endl;
    printfile(file);
    return true;
  }
  cout << "Could not verify loaded file. " << endl;
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
double getRandomNumber() {
  random_device myRNG;
  uniform_real_distribution<> dist(0, 1);
  return dist(myRNG);
}

void printfile(const string file) {
  int gameGrid[GRID_SIZE][GRID_SIZE];
  csvToArray(file, gameGrid);
  printGrid(gameGrid);
}

void loadNewFile(string newFile, string oldFile) {
  ifstream infile;
  ofstream outfile;
  string line;

  infile.open(newFile);
  outfile.open(oldFile);

  while (getline(infile, line)) {
    outfile << line << endl;
  }
  infile.close();
  outfile.close();
}

// create a randomized 30x30 csv file at startingGamestate.csv based on the
// input probability 2 for loops of 30, gen random 1 or 0 and input to slot 900
// times?
void randomGamestate(float probability) {
  ofstream outfile;
  outfile.open(filename);
  // float cell;

  // Generate a grid based on the probability and save it to the file
  for (int row = 0; row < GRID_SIZE; row++) {
    for (int col = 0; col < GRID_SIZE; col++) {
      int cell = (getRandomNumber()) < probability ? 1 : 0;
      outfile << cell;
      if (col < GRID_SIZE - 1) {
        outfile << ",";
      }
    }
    // outfile << endl;
    outfile << '\n';
  }

  outfile.close();
}

int multipleGames(int &gamesRun) {
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
    runGame(gamesRun);
  }

  return numberOfGames;
}

// copy startingGamestate.csv to activeGamestate.csv, run game, keep track of
// final year results (how many cells alive, dead, how many years played),
// record to gamestats, if best alive at end, copy startingGamestate.csv to
// bestGamestate.csv
void runGame(int &gamesRun) {
  // while not haltig
  int gameGrid[GRID_SIZE][GRID_SIZE];
  bool sameGeneration = false;
  bool extinction = false;
  int year = YEAR_MAX;
  int yearsRun = 0;
  int aliveCount = 0;
  int deadCount = 0;
  bool hasChanged = true;

  if (!fileVerify(filename)) {
    cout << "ERROR: No gamestate file loaded.";
  }
  csvToArray(gameGrid);
  while (year >= 0 && !sameGeneration && !extinction && hasChanged) {
    int tempGrid[GRID_SIZE][GRID_SIZE];
    for (int row = 0; row < GRID_SIZE; row++) {
      for (int col = 0; col < GRID_SIZE; col++) {
        tempGrid[row][col] = testCell(gameGrid[row][col], row, col, gameGrid);

        // Count alive/dead cells for stats
        if (tempGrid[row][col] == 1) {
          aliveCount++;
        } else {
          deadCount++;
        }

        // Check if there was any change in cell state
        if (tempGrid[row][col] != gameGrid[row][col]) {
          hasChanged = true;
        }
      }
    }

    // check for no change between generations
    sameGeneration = true;
    for (int row = 0; row < GRID_SIZE; row++) {
      for (int col = 0; col < GRID_SIZE; col++) {
        if (gameGrid[row][col] != tempGrid[row][col]) {
          sameGeneration = false;
        }
      }
    }

    // copy back into original gameGrid
    for (int row = 0; row < GRID_SIZE; row++) {
      for (int col = 0; col < GRID_SIZE; col++) {
        gameGrid[row][col] = tempGrid[row][col];
      }
    }

    // check for extinction (all cells dead)
    for (int row = 0; row < GRID_SIZE; row++) {
      for (int col = 0; col < GRID_SIZE; col++) {
        if (gameGrid[row][col]) {
          extinction = false;
        }
      }
    }

    // system("clear");
    year--;
    this_thread::sleep_for(chrono::milliseconds(100));
    printGrid(gameGrid);
    yearsRun++;

    // Optional: Break if maximum years to prevent infinite runs
    if (yearsRun >= 1000) { // For example, a max year limit
      break;
    }
  }
  gamesRun++;
  saveGameStats(yearsRun, aliveCount, deadCount);
}

void bestGamestateTest(int isAlive) {
  string line;
  int recordInt = 0;
  fstream record;
  record.open(bestGamestateFile);
  for (int i = 0; i < GRID_SIZE; i++) {
    getline(record, line);
    for (int j = 0; j < line.size(); j++) {
      if (line[j] != ',') {
        recordInt += line[j] - '0';
      }
    }
  }
  if (recordInt < isAlive) {
    loadNewFile(filename, bestGamestateFile);
    record << isAlive;
  }
  record.close();
}

void saveGameStats(int yearsRun, int aliveCount, int deadCount) {
  ofstream outfile;
  outfile.open("gameStats.csv", std::ios_base::app);
  if (outfile.is_open()) {
    outfile << "Years: " << yearsRun << ", Alive: " << aliveCount
            << ", Dead: " << deadCount << endl;
    outfile.close();
    cout << "Game statistics saved to gameStats.csv" << endl;
    bestGamestateTest(aliveCount);
  } else {
    cout << "Error: Unable to open gameStats.csv." << endl;
  }
}

int testCell(bool isAlive, int row, int col,
             const int gameGrid[GRID_SIZE][GRID_SIZE]) {
  int aliveNeighbourCount = 0;
  // cells in middle of grid
  if (row != 0 && col != 0 && row != GRID_SIZE - 1 && col != GRID_SIZE - 1) {
    for (int i = col - 1; i <= col + 1; i++) {
      if (gameGrid[row - 1][i]) {
        aliveNeighbourCount++;
      }
    }
    if (gameGrid[row][col - 1]) {
      aliveNeighbourCount++;
    }
    if (gameGrid[row][col + 1]) {
      aliveNeighbourCount++;
    }
    for (int i = col - 1; i <= col + 1; i++) {
      if (gameGrid[row + 1][i]) {
        aliveNeighbourCount++;
      }
    }
    //  top left corner
  } else if (row == 0 && col == 0) {
    if (gameGrid[row][col + 1]) {
      aliveNeighbourCount++;
    }
    if (gameGrid[row + 1][col]) {
      aliveNeighbourCount++;
    }
    if (gameGrid[row + 1][col + 1]) {
      aliveNeighbourCount++;
    }
    // top right corner
  } else if (row == 0 && col == GRID_SIZE - 1) {
    if (gameGrid[row][col - 1]) {
      aliveNeighbourCount++;
    }
    if (gameGrid[row + 1][col]) {
      aliveNeighbourCount++;
    }
    if (gameGrid[row + 1][col - 1]) {
      aliveNeighbourCount++;
    }
    // somewhere in the top row
  } else if (row == 0 && col != 0 && col != GRID_SIZE - 1) {
    if (gameGrid[row][col - 1]) {
      aliveNeighbourCount++;
    }
    if (gameGrid[row][col + 1]) {
      aliveNeighbourCount++;
    }
    for (int i = col - 1; i <= col + 1; i++) {
      if (gameGrid[row + 1][i]) {
        aliveNeighbourCount++;
      }
    }
    // somewhere in the first column
  } else if (row != 0 && col == 0) {
    if (gameGrid[row - 1][col]) {
      aliveNeighbourCount++;
    }
    if (gameGrid[row + 1][col] == 0) {
      aliveNeighbourCount++;
    }
    for (int i = row - 1; i <= row + 1; i++) {
      if (gameGrid[i][col + 1]) {
        aliveNeighbourCount++;
      }
    }
    // somewhere in the last column
  } else if (row != 0 && col == GRID_SIZE - 1) {
    if (gameGrid[row - 1][col]) {
      aliveNeighbourCount++;
    }
    if (gameGrid[row + 1][col]) {
      aliveNeighbourCount++;
    }
    for (int i = row - 1; i <= row + 1; i++) {
      if (gameGrid[i][col - 1]) {
        aliveNeighbourCount++;
      }
    }
    // bottom left corner
  } else if (row == GRID_SIZE - 1 && col == 0) {
    if (gameGrid[row - 1][col]) {
      aliveNeighbourCount++;
    }
    if (gameGrid[row - 1][col + 1]) {
      aliveNeighbourCount++;
    }
    if (gameGrid[row][col + 1]) {
      aliveNeighbourCount++;
    }
    // bottom right corner
  } else if (row == GRID_SIZE - 1 && col == GRID_SIZE - 1) {
    if (gameGrid[row - 1][col - 1]) {
      aliveNeighbourCount++;
    }
    if (gameGrid[row - 1][col]) {
      aliveNeighbourCount++;
    }
    if (gameGrid[row][col - 1]) {
      aliveNeighbourCount++;
    }
    // somewhere in the last row
  } else if (row == GRID_SIZE - 1 && col != 0 && col != GRID_SIZE - 1) {
    for (int i = col - 1; i <= col + 1; i++) {
      if (gameGrid[row - 1][i]) {
        aliveNeighbourCount++;
      }
    }
    if (gameGrid[row][col - 1]) {
      aliveNeighbourCount++;
    }
    if (gameGrid[row][col + 1]) {
      aliveNeighbourCount++;
    }
  }
  if (isAlive && aliveNeighbourCount < 2) {
    return 0;
  } else if ((isAlive && aliveNeighbourCount == 2) ||
             aliveNeighbourCount == 3) {
    return 1;
  } else if (isAlive && aliveNeighbourCount > 3) {
    return 0;
  } else if (!isAlive && aliveNeighbourCount == 3) {
    return 1;
  } else {
    return 0;
  }
}
