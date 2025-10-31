#include "Patient.h"
#include "Utility.h"
#include "Getch_cross.h"
#include <iostream>
#include <map>
#include <functional>
#include <vector>
#include <limits>
#include <string>
#include <limits>
#include <fstream>

bool inAdvancedMode = false;
bool inDoctorMode = false;

using namespace std;

// Function to initialize command table
map<string, function<void()>> initializeCommands(vector<Patient> &data, vector<Doctor> &data2) {
  map<string, function<void()>> commands;

  // All UNIVERSAL Commands
  commands["create"] = [&]() {
    cout << "\n=======Creating An Account=======\n";
    int id, age;
    string admissionDate, nameOfPatient, sex, wordNo, underDoctor;
    
    // Get the pID input from the user
    while (true) {
      cout << "Enter Patient ID: ";
      cin >> id;

      if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << "\nError: Please enter a numbers for patient ID. Try again...\n\n";
        continue;
      }

      if (!checkPatientID(id)) {
        cout << "\nError: Invalid Patient ID. The ID should be of 7 digits. Try again...\n\n";
        continue;
      }

      if (searchPatient(data, id) != -1) {
        cerr << "\nError: Patient already exist with the same ID. Try again...\n\n";
        continue;
      }
      
      break;
    }
    cin.ignore();   // Clean leftover newline buffer

    // Get the Patient name from the user
    while (true) {
      cout << "Enter Patient name: ";
      getline(cin, nameOfPatient);

      // Check if the entered name is empty or not
      if (nameOfPatient.empty()){
        cerr << "\nError: Patient name cannot be empty. Try again...\n\n";
        continue;
      }

      if (!checkName(nameOfPatient)) {
        cerr << "\nError: Invalid Patient name, Names are only accepted. Try again...\n\n";
        continue;
      }

      // End the loop
      break;
    }

    // Get age of the Patient from the user
    while (true) {
      cout << "Enter Patient age: ";
      cin >> age;

      if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cerr << "\nError: Please enter a numbers for patient ID. Try again...\n\n";
        continue;
      }

      if (!isValidAge(age)) {
        cerr << "\nError: Invalid age. The age can't be negative. Try again...\n\n";
        continue;
      }

      break;
    }
    cin.ignore();

    // Get Patient's sex from the user
    while (true) {
      cout << "Enter Patient sex: ";
      cin >> sex;

      if (!isValidSex(sex)) {
        cerr << "\nnError: Invalid sex. Try again...\n\n";
        continue;
      }

      break;
    }

    // Get Patient's admission date from the user
    while (true) {
      cout << "Enter Admission Date (DD-MM-YYYY): ";
      cin >> admissionDate;

      // Check if the admission date is valid or not
      if (!checkDateFormat(admissionDate)) {
        cerr << "\nError: Invalid Admission Date. Try again...\n\n";
        continue;
      }

      // End the loop
      break;
    }

    // Get Patient's word no from the user
    while (true) {
      cout << "Enter Word No: ";
      cin >> wordNo;

      if (!isValidWord(wordNo)) {
        cerr << "\nError: Invalid Word NO. Try again...\n\n";
        continue;
      }

      break;
    }
    cin.ignore();

    // Get the doctor name under which the patient is
    while (true) {
      cout << "Enter Doctor name: ";
      getline(cin, underDoctor);

      // Check if the entered name is empty or not
      if (nameOfPatient.empty()){
        cerr << "\nError: Doctor name cannot be empty. Try again...\n\n";
        continue;
      }

      // End the loop
      break;
    }

    // Push details to the "data/data.txt" file
    data.push_back(Patient(id, nameOfPatient, age, sex, admissionDate, wordNo, underDoctor));

    // Save the file
    saveToFile(data);
    cout << "\nData saved.\n";
  };

  commands["?"] = [&]() {
    if (!inAdvancedMode) {
      cout << "\n=======Available Commands=======\n";
      cout << " create            - Create a new account\n";
      cout << " cls               - Clears the screen\n";
      cout << " switch            - Switch between Normal and Advanced mode\n";
      cout << " ?                 - Show all available commands\n";
      cout << " exit              - Exit the program\n";
    }
    else {
      cout << "\n=======Available Commands In Advanced Mode=======\n";
      cout << " create            - Create a new account\n";
      cout << " details           - Show Patient details\n";
      cout << " cls               - Clears the screen\n";
      cout << " list              - List of details of all patients\n";
      cout << " switch            - Switch between Normal and Advanced mode\n";
      cout << " delete            - Delete a specific Patient record\n";
      cout << " changepassword    - Change the admin password\n";
      cout << " ?                 - Show all available commands\n";
      cout << " exit              - Exit the program\n";
    }
  };

  commands["exit"] = [&]() {
    cout << "\nExiting the program...\n";
    cout << "\nGOODBYE!!!  :)\n\n";
    exit(0);
  };

  commands["switch"] = [&]() {
    if (inAdvancedMode) {
      cout << "\n----------------------------\n\n";
      cout << "Switching to NORMAL Mode...\n";
      cout << "\n----------------------------\n";

      inAdvancedMode = false;
    }
    else {
      if (checkPassword("data/password.txt")) {
        cout << "\n----------------------------\n\n";
        cout << "Switching to ADVANCED Mode...\n";
        cout << "\n----------------------------\n";

        inAdvancedMode = true;
      }
      else
        cout << "\n##########Access Denied##########\n";
    }
  };

  commands["cls"] = [&]() {
    system("clear");
  };

  // All ADVANCED Mode commands
  commands["details"] = [&]() {
    if (inAdvancedMode) {
      cout << "\n=======Patient Details=======\n";
      int index = searchPatient(data);
      if (index != -1)
        data[index].displayPatientDetails();
      else
        cout << "Patient not found!!!";
    }
    else
      cout << "\n##########Switch to Advanced Mode for this command##########\n";
  };

  commands["list"] = [&]() {
    if (inAdvancedMode) {
      ifstream file("data/data.txt");

      if (!file) {
        cout << "Unable to open the file!!!" << endl;
        return;
      }

      cout << "\n=======List Of Patients=======\n";

      string line;
      while (getline(file, line))
        cout << line << endl;
            
      file.close();
    }
    else
      cout << "\n##########Switch to Advanced Mode for this command##########\n";
  };

  commands["delete"] = [&]() {
    if (inAdvancedMode) {
      int index = searchPatient(data);
      deleteRecord(data, index);
    }
    else
      cout << "\n##########Switch to Advanced Mode for this command##########\n";
  };

  // Command to change the password 
  commands["changepassword"] = [&]() {
    if (inAdvancedMode)
      changePassword();
    else
      cerr << "\n##########Switch to Advanced Mode for this command##########\n";
  };

  /*
  -------------------------------------
  Doctor class commands
  -------------------------------------
  */

  // Command to create Doctor records
  commands["create"] = [&]() {
    if (!inDoctorMode) {
      cerr << "\n##########Switch to Doctor Mode to access this command##########\n";
      return;
    }

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
        cin.ignore(numeric_limits<stringstream>::max(), '\n');
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
        cin.ignore(numeric_limits<stringstream>::max(), '\n');
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
  };
          
  return commands;
}
