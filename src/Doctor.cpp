#include "Doctor.h"
#include <iostream>
#include <string>

using namespace std;

Doctor::Doctor(int dID, string name, string specialization, string qualification, int experience, string contactNumber, string email, string available, int appointmentCount) : dID(dID), name(name), specialization(specialization), qualification(qualification), experience(experience), contactNumber(contactNumber), email(email), available(available), appointmentCount(appointmentCount) {}

int Doctor::getID() const {
  return dID;
}

string Doctor::getName() const {
  return name;
}

string Doctor::getSpecialization() const {
  return specialization;
}

string Doctor::getQualification() const {
  return qualification;
}

int Doctor::getExperience() const {
  return experience;
}

string Doctor::getContactNumber() const {
  return contactNumber;
}

string Doctor::getEmail() const {
  return email;
}

string Doctor::getAvailable() const {
  return available;
}

int Doctor::getAppointmentCount() const {
  return appointmentCount;
}

void Doctor::displayDetails() const {
  cout << "\n=======Doctor's Details=======\n";
  cout << "Doctor's Name: " << getName() << "\n";
  cout << "Doctor's ID: " << getID() << "\n";
  cout << "Doctor's Specialization: " << getSpecialization() << "\n";
  cout << "Doctor's Qualification: " << getQualification() << "\n";
  cout << "Years of Experience: " << getExperience() << "\n";
  cout << "Doctor's Contact Number: " << getContactNumber() << "\n";
  cout << "Doctor's Email: " << getEmail() << "\n";
  cout << "Is Doctor Available?: " << getAvailable() << "\n";
  cout << "Number of Appointments Doctor have: " << getAppointmentCount() << "\n";
}

void Doctor::setName(const string &newName) {
  name = newName;
}

void Doctor::setSpecialization(const string &newSpecialization) {
  specialization = newSpecialization;
}

void Doctor::setQualification(const string &newQualification) {
  qualification = newQualification;
}

void Doctor::setExperience(const int &newExperience) {
  experience = newExperience;
}

void Doctor::setContactNumber(const string &newContactNumber) {
  contactNumber = newContactNumber;
}

void Doctor::setEmail(const string &newEmail) {
  email = newEmail;
}

void Doctor::setAvailable(const string &newAvailable) {
  available = newAvailable;
}