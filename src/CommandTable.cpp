#include "Patient.h"
#include "Utility.h"
#include <iostream>
#include <map>
#include <functional>
#include <vector>
#include <limits>
#include <string>


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

                              cout << "Enter Patient Name: ";
                              cin >> nameOfPatient;
                              data.push_back(Patient(id, admissionDate, nameOfPatient));
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
                    cout << " help      - Show all available commands\n";
                    cout << " exit      - Save and exit the program\n";
          };

          commands["exit"] = [&]() {
                    saveToFile(data);
                    cout << "\nData saved. Exiting program...\n";
                    exit(0);
          };

          return commands;
}