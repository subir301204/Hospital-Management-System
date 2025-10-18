#include "Patient.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <limits>
#include <conio.h>

using namespace std;

// File handling functions
void saveToFile(const vector<Patient> &data) {
  ofstream fout("data/data.txt");

  if (!fout) {
    cerr << "Error: Cannot open file 'data/data.txt' for writing.\n";
    return;
  }

  cout << "Saving new records...\n";

  for (auto &da : data)
    fout << da.getID() << " " << da.getAdmissionDate() << " " << da.getName() << "\n";
  fout.close();
}

vector<Patient> loadFromFile() {
  vector<Patient> data;
  ifstream fin("data/data.txt");
  int id;
  string admissionDate, nameOfPatient;
  while (fin >> id >> admissionDate >> nameOfPatient)
    data.push_back(Patient(id, admissionDate, nameOfPatient));
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

  for (int i = 0; i <data.size(); i++)
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

// Function to delete a spacific record
void deleteRecord(const vector<Patient> &data, const int lineIndex) {
  ifstream fin("data/data.txt");
  if (!fin) {
    cerr << "Error: Unable to open the file!\n";
    return;
  }

  vector<string> lines;
  string line;

  while (getline(fin, line))
    lines.push_back(line);
  fin.close();

  // Remove the spacific line
  lines.erase(lines.begin() + lineIndex);

  ofstream fout("data/data.txt");
  if(!fout) {
    cerr << "Error: Unable to write to file!\n";
    return;
  }

  for (const string &l : lines)
    fout << l << "\n";
  fout.close();

  cout << "\nRecord has been deleted...\n";
}

