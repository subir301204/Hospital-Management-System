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

