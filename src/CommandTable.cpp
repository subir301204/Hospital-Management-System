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
    int id, age;
    string admissionDate, nameOfPatient, sex, wordNo, underDoctor;
    
    // Get the pID input from the user
    while (true) {
      cout << "Enter Patient ID: ";
      cin >> id;

      if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << "\nError: Please enter a numbers for patient ID. Try again...\n\n";
        continue;
      }

      if (!checkPatientID(id)) {
        cout << "\nError: Invalid Patient ID. The ID should be of 7 digits. Try again...\n\n";
        continue;
      }

      if (searchPatient(data, id) != -1) {
        cerr << "\nError: Patient already exist with the same ID. Try again...\n\n";
        continue;
      }
      
      break;
    }
    cin.ignore();   // Clean leftover newline buffer

    // Get the Patient name from the user
    while (true) {
      cout << "Enter Patient name: ";
      getline(cin, nameOfPatient);

      // Check if the entered name is empty or not
      if (nameOfPatient.empty()){
        cerr << "\nError: Patient name cannot be empty. Try again...\n\n";
        continue;
      }

      if (!checkName(nameOfPatient)) {
        cerr << "\nError: Invalid Patient name, Names are only accepted. Try again...\n\n";
        continue;
      }

      // End the loop
      break;
    }

    // Get age of the Patient from the user
    while (true) {
      cout << "Enter Patient age: ";
      cin >> age;

      if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << "\nError: Please enter a numbers for patient ID. Try again...\n\n";
        continue;
      }

      if (!isValidAge(age)) {
        cerr << "\nError: Invalid age. The age can't be negative. Try again...\n\n";
        continue;
      }

      break;
    }
    cin.ignore();

    // Get Patient's sex from the user
    while (true) {
      cout << "Enter Patient sex: ";
      cin >> sex;

      if (!isValidSex(sex)) {
        cerr << "\nnError: Invalid sex. Try again...\n\n";
        continue;
      }

      break;
    }

    // Get Patient's admission date from the user
    while (true) {
      cout << "Enter Admission Date (DD-MM-YYYY): ";
      cin >> admissionDate;

      // Check if the admission date is valid or not
      if (!checkDateFormat(admissionDate)) {
        cerr << "\nError: Invalid Admission Date. Try again...\n\n";
        continue;
      }

      // End the loop
      break;
    }

    // Get Patient's word no from the user
    while (true) {
      cout << "Enter Word No: ";
      cin >> wordNo;

      if (!isValidWord(wordNo)) {
        cerr << "\nError: Invalid Word NO. Try again...\n\n";
        continue;
      }

      break;
    }
    cin.ignore();

    // Get the doctor name under which the patient is
    while (true) {
      cout << "Enter Doctor name: ";
      getline(cin, underDoctor);

      // Check if the entered name is empty or not
      if (nameOfPatient.empty()){
        cerr << "\nError: Doctor name cannot be empty. Try again...\n\n";
        continue;
      }

      // End the loop
      break;
    }

    // Push details to the "data/data.txt" file
    data.push_back(Patient(id, nameOfPatient, age, sex, admissionDate, wordNo, underDoctor));

    // Save the file
    saveToFile(data);
    cout << "\nData saved.\n";
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
