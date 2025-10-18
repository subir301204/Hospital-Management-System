// Header for Patient
#ifndef PATIENT_H             // Include gard starting
#define PATIENT_H

#include <iostream>

using namespace std;

class Patient {
  private:
    int pID;
    string admissionDate;
    string nameOfPatient;

  public:
    // constructor
    Patient(int pID, string admissionDate, string nameOfPatient);

    // getter functions
    int getID() const;
    string getAdmissionDate() const;
    string getName() const;

    // display functions
    void displayPatientDetails() const;
};

#endif                        // Include gard ended
