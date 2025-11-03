#include "Patient.h"
#include "Doctor.h"
#include "Utility.h"
#include "CommandTable.h"
#include "CommandDoctor.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <functional>

using namespace std;

// map<string, function<void() >> initializeCommands(vector<Patient> &accounts);

// Main() function
int main() {
  vector<Patient> data = loadFromFile();
  vector<Doctor> data2 = loadFromFileDoctor(); 
  auto commands = initializeCommands(data);
  auto commands2 = initializeDoctorCommands(data2);

  cout << "\nWelcome to CMD Banking System! Type '?' for commands\n";

  string cmd;
  while (true) {
    if (inAdvancedMode)
      cout << "\n[ADVANCE]> ";
    else if (inDoctorMode)
      cout << "\n[DOCTOR]> ";
    else
      cout << "\n> ";
    cin >> cmd;

    if (!inAdvancedMode && !inDoctorMode) {
      if (commands.count(cmd))
        commands[cmd]();
      else
        cout << "\nUnknown command. Type '?' for available commands\n";
    }
    else if (inAdvancedMode) {
      if (commands.count(cmd))
        commands[cmd]();
      else
        cout << "\nUnknown command. Type '?' for available commands\n";
    }
    else if (inDoctorMode) {
      if (commands2.count(cmd))
        commands2[cmd]();
      else
        cout << "\nUnknown command. Type '?' for available commands\n";
    }
  }

  return 0;
}
