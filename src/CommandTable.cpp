#include "Patient.h"
#include "Utility.h"
#include <iostream>
#include <map>
#include <functional>
#include <vector>
#include <limits>
#include <string>
#include <limits>
#include <fstream>

bool inAdvancedMode = false;

using namespace std;

// Function to initialize command table
map<string, function<void()>> initializeCommands(vector<Patient> &data) {
  map<string, function<void()>> commands;

  // Commands
  commands["create"] = [&]() {
    cout << "\n=======Creating An Account=======\n";
    int id;
    string admissionDate, nameOfPatient;
    cout << "Enter Patient ID: ";
    cin >> id;
    // Add input validation similar to Utility.cpp
    if (cin.fail()) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Invalid input. Please enter a number for the ID.\n";
      return;
    }

    int index = searchPatient(data, id);
    if (index == -1) {
      while (true) {
        cout << "Enter Admission Date (DD-MM-YYYY): ";
        cin >> admissionDate;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (checkDateFormat(admissionDate))
          break;
        else
          cerr << "\nError: Invalid date. Try again...\n\n";
      }

      cout << "Enter Patient Name: ";
      getline(cin, nameOfPatient);
      data.push_back(Patient(id, admissionDate, nameOfPatient));

      saveToFile(data);
      cout << "\nData saved.\n";
    }
    else
      cout << "\nAccount already exists!\n";
  };

  commands["details"] = [&]() {
    if (inAdvancedMode) {
      cout << "\n=======Patient Details=======\n";
      int index = searchPatient(data);
      if (index != -1)
        data[index].displayPatientDetails();
      else
        cout << "Patient not found!!!";
    }
    else
      cout << "\n##########Switch to Advanced Mode for this command##########\n";
  };

  commands["?"] = [&]() {
    if (!inAdvancedMode) {
      cout << "\n=======Available Commands=======\n";
      cout << " create    - Create a new account\n";
      cout << " cls       - Clears the screen\n";
      cout << " switch    - Switch between Normal and Advanced mode\n";
      cout << " ?         - Show all available commands\n";
      cout << " exit      - Exit the program\n";
    }
    else {
      cout << "\n=======Available Commands In Advanced Mode=======\n";
      cout << " create    - Create a new account\n";
      cout << " details   - Show Patient details\n";
      cout << " cls       - Clears the screen\n";
      cout << " list      - List of details of all patients\n";
      cout << " switch    - Switch between Normal and Advanced mode\n";
      cout << " delete    - Delete a specific Patient record\n";
      cout << " ?         - Show all available commands\n";
      cout << " exit      - Exit the program\n";
    }
  };

  commands["exit"] = [&]() {
    cout << "\nExiting the program...\n";
    cout << "\nGOODBYE!!!  :)\n\n";
    exit(0);
  };

  commands["cls"] = [&]() {
    system("cls");
  };

  commands["list"] = [&]() {
    if (inAdvancedMode) {
      ifstream file("data/data.txt");

      if (!file) {
        cout << "Unable to open the file!!!" << endl;
        return 1;
      }

      cout << "\n=======List Of Patients=======\n";

      string line;
      while (getline(file, line))
        cout << line << endl;
            
      file.close();
    }
    else
      cout << "\n##########Switch to Advanced Mode for this command##########\n";
  };

  commands["switch"] = [&]() {
    if (inAdvancedMode) {
      cout << "\n----------------------------\n\n";
      cout << "Switching to NORMAL Mode...\n";
      cout << "\n----------------------------\n";

      inAdvancedMode = false;
    }
    else {
      if (checkPassword()) {
        cout << "\n----------------------------\n\n";
        cout << "Switching to ADVANCED Mode...\n";
        cout << "\n----------------------------\n";

        inAdvancedMode = true;
      }
      else
        cout << "\n##########Access Denied##########\n";
    }
  };

  // Advanced commands

  commands["delete"] = [&]() {
    if (inAdvancedMode) {
      int index = searchPatient(data);
      deleteRecord(data, index);
    }
    else
      cout << "\n##########Switch to Advanced Mode for this command##########\n";
  };
          
  return commands;
}
