#include "Patient.h"
#include "Getch_cross.h"
#include "Doctor.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <regex>
#include <sstream>
#include <string>
#include <algorithm>

using namespace std;

/*
------------------------------------
Patient Utility functions
------------------------------------
*/

// Save all patients to file
void saveToFile(const vector<Patient> &data) {
  ofstream fout("data/data.txt");
  if (!fout) {
    cerr << "\nError: Cannot open file \"data/data.txt\" for writing.\n\n";
    return;
  }

  cout << "\nSaving new records...\n";
  for (const auto &d : data)
    fout << d.getID() << "  " << "  " << d.getName() << "  " << d.getAge() << "  " << d.getSex() << "  " << d.getAdmissionDate() << "  " << d.getWordNo() << "  " << d.getUnderDoctor() << "\n";
}

// Load all patients from file
vector<Patient> loadFromFile() {
  vector<Patient> data;
  ifstream fin("data/data.txt");

  if (!fin) {
    cerr << "\nError: Cannot open the file for reading.\n\n";
    return data;
  }

  string line;
  while (getline(fin, line)) {
    if (line.empty())
      continue;
    
    stringstream ss(line);
    int id;
    ss >> id;

    vector<string> tokens;
    string token;
    while (ss >> token)
      tokens.push_back(token);

    if (tokens.size())
      continue;

    string underDoctor = tokens.back();
    tokens.pop_back();
    string wordNo = tokens.back();
    tokens.pop_back();
    string admissionDate = tokens.back();
    tokens.pop_back();
    string sex = tokens.back();
    tokens.pop_back();
    int age = stoi(tokens.back());
    tokens.pop_back();

    string name;
    for (size_t i = 0; i < tokens.size(); i++) {
      name += tokens[i];
      if (i != tokens.size())
        name += " ";
    }

    data.emplace_back(id, name, age, sex, wordNo, underDoctor, admissionDate);
  }

  fin.close();
  return data;
}

/*
----------------------------------------
Patient Utility functions
----------------------------------------
*/

// Search patient by ID, return index
int searchPatient(const vector<Patient> &data, int id) {
  for (int i = 0; i < data.size(); i++)
    if (data[i].getID() == id) return i;
  return -1;
}

// Search patient by user input
int searchPatient(vector<Patient> &data) {
  int id;
  while (true) {
    cout << "Enter the Patient Id: ";
    if (cin >> id) 
      break;

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cerr << "Invalid input. Try again...\n";
  }

  for (int i = 0; i < data.size(); i++)
    if (data[i].getID() == id)
      return i;

  return -1;
}

// Check password
bool checkPassword() {
  const string passwordFile = "data/password.txt";

  ifstream fin2(passwordFile);

  if (!fin2) {
    cerr << "\nError: No admin password found!!!\n";
    cout << "\n=======Create a Password=======\n";
    string newPassword = getHiddenInput("Enter admin password: ");

    ofstream fout(passwordFile);

    if (!fout) {
      cerr << "\nError: Cannot create password file!!!\n\n";
      return false;
    }

    fout << newPassword;
    fout.close();

    cout << "\nPassword saved successfully! You won't be asked again.\n";
    return true;
  }
  else
    fin2.close();

  ifstream fin1(passwordFile);

  if (!fin1) {
    cerr << "\nError: Cannot open the password file!!!\n\n";
    return false;
  }

  fin1.seekg(0, ios::end);
  if (fin1.tellg() == 0) {
    fin1.close();
    cerr << "\nError: File is empty. Deleting...\n\n";
    if (remove(passwordFile.c_str()) == 0)
      cout << "\nFile deleted successfully! Try again with \"switch\" command.\n\n";
    else
      cerr << "\nError: Could not delete file.\n";
  }

  ifstream fin(passwordFile);

  if (!fin) {
    cerr << "\nError: Cannot open the password file!!!\n\n";
    return false;
  }

  string passwordStored;
  getline(fin, passwordStored);
  fin.close();

  string input = getHiddenInput("Enter admin password: ");

  if (input == passwordStored) {
    cout << "\nAccess granted!\n";
    return true;
  }
  else {
    cerr << "\nAccess denied! Wrong password.\n";
    return false;
  }
}

// Delete record
void deleteRecord(vector<Patient> &data, const int lineIndex) {
  if (lineIndex < 0 || lineIndex >= data.size()) {
    cerr << "\nError: Invalid record index!\n";
    return;
  }

  data.erase(data.begin() + lineIndex);
  saveToFile(data);
  cout << "\nRecord deleted successfully.\n";
}

