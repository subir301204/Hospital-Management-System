#include "Patient.h"
#include "Doctor.h"
#include "Utility.h"
#include "CommandTable.h"
#include "CommandPatient.h"
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
  vector<Patient> data1 = loadFromFile();
  vector<Doctor> data2 = loadFromFileDoctor(); 
  auto commands = initializeCommands();
  auto commands1 = initializePatientCommands(data1);
  auto commands2 = initializeDoctorCommands(data2);

  cout << "\nWelcome to CMD Banking System! Type '?' for commands\n";

  string cmd;
  while (true) {
    if (inAdvancedMode)
      cout << "\n[PATIENT]> ";
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
      if (commands1.count(cmd))
        commands1[cmd]();
      else if (commands.count(cmd))
        commands[cmd]();
      else
        cout << "\nUnknown command. Type '?' for available commands\n";
    }
    else if (inDoctorMode) {
      if (commands2.count(cmd))
        commands2[cmd]();
      else if (commands.count(cmd))
        commands[cmd]();
      else
        cout << "\nUnknown command. Type '?' for available commands\n";
    }
  }

  return 0;
}
