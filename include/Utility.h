#ifndef UTILITY_H
#define UTILITY_H

#include "Patient.h"
#include "Doctor.h"
#include "Getch_cross.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

/*
------------------------------------
Patient Utility Functions
------------------------------------
*/

// File handling functions
void saveToFile(const vector<Patient> &data);

// Overriding the saveToFile() function for Doctor class
void saveToFile(const vector<Doctor> &data2);

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
// string getHiddenInput();

// Function to check password validity
bool checkPassword();

// Function to delete a specific record from the data/data.txt
void deleteRecord(vector<Patient> &data, const int lineIndex);

// Function to check admission date format validity
bool checkDateFormat(const string &date);

// Function to check Patient name validity
bool checkName(const string &name);

// Function to check patient id validity
bool checkPatientID(const int &pID);

// Function to check age validity
bool isValidAge(const int &age);

// Function to check sex validity of the Patient
bool isValidSex(const string &sex);

// Function to check wordNo validity of the patient
bool isValidWord(const string &wordNo);

// Function to change the password 
void changePassword(); 

/*
-----------------------------------
Doctor utility functions
-----------------------------------
*/

// Function to load Doctor details from the file
vector<Doctor> loadFromFileDoctor();

// Function to check Doctor's pin validity
bool checkDoctorPin(const int &dID);

// Function to search doctor with dID
int searchDoctor(vector<Doctor> &data2, const int &dID);

// Function to search doctor without dID
int searchDoctor(vector<Doctor> &data2);

// Function to delete a Doctor record
void deleteDoctor(vector<Doctor> &data2, const int lineIndex);

// Function to check the name validity of Doctor
bool checkDoctorName(const string &name);

// Function to show the available specialization list
void displaySpecialization();

// Function to check the Doctor specialization validity
bool isValidSpecialization(const string &specialization);

// Function to display available doctor qualifications
void displayQualification();

// Function to check doctor's qualification validity
bool isValidQualification(const string &qualification);

#endif
