#include <iostream>
#include "Patient.h"

using namespace std;

Patient::Patient(int pID, string nameOfPatient, string admissionDate) : pID(pID), nameOfPatient(nameOfPatient), admissionDate(admissionDate) {}


int Patient::getID() const {
  return pID;
}

string Patient::getAdmissionDate() const {
  return admissionDate;
}

string Patient::getName() const {
  return nameOfPatient;
}

void Patient::displayPatientDetails() const {
  cout << "\n=======Patient Details=======\n";
  cout << "Patient Name: " << getName() << "\n";
  cout << "Patient ID: " << getID() << "\n";
  cout << "Admission Date: " << getAdmissionDate() << "\n";
}
