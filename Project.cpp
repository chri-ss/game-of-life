/*
Author: CHRISTOPHER CRESSWELL, Ammar Chherawala, Austin Middleton
Student ID: xxxx, xxxx, 300407891
Purpose: Game of Life Project
Date: Nov 11, 2024
*/
#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int main() {
  int option = 0;
  int gamesRun;
  bool gameOver = false;
  string filename = "startingGamestate.csv";
  cout << "Hello! Welcome to the game of life in CMPT 1109." << endl;
  do {
    cout << "What would you like to do?"
         << endl
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
      fileOutput(filename);
      break;
    case 2:
      "Please enter the name of the file you would like to load: ";
      cin >> filename; //this, or we overwrite startingGamestate.csv with the chosen file? Might be easier to just overwrite when it comes to runGame() and best gamestate so far.
      break;
    case 3:
      //Call function, output file name to function. Do we want to try to call funtion to convert csv to 2d array first and then throw the 2d array?
      runGame(filename);
      gamesRun++;
      break;
    case 4:
      gameStats();
      break;
    case 5:
      gamesRun += multipleGames();
      break;
    case 6:
      cout << "The best game start so far has been: " << endl;
      fileOutput("bestGamestate.csv");
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

//output current gamestate to console, use in case 1, best gamestate, and rungame yearly
void fileOutput(string filename){

}

//not sure if needed, could use in fileOutput() maybe?
bool csvToArray(string filename){
  ifstream infile;
  infile.open(filename);
  static bool array[30][30];
}

//output gamestats to console
void gameStats(){
  ifstream infile;
  infile.open("gameStats.csv");

}

//create a randomized 30x30 csv file at startingGamestate.csv based on the input probability
//2 for loops of 30, gen random 1 or 0 and input to slot 900 times?
void randomGamestate(float probability){

}

//should be completed
int multipleGames(){
  int probability;
  int numberOfGames;
  string filename = "startingGamestate.csv";
  cout << "How many times would you like to play the game?";
  cin >> numberOfGames;
  cout << "What probability would you like for each cell to be alive? (1 = all alive, 0.5 = half alive)";
  cin >> probability;
  for (int i = numberOfGames; i > 0; i--){
    randomGamestate(probability);
    runGame(filename);
  }
  return numberOfGames;
}

//copy startingGamestate.csv to activeGamestate.csv, run game, keep track of final year results (how many cells alive, dead, how many years played), record to gamestats, if best alive at end, copy startingGamestate.csv to bestGamestate.csv
void runGame(string filename){

}