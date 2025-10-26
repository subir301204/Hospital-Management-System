#include "Patient.h"
#include "Getch_cross.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <regex>
#include <sstream>
#include <string>

using namespace std;

// Save all patients to file
void saveToFile(const vector<Patient> &data) {
  ofstream fout("data/data.txt");
  if (!fout) {
    cerr << "Error: Cannot open file 'data/data.txt' for writing.\n";
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
    if (cin >> id) break;

    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cerr << "Invalid input. Try again...\n";
  }
  cin.ignore(numeric_limits<streamsize>::max(), '\n');

  for (int i = 0; i < data.size(); i++)
    if (data[i].getID() == id) return i;

  return -1;
}

// Check password
bool checkPassword() {
  const string passwordFile = "data/password.txt";

  ifstream fin2(passwordFile);

  if (!fin2) {
    cerr << "\nError: No admin password found!!!\n";
    cout << "\n=======Create a Password=======\n";
    string newPassword = getHiddenInput();

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

  string input = getHiddenInput();

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