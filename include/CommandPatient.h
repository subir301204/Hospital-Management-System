#ifndef COMMANDPATIENT_H
#define COMMANDPATIENT_H

#include "Patient.h"
#include <map>
#include <functional>
#include <vector>

map<string, function<void()>> initializePatientCommands(vector<Patient> &data);

#endif