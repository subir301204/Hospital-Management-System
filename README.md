# Project Overview: Hospital Management System

## Introduction

This document provides a comprehensive overview of the Hospital Management System, a command-line application developed in C++. The system is designed to manage patient and doctor information efficiently. It operates in two distinct modes: a standard `Normal Mode` for basic interactions and a secure `Advanced Mode` for administrative tasks, which is protected by a password.

## Features

The Hospital Management System offers the following key features:

- **Dual Operating Modes**: 
  - **Normal Mode**: Provides fundamental commands for creating new patient entries and navigating the system.
  - **Advanced Mode**: Unlocks administrative functionalities such as viewing detailed patient records, listing all patients, and deleting entries. Access to this mode is restricted via a password.
- **Patient Management**:
  - Create, view, list, and delete patient records.
  - Each patient record includes a unique ID, name, age, sex, admission date, ward number, and the name of the attending doctor.
  - Robust input validation is in place for all patient attributes to ensure data integrity.
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

## Data Storage

The application uses the following files for data persistence, located in the `data/` directory:

- `data.txt`: Stores the records for all patients.
- `password.txt`: Securely stores the password required to access the `Advanced Mode`.
