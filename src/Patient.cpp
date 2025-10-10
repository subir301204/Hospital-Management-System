#include <iostream>
#include "Patient.h"

using namespace std;

Patient::Patient(int pID, string admissionDate, string nameOfPatient) : pID(pID), admissionDate(admissionDate), nameOfPatient(nameOfPatient) {}


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