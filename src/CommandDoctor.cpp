/*
This file contains all Doctor Mode commends
This commands are only usable from the Doctor mode
*/

#include "Doctor.h"
#include "Utility.h"
#include "Getch_cross.h"
#include "CommandTable.h"
#include <iostream>
#include <map>
#include <functional>
#include <vector>
#include <limits>
#include <string>
#include <fstream>

using namespace std;

// Function to initialize the Doctor Command map
map<string, function<void()>> initializeDoctorCommands(vector<Doctor> &data2) {
  map<string, function<void()>> commands;

  // Command to create Doctor records
  commands["create"] = [&]() {
    if (inDoctorMode) {
      cout << "\n=======Create An Doctor's Record=======\n";
      int dID, experience, appointmentCount;
      string name, specialization, qualification, contactNumber, email, available;

      // Get the Doctor's ID form the user
      while (true) {
        cout << "Enter Doctor ID: ";
        cin >> dID;

        if (cin.fail()) {
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          cerr << "\nError: Please enter number values for Doctor's ID. Try again...\n\n";
          continue;
        }

        if (!checkDoctorID(dID)) {
          cerr << "\nError: Invalid Doctor ID. The ID should be of 7 digits. Try again...\n\n";
          continue;
        }

        if (searchDoctor(data2, dID)) {
          cerr << "\nError: Doctor already exist with the same ID. Try again...\n\n";
          continue;
        }

        break;
      }
      cin.ignore();

      // Get the Doctor's name from the user
      while (true) {
        cout << "Enter Doctor name: ";
        getline(cin, name);

        if (name.empty()) {
          cerr << "\nError: Doctor's name cannot be empty. Try again...\n\n";
          continue;
        }

        if (!checkDoctorName(name)) {
          cerr << "\nError: Invalid Doctor name, Names are only accepted. Try again...\n\n";
          continue;
        }

        break;
      }

      // Get Doctor's specialization
      while (true) {
        cout << "Enter Doctor Specialization: ";
        getline(cin, specialization);
        
        if (specialization.empty()) {
          cerr << "\nError: Doctor's specialization cannot be empty. Try again...\n\n";
          continue;
        }

        if (!isValidSpecialization(specialization)) {
          cerr << "\nError: Invalid Specialization.\n";
          displaySpecialization();
          cerr << "\nTry again...\n\n";
          continue;
        }

        break;
      }

      // Get Doctor's qualification from the user
      while (true) {
        cout << "Enter Doctor Qualification: ";
        getline(cin, qualification);

        if (qualification.empty()) {
          cerr << "\nError: Doctor's Qualification cannot be empty. Try again...\n\n";
          continue;
        }

        if (!isValidQualification(qualification)) {
          cerr << "\nError: Invalid Qualification.\n";
          displayQualification();
          cerr << "\nTry again...\n";
          continue;
        }

        break;
      }

      // Get Doctor's experience in terms of tears
      while (true) {
        cout << "Enter Doctor's Years of Experience: ";
        cin >> experience;

        if (cin.fail()) {
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          cerr << "\nError: Please enter numeric inputs for Doctor experience. Try again...\n\n";
          continue; 
        }

        if (!isValidExperience(experience)) {
          cerr << "\nError: Invalid Experience value. Try again...\n\n";
          continue;
        }

        break;
      }
      cin.ignore();

      // Get Doctor's contact number
      while (true) {
        cout << "Enter Doctor's Contact Number: ";
        getline(cin, contactNumber);

        if (contactNumber.empty()) {
          cerr << "\nError: Doctor's contact number cannot be empty. Try again...\n\n";
          continue;
        }

        if (!isValidContactNumber(contactNumber)) {
          cerr << "\nError: Invalid Contact Number. The number has to be of 10 digits and cannot start wil less than 6. Try again...\n\n";
          continue;
        }

        break;
      }

      // Get Doctor's email
      while (true) {
        cout << "Enter Doctor's email: ";
        getline(cin, email);

        if (email.empty()) {
          cerr << "\nError: Doctor's Email cannot be empty. Tru again...\n";
          continue;
        }

        if (!isValidEmail(email)) {
          cerr << "\nError: Invalid email. Try again...\n\n";
          continue;
        }

        break;
      }

      // Get Doctor's availability
      while (true) {
        cout << "Enter Doctor's Availability: ";
        getline(cin, available);

        if (available.empty()) {
          cerr << "\nError: Doctor's availability cannot be empty. Try again...\n\n";
          continue;
        }

        if (!isAvailable(available)) {
          cerr << "\nError: Invalid input. Try again...\n\n";
          continue;
        }

        break;
      }

      // Get Doctor's appointmentCount
      while (true) {
        cout << "Enter Doctor's Appointment Count: ";
        cin >> appointmentCount;

        if (cin.fail()) {
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          cerr << "\nError: Please enter a numeric value. Try again...\n\n";
          continue;
        }

        if (!isValidAppointmentCount(appointmentCount)) {
          cerr << "\nError: Invalid input. Try again...\n\n";
          continue;
        }

        break;
      }

      data2.push_back(Doctor(dID, name, specialization, qualification, experience, contactNumber, email, available, appointmentCount));

      saveToFile(data2);
      cout << "\nData saved.\n";
    }
    else
      cerr << "\n##########Switch to Doctor Mode to access this command##########\n";    
  };

  // Command to see a Doctor's details
  commands["details"] = [&]() {
    if (!inDoctorMode) {
      cerr << "\n##########Switch to Doctor Mode to access this command##########\n";
      return;
    }

    int index = searchDoctor(data2);
    if (index != -1) 
      data2[index].displayDetails();
    else
      cerr << "\nError: Doctor not found!!!\n\n";
  };

  // Command to see the list of all Doctor's details
  commands["list"] = [&]() {
    if (!inDoctorMode) {
      cerr << "\n##########Switch to Doctor Mode to access this command##########\n";
      return;
    }

    ifstream fin("data/dataDoctor.txt");

    if (!fin) {
      cerr << "\nError: Cannot open the file!!!\n\n";
      return;
    }

    cout << "\n=======List Of Doctors=======\n";

    string line;
    while (getline(fin, line))
      cout << line << endl;
    fin.close();
  };

  // Command to change the doctor mode password
  commands["changepassword"] = [&]() {
    if (!inDoctorMode) {
      cerr << "\n##########Switch to Doctor Mode to access this command##########\n";
      return;
    }

    changePassword("data/passwordDoctor.txt");
  };

  // Command to edit Doctor's fields
  commands["edit"] = [&]() {
    if (!inDoctorMode) {
      cerr << "\n##########Switch to Doctor Mode to access this command##########\n";
      return;
    }

    int index = searchDoctor(data2);
    if (index == -1)
      cerr << "\nError: Doctor not found.\n";

    cout << "\n=======Choice Menu=======\n";
    cout << "To chang Doctor's name enter 1\n";
    cout << "To change Doctor's specialization enter 2\n";
    cout << "To change Doctor's qualification enter 3\n";
    cout << "To change Doctor's experience enter 4\n";
    cout << "To change Doctor's contact number enter 5\n";
    cout << "To change Doctor's email enter 6\n";
    cout << "To change Doctor's availability enter 7\n";

    int ch;
    while (true) {
      cout << "Enter your choice: ";
      cin >> ch;

      if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << "\nError: Please enter numeric values only. Try again...\n\n";
        break;
      }
    }

    switch (ch) {
      case 1: {
        string newName;
        while (true) {
          cout << "Enter Doctor's new name: ";
          getline(cin, newName);

          if (newName.empty()) {
            cerr << "\nError: Doctor's name cannot be empty. Try again...\n\n";
            continue;
          }

          if (!checkDoctorName(newName)) {
            cerr << "\nError: Invalid Doctor name, Names are only accepted. Try again...\n\n";
            continue;
          }

          break;
        }

        data2[index].setName(newName);
        break;
      }

      case 2: {
        string newSpecialization;
        while (true) {
          cout << "Enter Doctor's new Specialization: ";
          getline(cin, newSpecialization);
          
          if (newSpecialization.empty()) {
            cerr << "\nError: Doctor's specialization cannot be empty. Try again...\n\n";
            continue;
          }

          if (!isValidSpecialization(newSpecialization)) {
            cerr << "\nError: Invalid Specialization.\n";
            displaySpecialization();
            cerr << "\nTry again...\n\n";
            continue;
          }

          break;
        }

        data2[index].setSpecialization(newSpecialization);
        break;
      }

      case 3: {
        string newQualification;
        while (true) {
          cout << "Enter Doctor's new Qualification: ";
          getline(cin, newQualification);

          if (newQualification.empty()) {
            cerr << "\nError: Doctor's Qualification cannot be empty. Try again...\n\n";
            continue;
          }

          if (!isValidQualification(newQualification)) {
            cerr << "\nError: Invalid Qualification.\n";
            displayQualification();
            cerr << "\nTry again...\n";
            continue;
          }

          break;
        }

        data2[index].setQualification(newQualification);
        break;
      }

      case 4: {
        int newExperience;
        while (true) {
          cout << "Enter Doctor's Updated Experience: ";
          cin >> newExperience;

          if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cerr << "\nError: Please enter numeric inputs for Doctor experience. Try again...\n\n";
            continue; 
          }

          if (!isValidExperience(newExperience)) {
            cerr << "\nError: Invalid Experience value. Try again...\n\n";
            continue;
          }

          break;
        }
        cin.ignore();

        data2[index].setExperience(newExperience);
        break;
      }
      
      case 5: {
        string newContactNumber;
        while (true) {
          cout << "Enter Doctor's new Contact Number: ";
          getline(cin, newContactNumber);

          if (newContactNumber.empty()) {
            cerr << "\nError: Doctor's contact number cannot be empty. Try again...\n\n";
            continue;
          }

          if (!isValidContactNumber(newContactNumber)) {
            cerr << "\nError: Invalid Contact Number. The number has to be of 10 digits and cannot start wil less than 6. Try again...\n\n";
            continue;
          }

          break;
        }

        data2[index].setContactNumber(newContactNumber);
        break;
      }

      case 6: {
        string newEmail;
        while (true) {
          cout << "Enter Doctor's new email: ";
          getline(cin, newEmail);

          if (newEmail.empty()) {
            cerr << "\nError: Doctor's Email cannot be empty. Tru again...\n";
            continue;
          }

          if (!isValidEmail(newEmail)) {
            cerr << "\nError: Invalid email. Try again...\n\n";
            continue;
          }

          break;
        }

        data2[index].setEmail(newEmail);
        break;
      }

      case 7: {
        string newAvailable;
        while (true) {
          cout << "Enter Doctor's Updated Availability: ";
          getline(cin, newAvailable);

          if (newAvailable.empty()) {
            cerr << "\nError: Doctor's availability cannot be empty. Try again...\n\n";
            continue;
          }

          if (!isAvailable(newAvailable)) {
            cerr << "\nError: Invalid input. Try again...\n\n";
            continue;
          }

          break;
        }

        data2[index].setAvailable(newAvailable);
        break;
      }

      default:
        cerr << "\nError: Invalid choice. Try again with the same command...\n\n";
    }

    saveToFile(data2);
  };

  // Command to get all available commands
  commands["?"] = [&]() {
    cout << "\n=======All available commands in Doctor mode=======\n";
    cout << " create          - To create a new Doctor's record.\n";
    cout << " details         - To see all details about a specific Doctor.\n";
    cout << " list            - To see all details of all the Doctors.\n";
    cout << " changepassword  - To change the Doctor mode password.\n";
    cout << " edit            - To edit any one field of a specific Doctor.\n";
    cout << " ?               - To see all available commands.\n";
    cout << " exit            - To exit from the program.\n";
  };
  
  return commands;
}