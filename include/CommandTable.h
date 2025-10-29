// CommandTable.h
#ifndef COMMANDTABLE_H
#define COMMANDTABLE_H

#include "Patient.h"
#include "Doctor.h"
#include <map>
#include <functional>
#include <vector>

using namespace std;

// Global variable for mode flag
extern bool inAdvancedMode;

// Function prototype
map<string, function<void()>> initializeCommands(vector<Patient> &data, vector<Doctor> &data2);

#endif // COMMANDTABLE_H
