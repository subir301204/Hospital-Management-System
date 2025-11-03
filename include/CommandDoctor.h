#ifndef COMMANDDOCTOR_H
#define COMMANDDOCTOR_H

#include "Doctor.h"
#include <map>
#include <functional>
#include <vector>

// Function to initialize the Doctor commands map
map<string, function<void()>> initializeDoctorCommands(vector<Doctor> &data2);

#endif