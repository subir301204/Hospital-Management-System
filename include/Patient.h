// Header for Patient
#ifndef PATIENT_H             // Include gard starting
#define PATIENT_H

#include <iostream>

using namespace std;

class Patient {
  private:
    int pID;
    string nameOfPatient;
    int age;
    string sex;
    string admissionDate;
    string wordNo;
    string underDoctor;

  public:
    // constructor
    Patient(int pID, string nameOfPatient, int age, string sex, string admissionDate, string wordNo, string underDoctor);

    // getter functions
    int getID() const;
    string getName() const;
    int getAge() const;
    string getSex() const;
    string getAdmissionDate() const;
    string getWordNo() const;
    string getUnderDoctor() const;

    // display functions
    void displayPatientDetails() const;
};

#endif                        // Include gard ended