// Check date format and validity
bool checkDateFormat(const string &date) {
  regex dateFormat(R"(^\d{2}-\d{2}-\d{4}$)");
  if (!regex_match(date, dateFormat)) 
    return false;

  int day = stoi(date.substr(0, 2));
  int month = stoi(date.substr(3, 2));
  int year = stoi(date.substr(6, 4));

  if (month < 1 || month > 12 || day < 1 || year < 1900 || year > 2025)
    return false;

  int daysInMonth[] = {31,28,31,30,31,30,31,31,30,31,30,31};
  if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
    daysInMonth[1] = 29;

  return day <= daysInMonth[month - 1];
}

// Check name validity (alphabets + spaces)
bool checkName(const string &name) {
  regex namePattern(R"(^[A-Za-z ]+$)");
  return regex_match(name, namePattern);
}

// Function to check Patient ID validity
bool checkPatientID(const int &pID) {
  if (pID < 999999 || pID > 10000000)
    return false;
  return true;
}

bool isValidAge(const int &age) {
  if (age <= 0)
    return false;
  return true;
}

bool isValidSex(const string &sex) {
  return (sex == "M" || sex == "F" || sex == "O");
}

bool isValidWord(const string &wordNo) {
  return (wordNo == "W1" || wordNo == "W2" || wordNo == "W3" || wordNo == "W4" || wordNo == "W5");
}

// Function to change the switch mode password
void changePassword() {
  string passwordFile = "data/password.txt";
  cout << "\n=======Changing the password=======\n";
  
  if (checkPassword()) {
    if (remove(passwordFile.c_str()) == 0) {
      string newPassword =  getHiddenInput("\nEnter new password: ");

      ofstream fout("data/password.txt");

      if (!fout) {
        cerr << "\nError: Cannot change the password!!!\n\n";
        return;
      }

      fout << newPassword;
      fout.close();

      cout << "\nPassword changed successfully!!!\n\n";
    }
  }
}

/*
----------------------------------------------
Doctor class utility functions
----------------------------------------------
*/

// Function to save Doctor data to the file
void saveToFile(const vector<Doctor> &data2) {
  ofstream fout("data/doctor.txt");

  if (!fout) {
    cerr << "\nError: Cannot open file \"data/doctor.txt\" for writing.\n\n";
    return;
  }

  cout << "\nSaving new records...\n";
  for (const auto &d : data2)
    fout << d.getID() << "  " << d.getName() << "  " << d.getSpecialization() << "  " << d.getQualification() << "  " << d.getExperience() << "  " << d.getContactNumber() << "  " << d.getEmail() << "  " << d.getAvailable() << "  " << d.getAppointmentCount() << "\n";
}

// Function to load Doctors details from the file
vector<Doctor> loadFromFileDoctor() {
  vector<Doctor> data2;
  ifstream fin("data/doctor.txt");

  if (!fin) {
    cerr << "\nError: Cannot open the file for reading.\n\n";
    return data2;
  }

  string line;
  while (getline(fin, line)) {
    if (line.empty())
      continue;
    
    stringstream ss(line);
    int id;
    ss >> id;

    vector<string> tokens;
    string token;
    while (ss >> token)
      tokens.push_back(token);
    
    if (tokens.size())
      continue;
    
    int appointmentCount = stoi(tokens.back());
    tokens.pop_back();
    string available = tokens.back();
    tokens.pop_back();
    string email = tokens.back();
    tokens.pop_back();
    string contactNumber = tokens.back();
    tokens.pop_back();
    int experience = stoi(tokens.back());
    tokens.pop_back();
    string qualification = tokens.back();
    tokens.pop_back();
    string specialization = tokens.back();
    tokens.pop_back();

    string name;
    for (size_t i = 0; i < tokens.size(); i++) {
      name += tokens[i];
      if (i != tokens.size())
        name += " ";
    }

    data2.emplace_back(id, name, specialization, qualification, experience, contactNumber, email, available, appointmentCount);
  }

  fin.close();
  return data2;
}

// Function to check Doctor's pin validity
bool checkDoctorPin(const int &dID) {
  if (dID < 999999 || dID > 10000000)
    return false;
  return true;
}

// Function to search doctor without dID
int searchDoctor(vector<Doctor> &data2) {
  int id;
  while (true) {
    cout << "Enter Doctor ID: ";
    if (cin >> id)
      break;
    
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cerr << "\nError: Invalid input. Try again...\n\n";
  }

  for (int i = 0; i < data2.size(); i++)
    if (data2[i].getID() == id)
      return i;
  
  return -1;
}

