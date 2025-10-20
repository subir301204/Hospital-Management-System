#include "Patient.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <conio.h>
#include <regex>

using namespace std;

// File handling functions
void saveToFile(const vector<Patient> &data) {
  ofstream fout("data/data.txt");

  if (!fout) {
    cerr << "Error: Cannot open file 'data/data.txt' for writing.\n";
    return;
  }

  cout << "\nSaving new records...\n";

  for (auto &da : data)
    fout << da.getID() << "  " << da.getName() << "  " << da.getAdmissionDate() << "\n";
  fout.close();
}

vector<Patient> loadFromFile() {
  vector<Patient> data;
  ifstream fin("data/data.txt");
  int id;
  string admissionDate, nameOfPatient;
  while (fin >> id >> nameOfPatient >> admissionDate)
    data.push_back(Patient(id, nameOfPatient, admissionDate));
  fin.close();
  return data;
}

int searchPatient(const vector<Patient> &data, int id) {
  for (int i = 0; i < data.size(); i++)
    if (data[i].getID() == id)
      return i;
  return -1;
}

int searchPatient(vector<Patient> &data) {
  int id;
  while (true) {
    cout << "Enter the Patient Id: ";
    cin >> id;

    if (cin.fail()) {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Invalid input. Try again...";
    }
    else {
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      break;
    }
  }

  for (int i = 0; i < data.size(); i++)
    if (data[i].getID() == id)
      return i;
  
  return -1;
}


// Function to get hidden inputs
string getHiddenInput() {
  string input;
  char ch;

  while ((ch = _getch()) != '\r') {
    if (ch == '\b' && !input.empty()) {
      input.pop_back();
      cout << "\b \b";
    }
    else if (ch != '\b') {
      input.push_back(ch);
      cout << '*';
    }
  }

  cout << endl;
  return input;
}

// Function to check password validity
bool checkPassword() {
  ifstream fin("data/password.txt");
  if (!fin) {
    cerr << "No password file found. Please create one first.\n";
    return false;
  }

  string stored, input;
  getline(fin, stored);
  fin.close();

  cout << "Enter admin password: ";
  input = getHiddenInput();
  
  return (input == stored);
}

// Function to delete a specific record
void deleteRecord(vector<Patient> &data, const int lineIndex) {
  // Check valid line index
  if (lineIndex < 0 || lineIndex >= data.size()) {
    cerr << "\nError: Invalid record index...\n\n";
    return;
  }

  data.erase(data.begin() + lineIndex);

  ofstream fout("data/data.txt");
  if (!fout) {
    cerr << "\nError: Unable to write to file!\n";
    return;
  }

  for (auto &d : data)
    fout << d.getID() << "  " << d.getName() << "  " << d.getAdmissionDate() << '\n';
  fout.close();

  cout << "\nRecord deleted successfully.\n";
}

// Function to check admission date format validity
bool checkDateFormat(const string &date) {
  // Check the Date format
  regex dateFormat(R"(^\d{2}-\d{2}-\d{4}$)");   // Format: DD-MM-YYYY

  if (!regex_match(date, dateFormat))
    return false;

  // Extracting day, month, year
  int day = stoi(date.substr(0, 2));
  int month = stoi(date.substr(3, 2));
  int year = stoi(date.substr(6, 4));

  // Basic month and day range check
  if (month < 1 || month > 12 || day < 1 || year > 2025 || year < 1900)
    return false;

  // Days in each month
  int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  // Leap year check
  if ((year % 4 == 0 && year % 100 == 0) || (year % 400 == 0))
    daysInMonth[1] = 29;
  
  // Final day check
  if (day > daysInMonth[month - 1])
    return false;
  
  return true;
}

// Function to check Patient name validity
bool checkName(const string &name) {
  // Allowing only alphabets and spaces between them
  regex namePattern(R"(^[A-Za-z ]+$)");
  return (regex_match(name, namePattern));
}