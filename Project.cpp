#include <iostream>

using namespace std;

int main() {
  int option = 0;
  bool gameOver = false;
  do {
    cout << "Hello! Welcome to the game of life in CMPT 1109. What would you "
            "like to do?"
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
      //
      break;
    case 2:
      //
      break;
    case 3:
      //
      break;
    case 4:
      //
      break;
    case 5:
      //
      break;
    case 6:
      //
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
