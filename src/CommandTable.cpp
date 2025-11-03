/*
This file contains all universal commands 
This commands can be used in any mode
*/
#include "Utility.h"
#include "CommandPatient.h"
#include "CommandDoctor.h"
#include <iostream>
#include <map>
#include <functional>
#include <vector>
#include <limits>
#include <string>
#include <limits>
#include <fstream>

// Mode detecting external variables
bool inAdvancedMode = false;
bool inDoctorMode = false;

using namespace std;

// Function to initialize command table
map<string, function<void()>> initializeCommands() {
  map<string, function<void()>> commands;

  // Command to see all available commands in the Normal mode
  commands["?"] = [&]() {
    cout << "\n=======Available Commands In NORMAL Mode=======\n";
    cout << " create            - Create a new Patient record\n";
    cout << " cls               - Clears the screen\n";
    cout << " switch            - Switch between Normal and Advanced mode\n";
    cout << " ?                 - Show all available commands\n";
    cout << " exit              - Exit the program\n";
  };

  // Command to exit from the program 
  commands["exit"] = [&]() {
    cout << "\nExiting the program...\n";
    cout << "\nGOODBYE!!!\n\n";
    exit(0);
  };

  // Command to switch between modes
  commands["switch"] = [&]() {
    if (inAdvancedMode || inDoctorMode) {
      cout << "\n--------------------------------\n";
      cout << "Switching to NORMAL mode...";
      cout << "\n--------------------------------\n";

      inAdvancedMode = false;
      inDoctorMode = false;
      return;
    }

    cout << "\n==========Choice Menu==========\n";
    cout << "Enter 1 to switch into Patient mode.\n";
    cout << "Enter 2 to switch into Doctor mode.\n";

    cout << "Enter your choice: ";
    int ch;
    cin >> ch;

    if (cin.fail()) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cerr << "\nError: Please enter only numeric values. Try again with the same command...\n\n";
      return;
    }

    switch (ch) {
      case 1: {
        if (checkPassword("data/password.txt")) {
          cout << "\n--------------------------------\n";
          cout << "Switching to PATIENT mode...";
          cout << "\n--------------------------------\n";

          inAdvancedMode = true;
        }
        break;
      }
      case 2: {
        if (checkPassword("data/passwordDoctor.txt")) {
          cout << "\n--------------------------------\n";
          cout << "Switching to DOCTOR mode...";
          cout << "\n--------------------------------\n";

          inDoctorMode = true;
        }
        break;
      }
      default: {
        cerr << "\nError: Invalid choice. Try again with the same command...\n\n";
        return;
      }
    }
  };

  // Command to clear screen 
  commands["cls"] = [&]() {
    system("clear");
  };

  return commands;
}
