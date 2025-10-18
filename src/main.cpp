#include "Patient.h"
#include "Utility.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <functional>

using namespace std;

map<string, function<void() >> initializeCommands(vector<Patient> &accounts);

// Main() function
int main() {
  vector<Patient> data = loadFromFile();
  auto commands = initializeCommands(data);

  cout << "\nWelcome to CMD Banking System! Type 'help' for commands\n";

  string cmd;
  while (true) {
    cout << "\n> ";
    cin >> cmd;

    if (commands.count(cmd))
      commands[cmd]();
    else
      cout << "\nUnknown command. Type 'help' for available commands\n";
  }

  return 0;
}
