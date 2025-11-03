#ifndef COMMANDDOCTOR_H
#define COMMANDDOCTOR_H

#include "Doctor.h"
#include <map>
#include <functional>
#include <vector>

using namespace std;

extern bool inDoctorMode;

map<string, function<void()>> initializeDoctorCommands(vector<Doctor> &data2);

#endif