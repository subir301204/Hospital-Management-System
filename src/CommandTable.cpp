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
      cout << "Enter Admission Date: ";
      cin >> admissionDate;

      cin.ignore(numeric_limits<streamsize>::max(), '\n');

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
    cout << "\n=======Patient Details=======\n";
    int index = searchPatient(data);
    if (index != -1)
      data[index].displayPatientDetails();
    else
      cout << "Patient not found!!!";
  };

  commands["help"] = [&]() {
    cout << "\n=======Available Commands=======\n";
    cout << " create    - Create a new account\n";
    cout << " details   - Show Patient details\n";
    cout << " cls       - Clears the screen\n";
    cout << " list      - List of details of all patients\n";
    cout << " help      - Show all available commands\n";
    cout << " exit      - Exit the program\n";
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
  }; 
          
  return commands;
}
