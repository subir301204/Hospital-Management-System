// CommandTable.h
#ifndef COMMANDTABLE_H
#define COMMANDTABLE_H

#include "Patient.h"
#include <map>
#include <functional>
#include <vector>

// Global variable for mode flag
extern bool inAdvancedMode;

// Function prototype
std::map<std::string, std::function<void()>> initializeCommands(std::vector<Patient> &data);

#endif // COMMANDTABLE_H
