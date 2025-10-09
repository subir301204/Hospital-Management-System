#ifndef UTILITY_H
#define UTILITY_H

#include "Patient.h"
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

// File handling functions
void saveToFile(const vector<Patient> &data);

vector<Patient> loadFromFile();

int searchPatient(const vector<Patient> &data, int id);

int searchPatient(vector<Patient> &data);

#endif