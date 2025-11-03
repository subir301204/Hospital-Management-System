# Project Overview: Hospital Management System

## Introduction

This document provides a comprehensive overview of the Hospital Management System, a command-line application developed in C++. The system is designed to manage patient and doctor information efficiently. It operates in three distinct modes: a standard `Normal Mode` for basic interactions, a secure `Patient Mode` for administrative tasks and another secure `Doctor Mode`, which are both protected by a password.

## Features

The Hospital Management System offers the following key features:

- **Three Operating Modes**: 
  - **Normal Mode**: Provides fundamental commands for creating new patient entries and navigating the system.
  - **Patient Mode**: This mode grant access to all the Patient management commands. This mode is protected by a user defined password.
  - **Doctor Mode**: This mode grant access to all the Doctor management commands. This mode is protected by a user define password.
- **Patient Management**:
  - Create, view, list, and delete patient records.
  - Each patient record includes a unique ID, name, age, sex, admission date, ward number, and the name of the attending doctor.
  - Robust input validation is in place for all patient attributes to ensure data integrity.
- **Doctor Management**:
  - Create, list, details, delete and edit doctor records.
  - Each doctor record include a unique ID, name, specialization, qualification, experience, contact number, email, availability, appointment count.
  - Robust input validation is in place for all doctor attributes to ensure data integrity.
- **Data Persistence**: 
  - All patient and doctor data is stored in plain text files, ensuring that information is retained across sessions.

## File Structure

The project is organized into the following directory structure:

- `include/`: This directory contains all the header files (`.h`), which define the classes and function prototypes used throughout the project.
- `src/`: This directory holds all the source files (`.cpp`), which provide the implementation for the functionalities declared in the header files.
- `data/`: This directory is designated for data storage. It contains the text files that store patient and doctor information.

## How to Compile and Run

To compile and run the application, follow these steps:

1. **Compilation**:
   Open your terminal and execute the following command. This command compiles all the source files and links them with the necessary headers to create an executable file named `main`.

   ```bash
   g++ src/*.cpp -I include -o main
   ```

2. **Execution**:
   After successful compilation, run the application with the following command:

   ```bash
   ./main
   ```

## Classes

The system is built around two primary classes:

- **`Patient`**: This class represents a patient and encapsulates all the related attributes and functions, such as displaying patient details.
- **`Doctor`**: This class represent a doctor and encapsulates all the related attributes and functions, such as displaying doctor details.

## Data Storage

The application uses the following files for data persistence, located in the `data/` directory:

- `data.txt`: Stores the records for all patients.
- `data2.txt`: Stores the records for all doctors.
- `password.txt`: Securely stores the password required to access the `Patient Mode`.
- `passwordDoctor.txt`: Securely stores the password required to access the `Doctor Mode`.

