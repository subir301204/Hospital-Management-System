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

    void setName(const string &newName);
    void setSpecialization(const string &newSpecialization);
    void setQualification(const string &newQualification);
    void setExperience(const int &newExperience);
    void setContactNumber(const string &newContactNumber);
    void setEmail(const string &newEmail);
    void setAvailable(const string &newAvailable);
};

#endif