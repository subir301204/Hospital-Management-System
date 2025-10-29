#include "Patient.h"
#include "Doctor.h"
#include "Utility.h"
#include "CommandTable.h"
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
  vector<Doctor> data2 = loadFromFileDoctor(); 
  auto commands = initializeCommands(data, data2);

  cout << "\nWelcome to CMD Banking System! Type '?' for commands\n";

  string cmd;
  while (true) {
    cout << (inAdvancedMode ? "\n[ADVANCED]>" : "\n>");
    cin >> cmd;

    if (commands.count(cmd))
      commands[cmd]();
    else
      cout << "\nUnknown command. Type 'help' for available commands\n";
  }

  return 0;
}
