#include <iostream>
#include <string>
#include "Patient.h"

using namespace std;

Patient::Patient(int pID, string nameOfPatient, int age, string sex, string admissionDate, string wordNo, string underDoctor) : pID(pID), nameOfPatient(nameOfPatient),  age(age), sex(sex), admissionDate(admissionDate), wordNo(wordNo), underDoctor(underDoctor) {}


int Patient::getID() const {
  return pID;
}

string Patient::getName() const {
  return nameOfPatient;
}

int Patient::getAge() const {
  return age;
}

string Patient::getSex() const {
  return sex;
}

string Patient::getAdmissionDate() const {
  return admissionDate;
}

string Patient::getWordNo() const {
  return wordNo;
}

string Patient::getUnderDoctor() const {
  return underDoctor;
}

void Patient::displayPatientDetails() const {
  cout << "\n=======Patient Details=======\n";
  cout << "Patient Name: " << getName() << "\n";
  cout << "Patient ID: " << getID() << "\n";
  cout << "Admission Date: " << getAdmissionDate() << "\n";
}
