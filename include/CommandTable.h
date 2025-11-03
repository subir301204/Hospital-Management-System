// CommandTable.h
#ifndef COMMANDTABLE_H
#define COMMANDTABLE_H

#include "Patient.h"
#include <map>
#include <functional>
#include <vector>

// Global variable for mode flag
extern bool inAdvancedMode;

// Global variable for Doctor mode flag
extern bool inDoctorMode;

// Function prototype
map<string, function<void()>> initializeCommands(vector<Patient> &data);

#endif // COMMANDTABLE_H
