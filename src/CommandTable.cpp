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


/*
          commands["details"] = [&]() {
                    cout << "\n=======Bank Details=======\n";
                    int index = searchAccount(accounts);
                    if (index != -1) {
                              if (pinValidity(accounts[index]))
                                        accounts[index].displayDetails();
                              else 
                                        cout << "\nInvalid PIN!!!\n";
                    }
                    else
                              cout << "\nAccount not found.\n";
          };

          commands["balance"] = [&]() {
                    cout << "\n=======Bank Balance=======\n";
                    int index = searchAccount(accounts);
                    if (index != -1) {
                              if (pinValidity(accounts[index]))
                                        accounts[index].displayBalance();
                              else
                                        cout << "\nInvalid PIN!!!\n";
                    }
                    else
                              cout << "\nAccount not found.\n";
          };

          commands["deposit"] = [&]() {
                    cout << "\n=======Deposit Money=======\n";
                    int index = searchAccount(accounts);
                    if (index != -1)
                              accounts[index].deposit();
                    else
                              cout << "\nAccount not found.\n";
          };

          commands["withdraw"] = [&]() {
                    cout << "\n=======Withdraw Money=======\n";
                    int index = searchAccount(accounts);
                    if (index != -1) {
                              if (pinValidity(accounts[index]))
                                        accounts[index].withdraw();
                              else
                                        cout << "\nInvalid PIN!!!\n";
                    }
                    else
                              cout << "\nAccount not found.\n";
          }; 

          commands["search"] = [&]() {
                    cout << "\n=======Search Account=======\n";
                    if (searchAccount(accounts) != -1)
                              cout << "\nAccount has been found.\n";
                    else
                              cout << "\nAccount not found.\n";
          };

          commands["transfer"] = [&]() {
                    cout << "\n=======Transfer From=======\n";
                    int index = searchAccount(accounts);
                    cout << "\n=======Transfer To=======\n";
                    int index2 = searchAccount(accounts);

                    if (index != -1 && index2 != -1) {
                              if (pinValidity(accounts[index]))
                                        accounts[index].transfer(accounts[index2]);
                              else
                                        cout << "\nInvalid PIN!!!\n";
                    }
                    else
                              cout << "\nAccount not found.\n";
          };
*/

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