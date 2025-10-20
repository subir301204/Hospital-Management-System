#ifndef UTILITY_H
#define UTILITY_H

#include "Patient.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <conio.h>

using namespace std;

// File handling functions
void saveToFile(const vector<Patient> &data);

// Function to load patient details to the program from the data/data.txt file
vector<Patient> loadFromFile();

/*
 * Function to search Patients in the system
 * It searches by taking the data base and patient id
*/
int searchPatient(const vector<Patient> &data, int id);

/*
 * Function to search Patients in the system
 * It searches by only taking the data base
*/
int searchPatient(vector<Patient> &data);

// Function to get hidden inputs
string getHiddenInput();

// Function to check password validity
bool checkPassword();

// Function to delete a specific record from the data/data.txt
void deleteRecord(vector<Patient> &data, const int lineIndex);

// Function to check admission date format validity
bool checkDateFormat(const string &date);

// Function to check Patient name validity
bool checkName(const string &name);

#endif