// Function to delete a Doctor record
void deleteDoctor(vector<Doctor> &data2, const int lineIndex) {
  if (lineIndex < 0 || lineIndex >= data2.size()) {
    cerr << "\nError: Invalid record index!\n\n";
    return;
  }

  data2.erase(data2.begin() + lineIndex);
  saveToFile(data2);
  cout << "\nRecord deleted successfully.\n\n";
}

// Function to search Doctor with dID
int searchDoctor(vector<Doctor> &data2, const int &dID) {
  for (int i = 0; i < data2.size(); i++)
    if (data2[i].getID() == dID)
      return i;
  return -1;
}

// Function to check the name validity of Doctor
bool checkDoctorName(const string &name) {
  regex namePattern(R"(^[A-Za-z .'\-]+$)");
  return regex_match(name, namePattern);
}

// Function to show the available specialization list
void displaySpecialization() {
  cout << "\n=======Available Specialization Fields=======\n";
  cout << "Cardiologist         - Heart and blood vessels (cardiovascular system)\n";
  cout << "Neurologist          - Brain, spinal cord, and nervous system\n";
  cout << "Pulmonologist        - Lungs and respiratory system\n";
  cout << "Gastroenterologist   - Digestive system and stomach-intestine issues\n";
  cout << "Nephrologist         - Kidneys and urinary system\n";
  cout << "Endocrinologist      - Hormones and glands (e.g., diabetes, thyroid)\n";
  cout << "Rheumatologist       - Joints, muscles, and autoimmune diseases\n";
  cout << "Hematologist         - Blood and blood-forming organs\n";
  cout << "Gynecology           - Female reproductive system, pregnancy, childbirth\n";
  cout << "Oncology             - Diagnosis and treatment of cancer\n";
  cout << "Dermatology          - Skin, hair, and nail diseases\n";
  cout << "Audiology            - Hearing and balance disorders\n";
  cout << "Dentistry            - Oral and dental care\n";
  cout << "Veterinary Medicine  - Medical care of animals\n";
  cout << "Urology              - Urinary tract and male reproductive organs\n";
  cout << "Pediatrics           - Health and diseases of infants and children\n";
  cout << "Orthopedic           - Musculoskeletal system — bones, muscles, ligaments, joints\n";
}

// Function to check the Doctor specialization validity
bool isValidSpecialization(const string &specialization) {
  const vector<string> SPECIALIZATION = {
    "Cardiologist",
    "Neurologist",
    "Pulmonologist",
    "Gastroenterologist",
    "Nephrologist",
    "Endocrinologist",
    "Rheumatologist",
    "Hematologist",
    "Gynecology",
    "Oncology",
    "Dermatology",
    "Veterinary Medicine",
    "Urology",
    "Pediatrics",
    "Orthopedic"
  };

  if (find(SPECIALIZATION.begin(), SPECIALIZATION.end(), specialization) != SPECIALIZATION.end())
    return true;
  
  return false;
}

// Function to display available doctor qualifications
void displayQualification() {
  cout << "\n=======Available Doctor Qualifications=======\n";
  cout << "MBBS   - Bachelor of Medicine and Bachelor of Surgery\n";
  cout << "MD     - Doctor of Medicine\n";
  cout << "MS     - Master of Surgery\n";
  cout << "DM     - Doctorate of Medicine\n";
  cout << "MCh    - Magister Chirurgiae (Master of Surgery)\n";
  cout << "BDS    - Bachelor of Dental Surgery\n";
  cout << "MDS    - Master of Dental Surgery\n";
  cout << "BVSc   - Bachelor of Veterinary Science\n";
  cout << "PhD    - Doctor of Philosophy\n";
  cout << "DNB    - Diplomate of National Board\n";
  cout << "BHMS   - Bachelor of Homeopathic Medicine and Surgery\n";
  cout << "BAMS   - Bachelor of Ayurvedic Medicine and Surgery\n";
}

// Function to check doctor's qualification validity
bool isValidQualification(const string &qualification) {
  const vector<string> QUALIFICATION = {
    "MBBS",
    "MD",
    "MS",
    "DM",
    "MCh",
    "BDS",
    "MDS",
    "BVSc",
    "PhD",
    "DNB",
    "BHMS",
    "BAMS"
  };

  if (find(QUALIFICATION.begin(), QUALIFICATION.end(), qualification) != QUALIFICATION.end())
    return true;
  
  return false;
}

// Function to get Doctor details
void doctorDetails() {
  cout << "\n=======Details of the Doctor=======\n";
}