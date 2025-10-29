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