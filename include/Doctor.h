#ifndef DOCTOR_H
#define DOCTOR_H

#include <iostream>
#include <string>

using namespace std;

class Doctor {
  private:
    int dID;
    string name;
    string specialization;
    string qualification;
    int experience;
    string contactNumber;
    string email;
    string available;
    int appointmentCount;
  
  public:
    Doctor(int dID, string name, string specialization, string qualification, int experience, string contactNumber, string email, string available, int appointmentCount);

    int getID() const;
    string getName() const;    
    string getSpecialization() const;
    string getQualification() const;
    int getExperience() const;
    string getContactNumber() const;
    string getEmail() const;
    string getAvailable() const;
    int getAppointmentCount() const;

    void displayDetails() const;
};

#endif